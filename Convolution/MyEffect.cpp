
#include "MyEffect.h"
#include "Logger.h"
#include "ArgumentInterpreter.h"

MyEffect* MyEffect::myInstance=NULL;

Package* MyEffect::CreateInstance(){
	if(myInstance==NULL){
		myInstance=new MyEffect;
	}
	return myInstance;
}
void MyEffect::DestroyInstance(){
	if(myInstance!=NULL){
		SAFE_DELETE(myInstance);
	}
}

int MyEffect::Init(AudioApi* _aapi,InputApi* _iapi){
	ShowCursor(true);
	srand((unsigned)time(NULL));

	iapi=_iapi;
	aapi=_aapi;

	string impulseFile="./impulse/impulse";
	switch(ArgumentInterpreter::hallType){
	case 0:
		impulseFile+="_komaba";
		break;
	case 1:
		impulseFile+="_hongo";
		break;
	case 2:
		impulseFile+="_nohall";
		break;
	}
	if(ArgumentInterpreter::hallType!=2){
		switch(ArgumentInterpreter::speakerSwitch){
		case 0:
			impulseFile+="_spboth";
			break;
		case 1:
			impulseFile+="_spleft";
			break;
		case 2:
			impulseFile+="_spright";
			break;
		}
	}
	if(ArgumentInterpreter::speakerConvolutionFlag){
		impulseFile+="_spconv";
	}else{
		impulseFile+="_nospconv";
	}
	impulseFile+=".wav";
	snd_impulseResponse = aapi->LoadWaveFile(impulseFile);
	if(snd_impulseResponse==-1){
		return -1;
	}

	snd_convertTarget = aapi->LoadWaveFile(ArgumentInterpreter::inputFile);
	if(snd_convertTarget==-1){
		return -1;
	}

	targetLength = aapi->GetWaveShellLeft(snd_convertTarget)->GetLength();
	impulseLength = aapi->GetWaveShellLeft(snd_impulseResponse)->GetLength();
	impulseLength*=2;

	double* impr = new double[impulseLength];
	fftw_complex* impc = new fftw_complex[impulseLength];
	double* tarr = new double[impulseLength];
	fftw_complex* tarc = new fftw_complex[impulseLength];
	wstemp = new float[targetLength+impulseLength/2];
	
	maxNorm=0;

	Logger::Println("[Start FFT Plan]");
	plan_rc = fftw_plan_dft_r2c_1d(impulseLength,impr,impc,FFTW_ESTIMATE);
	Logger::Println("[Start IFFT Plan]");
	plan_cr = fftw_plan_dft_c2r_1d(impulseLength,impc,impr,FFTW_ESTIMATE);

	if(ArgumentInterpreter::hallType!=2 && ArgumentInterpreter::speakerSwitch==1){
		Logger::Println("[Start Right Convolution]");
		Convolution(impr,impc,tarr,tarc,
			aapi->GetWaveShellRight(snd_impulseResponse),
			aapi->GetWaveShellLeft(snd_convertTarget),
			aapi->GetWaveShellRight(snd_convertTarget));
		Logger::Println("[Start Left Convolution]");
		Convolution(impr,impc,tarr,tarc,
			aapi->GetWaveShellLeft(snd_impulseResponse),
			aapi->GetWaveShellLeft(snd_convertTarget),
			aapi->GetWaveShellLeft(snd_convertTarget));
	}else if(ArgumentInterpreter::hallType!=2 && ArgumentInterpreter::speakerSwitch==2){
		Logger::Println("[Start Left Convolution]");
		Convolution(impr,impc,tarr,tarc,
			aapi->GetWaveShellLeft(snd_impulseResponse),
			aapi->GetWaveShellRight(snd_convertTarget),
			aapi->GetWaveShellLeft(snd_convertTarget));
		Logger::Println("[Start Right Convolution]");
		Convolution(impr,impc,tarr,tarc,
			aapi->GetWaveShellRight(snd_impulseResponse),
			aapi->GetWaveShellRight(snd_convertTarget),
			aapi->GetWaveShellRight(snd_convertTarget));
	}else{
		Logger::Println("[Start Right Convolution]");
		Convolution(impr,impc,tarr,tarc,
			aapi->GetWaveShellRight(snd_impulseResponse),
			aapi->GetWaveShellRight(snd_convertTarget),
			aapi->GetWaveShellRight(snd_convertTarget));
		Logger::Println("[Start Left Convolution]");
		Convolution(impr,impc,tarr,tarc,
			aapi->GetWaveShellLeft(snd_impulseResponse),
			aapi->GetWaveShellLeft(snd_convertTarget),
			aapi->GetWaveShellLeft(snd_convertTarget));
	}

	Logger::Println("[Start Normalize]");
	float normalize=(float)(1.0f/maxNorm);
	Logger::Println("	normalize:%f",normalize);
	for(int i=0;i<targetLength;i++){
		aapi->GetWaveShellLeft(snd_convertTarget)->shell[i]*=normalize;
		aapi->GetWaveShellRight(snd_convertTarget)->shell[i]*=normalize;
	}

	if(ArgumentInterpreter::fileOutputFlag){
		Logger::Println("[Start Output WaveFile]");
		aapi->WriteWaveFile(ArgumentInterpreter::outputFile,snd_convertTarget);
	}

	fftw_cleanup();
	delete[] tarr;
	delete[] tarc;
	delete[] impr;
	delete[] impc;
	delete[] wstemp;

	Reset();

	return 0;
}

