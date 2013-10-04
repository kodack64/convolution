
#include "ArgumentInterpreter.h"

string ArgumentInterpreter::inputFile;
string ArgumentInterpreter::outputFile;
int ArgumentInterpreter::inputLine;
int ArgumentInterpreter::outputLine;
int ArgumentInterpreter::speakerSwitch;
bool ArgumentInterpreter::speakerConvolutionFlag;
int ArgumentInterpreter::hallType;
bool ArgumentInterpreter::isModeConvertFlag;
bool ArgumentInterpreter::playAfterConvertFlag;
bool ArgumentInterpreter::fileOutputFlag;

void ArgumentInterpreter::Init(int argc,char** argv){

	inputFile="";
	outputFile="";
	inputLine=-1;
	outputLine=-1;
	speakerSwitch=0;
	hallType=0;
	isModeConvertFlag=false;
	speakerConvolutionFlag=false;
	playAfterConvertFlag=false;
	fileOutputFlag=false;

	string argstr;
	for(int i=0;i<argc;i++){
		argstr = argv[i];
		if(argstr=="-inputFile")		inputFile = argv[++i];
		if(argstr=="-inputLine")		inputLine = atoi(argv[++i]);
		if(argstr=="-outputFile")		outputFile = argv[++i];
		if(argstr=="-outputLine")		outputLine = atoi(argv[++i]);
		if(argstr=="-inputFromFile")	isModeConvertFlag=true;
		if(argstr=="-inputFromLine")	isModeConvertFlag=false;
		if(argstr=="-outputToFile")		fileOutputFlag=true;
		if(argstr=="-outputToLine")		playAfterConvertFlag=true;
		if(argstr=="-speakerConvolution")	speakerConvolutionFlag=true;
		if(argstr=="-speakerNotConvolution")speakerConvolutionFlag=false;
		if(argstr=="-speakerSwitchBoth")	speakerSwitch = 0;
		if(argstr=="-speakerSwitchLeft")	speakerSwitch = 1;
		if(argstr=="-speakerSwitchRight")	speakerSwitch = 2;
		if(argstr=="-hallKomaba")			hallType=0;
		if(argstr=="-hallHongo")			hallType=1;
		if(argstr=="-hallNone")				hallType=2;
	}
	cout << "[Argument]" << endl;
	cout << "	***File***" << endl;
	cout << "		inputFile	:" << inputFile << endl;
	cout << "		inputLine	:" << inputLine << endl;
	cout << "		outputFile	:" << outputFile << endl;
	cout << "		outputLine	:" << outputLine << endl;

	cout << "	***Mode***" << endl;
	cout << "		Convert		:" << isModeConvertFlag << endl;
	cout << "		PlayResult	:" << playAfterConvertFlag << endl;
	cout << "		FileOut		:" << fileOutputFlag << endl;

	cout << "	***Convlution***" << endl;
	cout << "		SpeakerCnv	:" << speakerConvolutionFlag << endl;
	cout << "		SpeakerSw	:" << speakerSwitch << endl;
	cout << "		HallType	:" << hallType << endl;
}