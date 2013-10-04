
#pragma once

#include "Common.h"

class InputLine{
protected:
	vector <char> waveData;
	int cursor;

public:
	virtual WavePacket* GetSamples(){
		cursor+=step;
		return wavePacket;
	}
	virtual int GetRestSample(){
		return waveData.size()-cursor;
	}
	virtual void CursorReset(){
		cursor=0;
	}
};