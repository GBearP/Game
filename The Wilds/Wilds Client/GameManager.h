#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../EngineLib/engine.h"
#include <Windows.h>
//#pragma comment(lib,"../x64/Debug/EngineLib.lib")

#define WIN_WIDTH 800		
#define WIN_HEIGHT 600

#define GUI_MAIN_SCREEN 1
#define GUI_START_SCREEN 2
#define GUI_CREDITS_SCREEN 3

#define STATIC_TEXT_ID 1
#define BUTTTON_START_ID 2
#define BUTTON_CREDITS_ID 3
#define BUTTON_QUIT_ID 4
#define BUTTON_BACK_ID 5
#define BUTTON_LEVEL_1 6
//





/*************************************************************/
class GameManager {
private:
	//AudioManager audioManager;
	HWND hWnd = NULL;
	SCREENMODE show = WIN;

	int g_mainGUI = -1;
	int g_startGUI = -1;
	int g_creditGUI = -1;
	int g_currentGUI = GUI_MAIN_SCREEN;
	int arialID = -1;
public:
	RenderInterface* gameRender = NULL;
	GameManager() = default;
	~GameManager() = default;

	//初始化窗口
	void CreateWnd(HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc);
	//初始化引擎,初始化D3D渲染接口对象
	bool InitEngine();
	//初始化游戏,用以初始化游戏初始资源
	bool InitGame();
	//开始游戏循环
	void GameLoop();
	//结束游戏循环
	void EndLoop(){ gameRender->EndRender(); }
	void LoadScene();

	void CloseGame() {};
	void CloseEngine() {};
	HWND GetHwnd() {
		return hWnd;
	}
	RenderInterface* GetGameRender() {
		return gameRender;
	}
	bool CreateRender();

	/*****************  UI *******************/
	bool InitMainMenu() {
		if (!gameRender->CreateText(L"Arial", 18, 12, true, 10, arialID)) {
			MessageBox(0, 0, L"CreateTextError", 0);
			return false;
		}
		if (!gameRender->CreateGUI(g_mainGUI)) {
			MessageBox(0, 0, L"CreateGUI ERROR", 0);
			return false;
		}
		//完整的文件
		if (!gameRender->CreateGUI(g_mainGUI)) {
			MessageBox(0, 0, L"CreateGUI ERROR", 0);
			return false;
		}
		if (!gameRender->AddGUIBackTexure(g_mainGUI, L"EnterUI.jpg")) {
			MessageBox(0, 0, L"AddBackTexture ERROR", 0);
			return false;
		}
		return true;
	}
	void MainMenuRender() {
		if (g_currentGUI == GUI_MAIN_SCREEN)
		{
			MessageBox(0, 0, L"2t", 9);
			//gameRender->ProcessGUI(g_mainGUI, LMBDown, mouseX, mouseY, NULL);
		}
	}
	void MainCallback(int id, int state) {

	}
	/*void SetCursorState(int x, int y,int t_LMBDown) {
		mouseX = x;
		mouseY = y;
		int LMBDown = t_LMBDown;
	}*/
};



#endif // !GAMEMANAGER_H
#pragma once
