
#pragma once

#include "Common.h"

class ArgumentInterpreter{
private:
	static ArgumentInterpreter* myInstance;
public:
	static string inputFile;
	static string outputFile;
	static int inputLine;
	static int outputLine;
	static int speakerSwitch;
	static bool speakerConvolutionFlag;
	static int hallType;
	static bool isModeConvertFlag;
	static bool playAfterConvertFlag;
	static bool fileOutputFlag;

	static void Init(int argc,char** argv);
};