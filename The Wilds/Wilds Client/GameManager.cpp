#include"GameManager.h"
//初始化窗口
//初始化引擎//
bool GameManager::InitEngine(SCREENMODE show) {
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