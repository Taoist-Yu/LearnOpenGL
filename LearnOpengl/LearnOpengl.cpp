#include "OpenglWindow.h"

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	OpenglWindow wnd(hInstance, nCmdShow);
	wnd.EnableOpenGL();
	return wnd.exec();
}
