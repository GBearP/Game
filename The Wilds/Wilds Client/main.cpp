#include <Windows.h>
//#include"GameManager.h"

#include "../EngineLib/engine.h"
#include <Windows.h>
#include"main.h"


#define GUI_MAIN_SCREEN 1
#define GUI_START_SCREEN 2
#define GUI_CREDITS_SCREEN 3

#define STATIC_TEXT_ID 1
#define BUTTTON_START_ID 2
#define BUTTON_CREDITS_ID 3
#define BUTTON_QUIT_ID 4
#define BUTTON_BACK_ID 5
#define BUTTON_LEVEL_1 6

int g_mainGUI = -1;
int g_startGUI = -1;
int g_creditGUI = -1;
int g_currentGUI = GUI_MAIN_SCREEN;

int arialID = -1;
int LMBDown = -1;
int mouseX = 0, mouseY = 0;
wchar_t* fontType = (wchar_t*)L"Arial";
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

RenderInterface* gameRender;
HWND hWnd = NULL;
//bool InitMainMenu(GameManager& gameManager) {
//	if (!gameManager.GetGameRender()->CreateText(fontType,18,12,true,10,arialID)){
//		MessageBox(0, 0,L"CreateTextError", 0);
//		return false;
//	}
//	if (!gameManager.GetGameRender()->CreateGUI(g_mainGUI)) {
//		return false;
//	}
//
//	if (!gameManager.GetGameRender()->AddGUIBackTexure(g_mainGUI, L"EnterUI.jpg")) {
//		return false;
//	}
//	return true;
//}
//void MainMenuRender(GameManager& gameManager) {
//	if (g_currentGUI==GUI_MAIN_SCREEN)
//	{
//		gameManager.GetGameRender()->ProcessGUI(g_mainGUI, LMBDown, mouseX, mouseY, NULL);
//	}
//}
//void MainCallback(int id,int state) {
//
//}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow) {
	 
	//初始化WndClass、注册、生成窗口
	CreateWnd(hInstance, nCmdShow, WndProc);

	//初始化游戏后开始消息循环
	if (InitEngine(SCREENMODE::WIN)&&InitGame())
	{

		MSG msg;
		ZeroMemory(&msg, sizeof(msg));

		while (msg.message != WM_QUIT) {
			if (PeekMessage(&msg, NULL, NULL,0U, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else{
				GameLoop();
			}
		}
		return (int)msg.wParam;
	}
	CloseGame();
	CloseEngine();
	UnregisterClass(WINDOW_CLASS, hInstance);
	return 0;
}


//事件回调处理
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		LMBDown = true;
		break;
	case WM_MOUSEMOVE:
		mouseX = LOWORD(lParam);
		mouseY = HIWORD(lParam);
		break;
	case WM_KEYUP:
		if (wParam == VK_ESCAPE)PostQuitMessage(0);
		break;
	case WM_LBUTTONUP:
		LMBDown = false;
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void CreateWnd(HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc) {
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
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
}

bool InitEngine(SCREENMODE show) {
	if (!CreateRender(&gameRender)) return false;
	if (!gameRender->Initialize(WIN_WIDTH, WIN_HEIGHT, hWnd, show)) {
		return false;
	}
	gameRender->SetBackColor(0, 0, 0);
	return true;
};
bool CreateRender(RenderInterface* gameRender) {

	if (!gameRender) {
		gameRender = new D3DRender();
		if (!gameRender)return false;
	}
	return true;
}

bool InitGame() {
	return true;
}

void CloseGame() {

}

void CloseEngine() {
	if (!gameRender){
		return;
	}
	gameRender->ShutDown();
	delete gameRender;
	gameRender = NULL;
}