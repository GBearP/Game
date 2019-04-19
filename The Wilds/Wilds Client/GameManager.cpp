#include"GameManager.h"
//��ʼ������
void GameManager::CreateWnd(HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc) {
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
	if (!hWnd){
		MessageBox(0, 0, L"hWnd is NULL", 0);
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
}
//��ʼ������//
bool GameManager::InitEngine() {
	if (!CreateRender()) return false;
	if (!gameRender->Initialize(WIN_WIDTH, WIN_HEIGHT, hWnd, show)) {
		return false;
	}
	gameRender->SetBackColor(0.2f, 0.2f, 0.2f);
	return true;
};
//��ʼ����Ϸ
bool GameManager::InitGame() {
	//device = (IDirect3DDevice9*)(gameRender->GetDevice());
	return true;
}
//��ʼ��Ϸѭ��
void GameManager::GameLoop() {
	if (!gameRender) {
		return;
	}
	//����б�Ҫ,��Ⱦ��ʼʱ�������
	//gameRender-> ClearBuffer(1, 1, 0);
	gameRender->StartRender(1, 1, 0);
	//��Ϸ��ѭ��,ģ��,�ƹ�,��ͼ�������������
}


void GameManager::LoadScene() {

}


bool GameManager::CreateRender() {

	if (!gameRender) {
		gameRender = new D3DRender();
		if (!gameRender)return false;
	}
	return true;
}


/*******************************/
