#include"GameManager.h"
//��ʼ������
//��ʼ������//
bool GameManager::InitEngine(SCREENMODE show) {
	if (!CreateRender()) return false;
	if (!gameRender->Initialize(WIN_WIDTH, WIN_HEIGHT, hWnd, show)) {
		return false;
	}
	gameRender->SetBackColor(0, 0, 0);
	return true;
};
//��ʼ����Ϸ
bool GameManager::InitGame() {
	device = (IDirect3DDevice9*)(gameRender->GetDevice());
	return true;
}
//��ʼ��Ϸѭ��
void GameManager::GameLoop() {
	if (!gameRender) {
		return;
	}
	gameRender-> ClearBuffer(1, 1, 0);
	//gameRender->ClearBuffer();  //����б�Ҫ,��Ⱦ��ʼʱ�������
	//��Ϸ��ѭ��,ģ��,�ƹ�,��ͼ���������
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