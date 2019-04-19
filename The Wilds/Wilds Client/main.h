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
//��ʼ����Ϸ,���Գ�ʼ����Ϸ��ʼ��Դ
bool InitGame();
//��ʼ��Ϸѭ��
void GameLoop();
//������Ϸѭ��
void CloseGame();
void CloseEngine();
//bool CreateRender();
void CreateWnd(HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc);

#endif // !MAIN_H
