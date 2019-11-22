#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

float r = 1, g = 0, b = 0;
float points[4][2] = {
	{-0.1f, 0.05f}, {0.1f, 0.05f}, {0.1f, -0.05f}, {-0.1f, -0.05f}
};
float spd = 0, acc = 0, lvl = 0;

float xDeg = 0, yTrans = 0;

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
		case VK_UP:
			xDeg += 1;
			break;
		case VK_DOWN:
			xDeg -= 1;
			break;
		case VK_LEFT:
			// Speed cap
			if (acc < 0.5)
			{
				acc += 0.05f;
			}
			break;
		case VK_RIGHT:
			// Speed cap
			if (acc > -0.5)
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
		glVertex3f(0, 0.2f, 0.9f);
		glVertex3f(0.1f, 0.15f, 0.9f);
		glVertex3f(0.2f, 0.1f, 0.9f);
		glVertex3f(0.25f, 0.12f, 0.9f);
		glVertex3f(0.3f, 0, 0.9f);
		glVertex3f(0.26f, -0.03f, 0.9f);
		glVertex3f(0.2f, -0.05f, 0.9f);
		glVertex3f(0.15F, -0.1f, 0.9f);
		glVertex3f(0.06f, -0.09f, 0.9f);
		glVertex3f(0, -0.15f, 0.9f);
		glVertex3f(-0.1f, -0.15f, 0.9f);
		glVertex3f(-0.15f, -0.1f, 0.9f);
		glVertex3f(-0.2f, 0, 0.9f);
		glVertex3f(-0.2f, 0.02f, 0.9f);
		glVertex3f(-0.18f, 0.05f, 0.9f);
		glVertex3f(-0.13f, 0.15f, 0.9f);
	}
	glEnd();
}

void myBone(float xDeg, float zDeg)
{
	glPushMatrix();
	glColor3ub(59, 37, 0);
	glTranslatef(0, yTrans, 0);
	glRotatef(xDeg, 1, 0, 0);
	glRotatef(zDeg, 0, 0, 1);
	glLineWidth(5);
	glBegin(GL_LINE_LOOP);
	{
		glVertex3f(0, 0.8f, -0.31f);
		glVertex3f(0, 0, -0.31f);
	}
	glEnd();
	glPopMatrix();
}

void myBlade(float xDeg, float zDeg)
{
	glPushMatrix();
	glColor3ub(230, 230, 230);
	glTranslatef(0, yTrans, 0);
	glRotatef(xDeg, 1, 0, 0);
	glRotatef(zDeg, 0, 0, 1);
	glBegin(GL_QUADS);
	{
		glVertex3f(-0.1f, 0.8f, -0.3f);
		glVertex3f(0.1f, 0.8f, -0.3f);
		glVertex3f(0.1f, 0.15f, -0.3f);
		glVertex3f(-0.1f, 0.15f, -0.3f);
	}
	glEnd();
	glPopMatrix();
}

void mySpinner(float xDeg, float zDeg)
{
	glPushMatrix();
	glColor3ub(59, 37, 0);
	glTranslatef(0, yTrans, 0);
	glRotatef(xDeg, 1, 0, 0);
	glRotatef(zDeg, 0, 0, 1);
	glBegin(GL_QUADS);
	{
		glVertex3f(-0.05f, 0.05f, -0.311f);
		glVertex3f(0.05f, 0.05f, -0.311f);
		glVertex3f(0.05f, -0.05f, -0.311f);
		glVertex3f(-0.05f, -0.05f, -0.311f);
	}
	glEnd();
	glPopMatrix();
}

void myBuilding()
{
	glTranslatef(0, yTrans, 0);

	glColor3ub(207, 185, 116);
	glBegin(GL_TRIANGLE_FAN);
	double PI = 3.141592654;
	double angle = 0.0;
	double radius = 0.3f;
	int points = 120;
	for (int i = 0; i < points; i++) {
		angle = PI * i / points;
		glVertex2f((float)cos(angle) * radius, (float)sin(angle) * radius);
	}
	glEnd();

	glColor3ub(207, 185, 116);
	glBegin(GL_QUADS);
	{
		glVertex3f(0.3f, -0.2f, 0);
		glVertex3f(0.3f, 0.03f, 0);
		glVertex3f(-0.3f, 0.03f, 0);
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
	glClearColor(0, 167, 209, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	if (xDeg >= 87 && yTrans < 2 && abs(acc) >= 0.35) {
		yTrans += 0.005f;
	}

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
	myBlade(xDeg, 0 + spd);
	myBlade(xDeg, 90 + spd);
	myBlade(xDeg, 180 + spd);
	myBlade(xDeg, 270 + spd);

	// Draw Bones
	myBone(xDeg, 0 + spd);
	myBone(xDeg, 90 + spd);
	myBone(xDeg, 180 + spd);
	myBone(xDeg, 270 + spd);

	// Draw Spinner
	mySpinner(xDeg, 0 + spd);

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
