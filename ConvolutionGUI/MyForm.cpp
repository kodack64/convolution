
#ifdef _DEBUG
#pragma comment(lib, "portaudio_x86_debug.lib")
#else
#pragma comment(lib, "portaudio_x86.lib")
#endif

#include "MyForm.h"


using namespace Project1;

[STAThreadAttribute]
#ifdef _DEBUG
int main(int argc,int argv)
#else
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
#endif
{
	MyForm ^fm = gcnew MyForm();
	fm->ShowDialog();
	return 0;
}