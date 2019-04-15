#pragma once
#ifndef RENDERINTERFACE_H
#define RENDERINTERFACE_H

#include "defines.h"
#include<Windows.h>
#include"light.h"
#include"material.h"
#include"GUI.h"
//抽象类的定义,如果用DirectX接口,则继承该类实现,如果用OpenGL接口,则继承之后另外实现.
class RenderInterface
{
public:
	RenderInterface() :m_screenWitdth(0), m_screenHeight(0), m_full(0), m_near(0), m_far(0) {}
	virtual void* GetDevice() = 0;
	virtual ~RenderInterface() {}
	virtual bool Initialize(int w, int h, WinHWND wh, int fullScreen) = 0;
	virtual void OneTimeInit() = 0;
	virtual void CalculateProjMatrix(float fov, float n, float f) = 0;
	virtual void CalculateOrhtojMatrix(float n, float f) = 0;
	virtual void SetBackColor(float r, float g, float b) = 0;
	virtual void StartRender(bool bColor, bool bDepth, bool bstencil) = 0;
	virtual void EndRender() = 0;
	virtual void ClearBuffer(bool bColor, bool bDepth, bool bstencil) = 0;
	virtual bool CreateStaticBuffer(Vertextype vTpye, PrimType primType, int totalVertex, int totalIndices, int stride, void** data, unsigned int* indices, int* staticID) = 0;
	virtual void ShutDown() = 0;
	virtual void Render(int staticID) = 0;//staticID是静态缓存链表的下标
	virtual void SetMaterial(dxMaterial* mat) = 0;
	virtual void SetLight(dxLight* light, int lightIndex) = 0;
	virtual void DisableLight(int index) = 0;
	virtual void SetTranspancy(RenderState state, TransState src, TransState dst) = 0;
	virtual int AddTexture2D(wchar_t* file, int* texID) = 0;
	virtual void SetTextureFilter(int index, int filter, int val) = 0;
	virtual void SetMultiTexture() = 0;
	virtual void ApplyTexture(int index, int texID) = 0;
	virtual void SaveScreenShot(wchar_t* file) = 0;
	virtual void EnablePointSprites(float size, float min, float a, float b, float c) = 0;
	virtual void DisableSprites() = 0;
	virtual int GetScreenWidth()=0;
	virtual	int GetScreenHeight() = 0;
	virtual bool CreateGUI(int& id)=0;
	virtual bool AddGUIBackTexure(int GUIID,WCHAR* fileName)=0;
	virtual bool AddGUIStaticText(int GUIID, int id, WCHAR* text, int x, int y, unsigned long color, int fontID) = 0;
	virtual bool AddGUIButton(int GUIID, int id, int x, int y, WCHAR* up, WCHAR* over, WCHAR* down) = 0;
	virtual void ProcessGUI(int GUIID, bool LMBDwon, int mouseX, int mouseY, void(*funcPtr)(int id, int state)) = 0;
	virtual bool CreateText(WCHAR* font, int weigth, int heigth, bool italic, int size, int &id) = 0;
	virtual void DisplayText(int id, long x, long y, int r, int g, int b, WCHAR* text, ...) = 0;
	virtual void DisplayText(int id,long x,long y,unsigned long color,WCHAR* text,...)=0;

protected:
	int m_screenWitdth;
	int m_screenHeight;
	bool m_full;
	WinHWND m_mainHandle;
	float m_near;
	float m_far;
	GUISystem* GUIList;
	int GUICount;
	int fontCount;
};

#endif

