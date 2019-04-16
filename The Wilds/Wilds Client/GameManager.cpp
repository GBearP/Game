#include"GameManager.h"
//初始化窗口
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
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
}
//初始化引擎//
bool GameManager::InitEngine(FULLSCREEN show) {
	if (!CreateRender()) return false;
	if (!gameRender->Initialize(WIN_WIDTH, WIN_HEIGHT, hWnd, show)) {
		return false;
	}
	gameRender->SetBackColor(0, 0, 0);
	return true;
};
//初始化游戏
bool GameManager::InitGame() {
	device = (IDirect3DDevice9*)(gameRender->GetDevice());
	return true;
}
//开始游戏循环
void GameManager::GameLoop() {
	if (!gameRender) {
		return;
	}
	gameRender-> ClearBuffer(1, 1, 0);
	//gameRender->ClearBuffer();  //如果有必要,渲染开始时清除缓存
	//游戏内循环,模型,灯光,贴图在这里添加
}
void GameManager::EndLoop() {
	gameRender->EndRender();
};
void InitMainMenu() {
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