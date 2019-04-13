#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../EngineLib/engine.h"
#include <Windows.h>
//#pragma comment(lib,"../x64/Debug/EngineLib.lib")

#define WIN_WIDTH 800		
#define WIN_HEIGHT 600
enum FULLSCREEN{
	WIN, FULL
};

class GameManager{
private:
	//AudioManager audioManager;
	RenderInterface* gameRender;
	HWND hWnd = NULL;
	IDirect3DDevice9* device;
	CD3DUIManager* GUI;
public:
	GameManager()=default;
	~GameManager()=default;

	//��ʼ������
	void CreateWnd(HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc);
	//��ʼ������,��ʼ��D3D��Ⱦ�ӿڶ���
	bool InitEngine(FULLSCREEN show);
	//��ʼ����Ϸ,���Գ�ʼ����Ϸ��ʼ��Դ
	bool InitGame();
	//��ʼ��Ϸѭ��
	void GameLoop();
	//������Ϸѭ��
	void EndLoop();
	//
	void LoadScene();

	//����UI ��Ҫ��Ϊ������UI,��Ϸ��UI,��Ϸ�˳�UI
	void CreateUI(UIType type);
	//UI�Ĵ��ڻص������ȵ�,����Ҫ�Ž�UIManager����
	void ProcessGUI(bool LMBDown, int MouseX, int mouseY, void(*funcPtr)(int id, int state));
	void CloseGame() {};
	void CloseEngine() {};
	HWND GetHwnd() {
		return hWnd;
	}
};



#endif // !GAMEMANAGER_H
#pragma once
