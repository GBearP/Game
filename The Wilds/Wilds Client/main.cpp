#include <Windows.h>
#include"GameManager.h"


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void (*p_DealUI)();
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow) {
	 
	//��ʼ��WndClass��ע�ᡢ���ɴ���
	GameManager gameManager;
	gameManager.CreateWnd(hInstance,nCmdShow,WndProc);

	//��ʼ����Ϸ��ʼ��Ϣѭ��
	if (gameManager.InitEngine()&&gameManager.InitGame())
	{
		gameManager.InitMainMenu();
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));

		while (msg.message != WM_QUIT) {
			if (PeekMessage(&msg,gameManager.GetHwnd(), NULL, NULL, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else{
				gameManager.GameLoop();
				gameManager.MainMenuRender();
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


//�¼��ص�����
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		/*hdc = BeginPaint(hWnd, &ps);

		
		EndPaint(hWnd, &ps);*/
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		//p_DealUI();
		break;
	case WM_MOUSEMOVE:
		//p_DealUI();
		break;
	case WM_KEYUP:
		if (wParam == VK_ESCAPE)PostQuitMessage(0);
		break;
	case WM_LBUTTONUP:
		//p_DealUI();
		//LMBDown = false;
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

