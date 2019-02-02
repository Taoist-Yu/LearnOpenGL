#include "OpenglWindow.h"
#include "Time.h"
#include "stdio.h"
#include "Text.h"

LRESULT CALLBACK  OpenglWindow::DefaultWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_DESTROY:
		return 0;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
	}
	break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

void OpenglWindow::DefaultRenderProc(HDC hDC)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//showframe
	static GLuint frames = 0;
	static GLfloat timeVal = 0;
	static GLuint fps = 0;
	timeVal += Time.GetUnscaledDeltaTime();
	frames++;
	if (timeVal > 1)
	{
		timeVal = 0;
		fps = frames;
		frames = 0;
	}
	TCHAR frametext[100];
	wsprintf(frametext, L"%d", fps);
	Text::Draw(frametext,0.8,0.9);

	SwapBuffers(hDC);
}

void* OpenglWindow::GetAnyGLFuncAddress(const char* name)
{

	void *p = (void *)wglGetProcAddress(name);
	if (p == 0 ||
		(p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) ||
		(p == (void*)-1))
	{
		HMODULE module = LoadLibraryA("opengl32.dll");
		p = (void *)GetProcAddress(module, name);
	}
	return p;
}

OpenglWindow::OpenglWindow(HINSTANCE hInstance, int nCmdShow, WNDPROC wndProc, void(*Render)(HDC hDC), int width, int height)
{
	this->hInstance = hInstance;
	this->nCmdShow = nCmdShow;
	this->wndProc = wndProc;
	this->Render = Render;
	this->width;
	this->height;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = wndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"GLSample";
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;

	RegisterClassEx(&wcex);

	/* create main window */
	hwnd = CreateWindowEx(0,
		L"GLSample",
		L"OpenGL Sample",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		NULL);
}

OpenglWindow::~OpenglWindow()
{
	DestroyWindow(hwnd);
}

void OpenglWindow::EnableOpenGL()
{
	PIXELFORMATDESCRIPTOR pfd;

	int iFormat;

	/* get the device context (DC) */
	hDC = GetDC(hwnd);

	/* set the pixel format for the DC */
	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	iFormat = ChoosePixelFormat(hDC, &pfd);

	SetPixelFormat(hDC, iFormat, &pfd);

	/* create and enable the render context (RC) */
	hRC = wglCreateContext(hDC);

	wglMakeCurrent(hDC, hRC);
	gladLoadGLLoader(GetAnyGLFuncAddress);
	isOpenglEnabled = true;
}

void OpenglWindow::DisableOpenGL()
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hwnd, hDC);
	isOpenglEnabled = false;
}

int OpenglWindow::exec()
{
	ShowWindow(hwnd, nCmdShow);
	MainLoop();
	return 0;
}

void OpenglWindow::MainLoop()
{
	while (!bQuit)
	{
		Time.TimerUpdate();
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			/* handle or dispatch messages */
			if (msg.message == WM_QUIT)
			{
				bQuit = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (isOpenglEnabled)
				Render(hDC);
		}

	}
}

