#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../EngineLib/engine.h"
#include <Windows.h>
//#pragma comment(lib,"../x64/Debug/EngineLib.lib")

#define WIN_WIDTH 800		
#define WIN_HEIGHT 600


class GameManager {
private:
	//AudioManager audioManager;
	RenderInterface* gameRender;
	HWND hWnd = NULL;
	//IDirect3DDevice9* device;
	
public:
	GameManager() = default;
	~GameManager() = default;

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

	HWND GetHwnd() {
		return hWnd;
	}
	IDirect3DDevice9* GetDevice() {
		return device;
	}
	RenderInterface* GetGameRender() {
		return gameRender;
	}
	bool CreateRender();
};



#endif // !GAMEMANAGER_H
#pragma once
