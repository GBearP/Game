#include <Windows.h>
#include"GameManager.h"

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
bool LMBDown = -1;
int mouseX = 0, mouseY = 0;
wchar_t* fontType = (wchar_t*)L"Arial";
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

bool InitMainMenu(GameManager& gameManager) {
	if (!gameManager.GetGameRender()->CreateText(fontType,18,12,true,10,arialID))
	{
		MessageBox(0, 0,L"CreateTextError", 0);
		return false;
	}
	if (!gameManager.GetGameRender()->CreateGUI(g_mainGUI)) {
		MessageBox(0, 0, L"CreateGUIError", 0);
		return false;
	}

	if (!gameManager.GetGameRender()->AddGUIBackTexure(g_mainGUI, (wchar_t*)L"EnterUI.jpg")) {
		if (!gameManager.GetGameRender()->GetGUIList())
		{
			MessageBox(0, 0, L"GUIListNull", 0);
		}
		MessageBox(0, 0,L"AddGUIBackTexureERROR",0);
		return false;
	}
	return true;
}
void MainMenuRender(GameManager& gameManager) {
	if (g_currentGUI==GUI_MAIN_SCREEN)
	{
		gameManager.GetGameRender()->ProcessGUI(g_mainGUI, LMBDown, mouseX, mouseY, NULL);
	}
}
void MainCallback(int id,int state) {

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow) {
	 
	//初始化WndClass、注册、生成窗口
	GameManager gameManager;
	gameManager.CreateWnd(hInstance,nCmdShow,WndProc);


	//初始化游戏后开始消息循环
	if (gameManager.InitEngine(WIN)&&gameManager.InitGame())
	{
		InitMainMenu(gameManager);
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));

		while (msg.message != WM_QUIT) {
			if (PeekMessage(&msg,gameManager.GetHwnd(), NULL, NULL, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else{
				gameManager.GameLoop();
		//gameManager.ProcessGUI(0,0,0,NULL);
				gameManager.EndLoop();
			}
		}
		return (int)msg.wParam;
	}
	gameManager.CloseGame();
	gameManager.CloseEngine();
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

