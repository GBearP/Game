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

	//创建UI 主要分为主界面UI,游戏中UI,游戏退出UI
	void CreateUI(UIType type);
	//UI的窗口回调函数等等,或许要放进UIManager类里
	void ProcessGUI(bool LMBDown, int MouseX, int mouseY, void(*funcPtr)(int id, int state));
	void CloseGame() {};
	void CloseEngine() {};
	HWND GetHwnd() {
		return hWnd;
	}
};



#endif // !GAMEMANAGER_H
#pragma once
