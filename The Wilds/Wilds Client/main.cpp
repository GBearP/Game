#include <Windows.h>
#include"GameManager.h"

bool LMBDown = false;

bool LMBDown = false;
int mouseX = 0, mouseY = 0;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow) {
	 
	//初始化WndClass、注册、生成窗口
	GameManager gameManager;
	gameManager.CreateWnd(hInstance,nCmdShow,WndProc);


	//初始化游戏后开始消息循环
	if (gameManager.InitEngine(WIN)&&gameManager.InitGame())
	{
		gameManager.CreateUI(ENTER);
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
	case WM_KEYUP:
		if (wParam==VK_ESCAPE) PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		//按下状态为true;
		LMBDown = true;
	case WM_LBUTTONUP:
		LMBDown = false;
		break;
	case WM_MOUSEMOVE:
		mouseX = HIWORD(lParam);
		mouseY = LOWORD(lParam);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}



