#include<Windows.h>

#define WINDOW_CLASS TEXT("Maid")
#define WINDOW_NAME TEXT("FBK")
typedef struct _Myarea {
	int x, y, w, h;
}Myarea;
const int WIN_WIDTH = 300;
const int WIN_HEIGHT = 300;

static HBITMAP pBitMap;
HWND hWnd;
Myarea area;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hDc = GetDC(NULL);//获取客户区窗口，如果该值为NULL，GetDC则获整个屏幕的窗口。	
	switch (message)
	{
	case WM_CREATE:
		SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_CAPTION);
		SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_DRAWFRAME);
		area.x = ps.rcPaint.left;
		area.y = ps.rcPaint.top;
		area.w = ps.rcPaint.right - area.x;
		area.h = ps.rcPaint.bottom - area.y;
		
		break;
	case WM_PAINT:
		HBITMAP hBitmap = CreateCompatibleBitmap(hDc, 700, 600);//创建一个兼容的位图
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:


		break;
	case WM_MOUSEMOVE:

		break;
	case WM_KEYUP:
		if (wParam == VK_ESCAPE)PostQuitMessage(0);
		break;
	case WM_LBUTTONUP:

		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

int CreateWnd(HINSTANCE, int);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR scCmdLine, int nCmdShow) {
	CreateWnd(hInstance, nCmdShow);

		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT) {
			if (PeekMessage(&msg, hWnd, NULL, NULL, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			///TODO
			
		}
		return 0;
}

int CreateWnd(HINSTANCE hInstance, int nCmdShow) {
	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_CLASSDC;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = WINDOW_CLASS;
	wndClass.hIconSm = LoadIcon(wndClass.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wndClass)) {
		MessageBox(0, L"RegisterClassError", 0, 0);
	}

	if (nCmdShow) {
		hWnd = CreateWindow(WINDOW_CLASS, WINDOW_NAME, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, WIN_WIDTH, WIN_HEIGHT, NULL, NULL, hInstance, NULL);
	}
	else {
		hWnd = CreateWindow(WINDOW_CLASS, WINDOW_NAME, WS_POPUP | WS_VISIBLE | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, WIN_WIDTH, WIN_HEIGHT, NULL, NULL, hInstance, NULL);
	}
	if (!hWnd) {
		MessageBox(0, 0, L"hWnd is NULL", 0);
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return 1;
}

