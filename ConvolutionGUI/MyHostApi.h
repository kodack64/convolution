
#pragma once

#include "portaudio.h"
#include <vector>
#include <string>
using namespace std;

class MyDevice{
public:
	string name;
	int deviceId;
};

class MyHostApi{
public:
	string name;
	int hostApiId;

	int defaultInputDevice;
	vector <MyDevice*> inputDeviceList;
	int defaultOutputDevice;
	vector <MyDevice*> outputDeviceList;

	MyHostApi()
	:defaultInputDevice(-1),
	defaultOutputDevice(-1)
	{};
	virtual ~MyHostApi(){
		for(unsigned int i=0;i<inputDeviceList.size();i++){
			delete inputDeviceList[i];
		}
		for(unsigned int i=0;i<outputDeviceList.size();i++){
			delete outputDeviceList[i];
		}
	}
};

class MyHostApiList{
public:
	int defaultHostApi;
	vector <MyHostApi*> hostApiList;

	MyHostApiList(){};
	virtual ~MyHostApiList(){
		for(unsigned int i=0;i<hostApiList.size();i++){
			delete hostApiList[i];
		}
	};
	virtual void Initialize(){
		int hostApiCount;
		int deviceCount;

		Pa_Initialize();
		hostApiCount = Pa_GetHostApiCount();
		for(int i=0;i<hostApiCount;i++){
			const PaHostApiInfo* info = Pa_GetHostApiInfo(i);

			if(info->deviceCount>0){
				MyHostApi* api = new MyHostApi();
				api->name=info->name;
				api->hostApiId=i;
				if(Pa_GetDefaultHostApi()==i){
					defaultHostApi = hostApiList.size();
				}
				hostApiList.push_back(api);
			}
		}

		deviceCount = Pa_GetDeviceCount();
		for(int i=0;i<deviceCount;i++){
			const PaDeviceInfo* info = Pa_GetDeviceInfo(i);
			MyDevice* device = new MyDevice();
			device->deviceId=i;
			device->name=info->name;
			if(info->maxInputChannels>0){
				if(Pa_GetHostApiInfo(info->hostApi)->defaultInputDevice==i){
					hostApiList[info->hostApi]->defaultInputDevice=hostApiList[info->hostApi]->inputDeviceList.size();
				}
				hostApiList[info->hostApi]->inputDeviceList.push_back(device);
			}
			if(info->maxOutputChannels>0){
				if(Pa_GetHostApiInfo(info->hostApi)->defaultOutputDevice==i){
					hostApiList[info->hostApi]->defaultOutputDevice=hostApiList[info->hostApi]->outputDeviceList.size();
				}
				hostApiList[info->hostApi]->outputDeviceList.push_back(device);
			}
		}
		Pa_Terminate();
	}
};
