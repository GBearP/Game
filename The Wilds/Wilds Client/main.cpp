#include <Windows.h>
#include"GameManager.h"


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow) {
	 
	//��ʼ��WndClass��ע�ᡢ���ɴ���
	GameManager gameManager;
	gameManager.CreateWnd(hInstance,nCmdShow,WndProc);


	//��ʼ����Ϸ��ʼ��Ϣѭ��
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


//�¼��ص�����
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
		//����״̬Ϊtrue;
		break;
	case WM_MOUSEMOVE:
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
