
#pragma once

#include "package.h"
#include "fftw3.h"

class MyEffect:public Package{
private:

	int snd_convertTarget;
	int snd_impulseResponse;
	float* wstemp;

private:
	static MyEffect* myInstance;
public:
	virtual int Init(AudioApi* _aapi,InputApi* _iapi);
	virtual int Reset();
	virtual int Close();
	virtual int End();
	virtual int Run();
	virtual int AudioCallback(float* in,float* out,int frames);
	virtual int GraphicCallback();

	static Package* CALLBACK CreateInstance();
	static void CALLBACK DestroyInstance();

private:
	int impulseLength;
	int targetLength;
	fftw_plan plan_rc;
	fftw_plan plan_cr;
	float maxNorm;
	virtual void Convolution(double*,fftw_complex*,double*,fftw_complex*,WaveShell*,WaveShell*,WaveShell*);
};