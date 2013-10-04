
#include "PackageManager.h"
#include "Logger.h"
#include "Package.h"
#include "MyEffect.h"

PackageManager* PackageManager::myInstance=NULL;

PackageManager::PackageManager()
:aapi(NULL)
,iapi(NULL){
}

PackageManager::~PackageManager(){
}

PackageManager* PackageManager::CreateInstance(){
	if(myInstance==NULL){
		myInstance=new PackageManager;
	}
	return myInstance;
}
void PackageManager::DestroyInstance(){
	SAFE_DELETE(myInstance);
}


bool PackageManager::Init(AudioApi* _aapi,InputApi* _iapi){
	Logger::Println("[PackageManager]	Initialize");

	aapi=_aapi;
	iapi=_iapi;

	package=MyEffect::CreateInstance();
	if(package->Init(aapi,iapi)==-1){
		return false;
	}
	endFlag=false;
	return true;
}

void PackageManager::Close(){
	Logger::Println("[PackageManager]	Close");
	endFlag=true;
	package->Close();
	MyEffect::DestroyInstance();
}

int PackageManager::TimerMain(){
	if(IsActive()){
		int res=package->Run();
		if(res==1){
			package->Reset();
		}else if(res==2){
			return -1;
		}
	}
	return 0;
}

void PackageManager::AudioMain(float* in,float* out,int frames){
	if(IsActive()){
		package->AudioCallback(in,out,frames);
	}else{
		for(int i=0;i<frames;i++){
			*out++ = 0.0f;
			*out++ = 0.0f;
		}
	}
}

void PackageManager::GraphicMain(){
	if(IsActive()){
		package->GraphicCallback();
	}
}

bool PackageManager::IsEnd(){
	return endFlag;
}

int PackageManager::TimerCallbackProc(){
	if(myInstance!=NULL){
		return myInstance->TimerMain();
	}else{
		return 0;
	}
}
void PackageManager::AudioCallbackProc(float* in,float* out,int frames){
	if(myInstance!=NULL){
		myInstance->AudioMain(in,out,frames);
	}
}

void PackageManager::GraphicCallbackProc(){
	if(myInstance!=NULL){
		myInstance->GraphicMain();
	}
}

bool PackageManager::IsActive(){
	if(package!=NULL && !endFlag)	return true;
	else return false;
}

void PackageManager::BackToStart(){
	myInstance->BackToStartProc();
}

void PackageManager::BackToStartProc(){
	package->End();
	package->Reset();
}