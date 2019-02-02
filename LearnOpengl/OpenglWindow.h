#pragma once

#include<windows.h>
#include <glad/glad.h>

class OpenglWindow
{

//protected static
protected:
	static LRESULT CALLBACK DefaultWindowProc(HWND, UINT, WPARAM, LPARAM);
	static void DefaultRenderProc(HDC hDC);
	static void* GetAnyGLFuncAddress(const char* name);

public:
	OpenglWindow(HINSTANCE hInstance, int nCmdShow, WNDPROC wndProc = DefaultWindowProc, void(*Render)(HDC hDC) = DefaultRenderProc, int width = 800, int height = 600);
	~OpenglWindow();

	void EnableOpenGL();
	void DisableOpenGL();

	int exec();

protected:
	WNDCLASSEX wcex;
	HWND hwnd;
	HDC hDC;
	HGLRC hRC;
	MSG msg;
	BOOL bQuit = FALSE;
	HINSTANCE hInstance;
	int nCmdShow;
	int width;
	int height;
	bool isOpenglEnabled = false;

	WNDPROC wndProc;
	void (*Render)(HDC hDC);

	void MainLoop();
};