void MyEffect::Convolution(double* impr,fftw_complex* impc,double* tarr,fftw_complex* tarc,WaveShell* wsimp,WaveShell* wstar,WaveShell* wsout){
	double real,img;
	int i,j,numBlock,halfImpulse,st;

	for(int i=0;i<impulseLength;i++){
		impc[i][0]=impc[i][1]=tarc[i][0]=tarc[i][1]=0;
		impr[i]=tarr[i]=0;
	}

	halfImpulse=impulseLength/2;
	numBlock=targetLength/halfImpulse+1;

	Logger::Println("[Prepare Impulse]");
	for(i=0;i<impulseLength;i++){
		if(i<impulseLength/2){
			impr[i]=0;
		}else{
			impr[i]=wsimp->shell[i-halfImpulse];
		}
	}
	fftw_execute_dft_r2c(plan_rc,impr,impc);
	for(i=0;i<impulseLength;i++){
		impc[i][0]/=impulseLength;
		impc[i][1]/=impulseLength;
	}
	fftw_execute_dft_c2r(plan_cr,impc,impr);

	Logger::Println("	Progress... ");
	for(i=0;i<numBlock;i++){
		st=halfImpulse*i;
		for(j=st-halfImpulse;j<st+halfImpulse;j++){
			if(j<0 || j>=targetLength){
				tarr[j-st+halfImpulse]=0;
			}else{
				tarr[j-st+halfImpulse]=wstar->shell[j];
			}
		}
		fftw_execute_dft_r2c(plan_rc,tarr,tarc);

		for(j=0;j<impulseLength;j++){
			tarc[j][0]/=impulseLength;
			tarc[j][1]/=impulseLength;
			real = tarc[j][0]*impc[j][0]-tarc[j][1]*impc[j][1];
			img = tarc[j][0]*impc[j][1]+tarc[j][1]*impc[j][0];
			tarc[j][0]=real;
			tarc[j][1]=img;
		}
		fftw_execute_dft_c2r(plan_cr,tarc,tarr);

		for(j=st;j<st+halfImpulse;j++){
			if(j>=0 && j<targetLength+halfImpulse){
				wstemp[j]=(float)tarr[j-st];
			}
		}
		Logger::Println("		Block:%d/%d",i+1,numBlock);
	}
	for(i=0;i<targetLength+halfImpulse;i++){
		maxNorm=max(maxNorm,fabs(wstemp[i]));
		if(i<targetLength){
			wsout->shell[i]=wstemp[i];
		}else{
			wsout->Add(wstemp[i]);
		}
	}
	Logger::Println("	Finish");
}


int MyEffect::Reset(){
	return 0;
}

int MyEffect::Close(){
	aapi->ReleaseWave(snd_convertTarget);
	return 0;
}

int MyEffect::End(){
	return 0;
}
int MyEffect::Run(){
	if(ArgumentInterpreter::playAfterConvertFlag){
		aapi->SetState(snd_convertTarget,AudioState::Audio_Play);
		Logger::Println("	Push Any Key to Exit");
		ArgumentInterpreter::playAfterConvertFlag=false;
	}

	if(aapi->GetState(snd_convertTarget)!=AudioState::Audio_Play){
		return 2;
	}
	if(_kbhit()){
		return 2;
	}
	return 0;
}

int MyEffect::GraphicCallback(){
	return 0;
}

int MyEffect::AudioCallback(float* in,float* out,int frames){
	int i;
	float left,right;
	for(i=0;i<frames;i++){
		left=right=0.0f;
		aapi->GetWaveDataAll(&left,&right);
		*out++ = left;
		*out++ = right;
	}
	return 0;
}
