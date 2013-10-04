
#include "Application.h"

//#pragma comment(lib, "dxguid.lib")
//#pragma comment(lib, "d3d9.lib")
//#pragma comment(lib, "d3dx9.lib")

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "ws2_32.lib")

#pragma comment(lib, "libfftw3-3.lib")
//#pragma comment(lib, "libfftw3f-3.lib")
//#pragma comment(lib, "libfftw3l-3.lib")

#ifdef _DEBUG
#pragma comment(lib, "portaudio_x86_debug.lib")
#else
#pragma comment(lib, "portaudio_x86.lib")
#endif

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Application* application = new Application;
	if(application->Init(&__argc,__argv,hInstance,hPrevInstance,lpCmdLine,nCmdShow)){
		application->Run();
	}
	application->Close();
	delete application;

	printf("Push any key to Exit\n");
	while(!_kbhit()){
	}
	return 0;
}
