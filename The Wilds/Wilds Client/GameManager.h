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

	//初始化窗口
	void CreateWnd(HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc);
	//初始化引擎,初始化D3D渲染接口对象
	bool InitEngine(FULLSCREEN show);
	//初始化游戏,用以初始化游戏初始资源
	bool InitGame();
	//开始游戏循环
	void GameLoop();
	//结束游戏循环
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
