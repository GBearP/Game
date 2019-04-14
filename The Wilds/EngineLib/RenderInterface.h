#pragma once
#ifndef RENDERINTERFACE_H
#define RENDERINTERFACE_H

#include "defines.h"
#include<Windows.h>
#include"light.h"
#include"material.h"

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
	virtual void CreateStaticBuffer(Vertextype vTpye, PrimType primType, int totalVertex, int totalIndices, int stride, void** data, unsigned int* indices, int* staticID) = 0;
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

	//创建UI 主要分为主界面UI,游戏中UI,游戏退出UI
	virtual void CreateUI(UIType type) = 0;
	virtual void CreateText(wchar_t* fontType, int id, bool set, int fontSize, int g_arialID) = 0;

protected:
	int m_screenWitdth;
	int m_screenHeight;
	bool m_full;
	WinHWND m_mainHandle;
	float m_near;
	float m_far;
};

#endif

