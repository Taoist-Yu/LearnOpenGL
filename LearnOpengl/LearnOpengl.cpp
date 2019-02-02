#include "OpenglWindow.h"
#include "Time.h"
#include "Text.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

LRESULT CALLBACK  WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void RenderProc(HDC hDC);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	OpenglWindow wnd(hInstance, nCmdShow,WindowProc,RenderProc);
	wnd.EnableOpenGL();
	return wnd.exec();
}

LRESULT CALLBACK  WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

void RenderProc(HDC hDC)
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
	Text::Draw(frametext, 0.8, 0.9,glm::vec3(1,0,0));

	SwapBuffers(hDC);
}

