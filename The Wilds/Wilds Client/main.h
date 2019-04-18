#pragma once
#ifndef MAIN_H
#define MAIN_H

#define WIN_WIDTH 800		
#define WIN_HEIGHT 600
#define WINDOW_CLASS L"The Wilds"
#define WINDOW_NAME L"Wilds"

enum SCREENMODE{
	WIN,FULL
};

bool InitEngine(SCREENMODE show);
//初始化游戏,用以初始化游戏初始资源
bool InitGame();
//开始游戏循环
void GameLoop();
//结束游戏循环
void CloseGame();
void CloseEngine();
//bool CreateRender();
void CreateWnd(HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc);

#endif // !MAIN_H
