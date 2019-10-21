#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include <conio.h>
#include <string>

//#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

float r = 1, g = 0, b = 0;
float points[4][2] = {
	{-0.1f, 0.05f}, {0.1f, 0.05f}, {0.1f, -0.05f}, {-0.1f, -0.05f}
};
float spd = 0, acc = 0, lvl = 0;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CHAR:
		switch (wParam)
		{
		case 0x52:
			r = 1.0f;
			g = 0;
			b = 0;
			break;
		case 0x47:
			r = 0;
			g = 1.0f;
			b = 0;
			break;
		case 0x42:
			r = 0;
			g = 0;
			b = 1.0f;
			break;
		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case VK_LEFT:
		case VK_UP:
			// Speed cap
			if (acc < 0.25)
			{
				acc += 0.05f;
			}
			break;
		case VK_RIGHT:
		case VK_DOWN:
			// Speed cap
			if (acc > -0.25)
			{
				acc -= 0.05f;
			}
			break;
		case VK_SPACE:
			acc = 0;
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void myCloud(float x_trans, float y_trans)
{
	glColor3ub(255, 255, 255);
	glTranslatef(x_trans, y_trans, 0);
	glBegin(GL_TRIANGLE_FAN);
	{
		glVertex2f(0, 0.2f);
		glVertex2f(0.1f, 0.15f);
		glVertex2f(0.2f, 0.1f);
		glVertex2f(0.25f, 0.12f);
		glVertex2f(0.3f, 0);
		glVertex2f(0.26f, -0.03f);
		glVertex2f(0.2f, -0.05f);
		glVertex2f(0.15F, -0.1f);
		glVertex2f(0.06f, -0.09f);
		glVertex2f(0, -0.15f);
		glVertex2f(-0.1f, -0.15f);
		glVertex2f(-0.15f, -0.1f);
		glVertex2f(-0.2f, 0);
		glVertex2f(-0.2f, 0.02f);
		glVertex2f(-0.18f, 0.05f);
		glVertex2f(-0.13f, 0.15f);
	}
	glEnd();
}

void myBone(float degree)
{
	glColor3ub(59, 37, 0);
	glLineWidth(5);
	glRotatef(degree, 0, 0, 1);
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(0, 0.8f);
		glVertex2f(0, -0.8f);
	}
	glEnd();
}

void myBlade(float degree)
{
	glColor3ub(230, 230, 230);
	glRotatef(degree, 0, 0, 1);
	glBegin(GL_QUADS);
	{
		glVertex3f(-0.1f, 0.8f, 0.5f);
		glVertex3f(0.1f, 0.8f, 0.5f);
		glVertex3f(0.1f, 0.15f, 0.5f);
		glVertex3f(-0.1f, 0.15f, 0.5f);
	}
	glEnd();
}

void mySpinner(float degree)
{
	glColor3ub(59, 37, 0);
	glRotatef(degree, 0, 0, 1);
	glBegin(GL_QUADS);
	{
		glVertex3f(-0.05f, 0.05f, 0);
		glVertex3f(0.05f, 0.05f, 0);
		glVertex3f(0.05f, -0.05f, 0);
		glVertex3f(-0.05f, -0.05f, 0);
	}
	glEnd();
}

void myBuilding()
{
	glColor3ub(107, 57, 0);
	glBegin(GL_QUADS);
	{
		glVertex3f(-0.15, 0.2f, 0);
		glVertex3f(0.15, 0.2f, 0);
		glVertex3f(0.3f, -0.2f, 0);
		glVertex3f(-0.3f, -0.2f, 0);
	}
	glEnd();

	glColor3ub(74, 39, 0);
	glBegin(GL_QUADS);
	{
		glVertex3f(0.3f, -0.2f, 0);
		glVertex3f(0.3f, -1.0f, 0);
		glVertex3f(-0.3f, -1.0f, 0);
		glVertex3f(-0.3f, -0.2f, 0);
	}
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 167, 209, 0);
	glMatrixMode(GL_MODELVIEW);
	
	/*
	Draw Cloud
	*/
	glLoadIdentity();
	myCloud(0.5f, 0.5f);
	glLoadIdentity();
	myCloud(-0.3f, 0.1f);
	glLoadIdentity();
	myCloud(-0.9f, 0.8f);

	/*
	Draw Building
	*/
	glLoadIdentity();
	myBuilding();

	// Draw blades
	glPushMatrix();
	myBlade(0 + spd);
	glPopMatrix();

	glPushMatrix();
	myBlade(90 + spd);
	glPopMatrix();

	glPushMatrix();
	myBlade(180 + spd);
	glPopMatrix();

	glPushMatrix();
	myBlade(270 + spd);
	glPopMatrix();

	// Draw Bones
	glPushMatrix();
	myBone(0 + spd);
	glPopMatrix();

	glPushMatrix();
	myBone(90 + spd);
	glPopMatrix();

	// Draw Spinner
	glPushMatrix();
	mySpinner(0 + spd);
	glPopMatrix();

	// Prevent the spd variable's value becaming too large due to acceleration by using modulus
	spd = fmod((spd + acc), 360.0f);
}

//--------------------------------------------------------------------

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prevInstance,
	_In_ LPSTR cmdLine, _In_ int nCmdShow) // FIXED
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------