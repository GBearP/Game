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
	if (!CreateD3DRender(&gameRender)) {
		return false;
	}
	if (!gameRender->Initialize(WIN_WIDTH, WIN_HEIGHT, hWnd, show)) {
		return false;
	}
	gameRender->SetBackColor(0, 0, 0);
	return true;
};
//初始化游戏
bool GameManager::InitGame() {
	device = (IDirect3DDevice9*)(gameRender->GetDevice());
	//GUI = new CD3DGUISystem(device, hWnd, WIN_WIDTH, WIN_HEIGHT);
	//UIManager.Show();
	return true;
}
//开始游戏循环
void GameManager::GameLoop() {
	if (!gameRender) {
		return;
	}
	gameRender->StartRender(1, 1, 0);
	//gameRender->ClearBuffer();  //如果有必要,渲染开始时清除缓存
	//游戏内循环,模型,灯光,贴图在这里添加
}
void GameManager::EndLoop() {
	gameRender->EndRender();
};
//bool LoadScene();

//创建UI,GameManagr::GUI指针每次只指向一个有效UI
void GameManager::CreateUI(UIType type) {

	switch (type)
	{
	case ENTER:
	if (GUI) { delete GUI; }
		GUI = new CD3DUIManager(WIN_WIDTH, WIN_HEIGHT);
		GUI->AddBackDrop(device, L"EnterUI.jpg");
		//创建字体
		//创建Button
   		break;
	case GAMING:
		delete GUI;
		GUI = new CD3DUIManager(WIN_WIDTH, WIN_WIDTH);
		GUI->AddBackDrop(device, L"GamingUI.jpg");
		//创建字体
		//创建Button
		break;
	case EXIT:
		delete GUI;
		GUI = new CD3DUIManager(300, 200);
		GUI->AddBackDrop(device, L"ExitUI.jpg");
		//创建字体
		//创建Button
		break;
	}
};
void GameManager::ProcessGUI(bool LMBDown, int MouseX, int mouseY, void(*funcPtr)(int id, int state)) {
	if (!device) {
		MessageBox(0, 0, L"No Device to processGUI;", 0);
		return;
	}
	IDirect3DTexture9* backDrop = GUI->GetBackDrop();
	IDirect3DVertexBuffer9* backBuffer = GUI->GetBackDropBuffer();
	if (GUI->UseBackDrop() && backDrop&&backBuffer) {

		device->SetTexture(0,backDrop);
		device->SetStreamSource(0, backBuffer, 0, sizeof(GUIVertex));
		device->SetFVF(D3DFVF_GUI);
		device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
		//device->SetTexture(0, NULL);
	}
	LPD3DXFONT pFont = NULL;
	RECT fontPositon = { 0,0,(long)(GUI->GetWinHeight()) };
	for (int i = 0; i < GUI->GetControlsCount(); i++) {

		GUIControl* pCnt = GUI->GetGUIControl(i);
		if (!pCnt) {
			continue;
		}

		switch (pCnt->m_type) {
		case STATICTEXT:
			pFont = GUI->GetFont(pCnt->m_listID);
			if (!pFont) {
				continue;
			}
			fontPositon.left = pCnt->m_xPos;
			fontPositon.top = pCnt->m_yPos;
			pFont->DrawText(NULL, pCnt->m_text[i], -1, &fontPositon, DT_LEFT, pCnt->m_color);
			MessageBox(0, 0, 0, 0);
			break;
		default:
			break;
		}
	}
}

void GameManager::LoadScene() {

}