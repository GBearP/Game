#pragma once
#ifndef D3DRENDER_H
#define D3DRENDER_H

#include "RenderInterface.h"
#include<d3d9.h>
#include<d3dx9.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

//用以存储图元信息
struct StaticVertexBuffer {
	StaticVertexBuffer() :pt_VertexBuffer(0), pt_IndexBuffer(0), numVertexs(0), numIndex(0), fvf(0), primType(NULL_TYPE) {}
	LPDIRECT3DVERTEXBUFFER9 pt_VertexBuffer;//顶点缓存指针
	LPDIRECT3DINDEXBUFFER9  pt_IndexBuffer;//索引缓存指针
	int numVertexs; //顶点数量
	int numIndex; //索引缓存数量
	int stride;
	unsigned long fvf;//灵活顶点模式
	PrimType primType;//图元类型 三角、线等

};

//用以存储贴图信息
struct meshTexture
{
	wchar_t* fileName;
	int width, height;
	IDirect3DTexture9* image;
};

bool CreateD3DRender(RenderInterface** g_Render);


//继承于RenderInterface的接口,实现DirectX渲染,如果用OpenGL,则新建OpenGLRender
class D3DRender :public RenderInterface
{
private:
	StaticVertexBuffer* m_StaticBufferList;
	meshTexture* m_texture;
	D3DCOLOR m_color;
	D3DMATERIAL9* m_materialList;
	D3DLIGHT9* lightList;

	LPDIRECT3D9 m_Direct3D;
	LPDIRECT3DDEVICE9 m_Direct3DDevice;
	bool m_rengderingScene;
	int m_StaticBufferCount;
	int m_ActiveBufferCount;
	unsigned int m_TexturesCount;

public:
	D3DRender();
	~D3DRender();

	void* GetDevice() { return m_Direct3DDevice; }
	bool Initialize(int w, int h, WinHWND wh, int fullScreen);//创建D3D设备
	void OneTimeInit();//设置初始渲染状态
	void SetBackColor(float r, float g, float b);
	
	//渲染所需的设置灯光,材质,贴图的方法
	void CalculateProjMatrix(float fov, float n, float f);
	void CalculateOrhtojMatrix(float n, float f);
	void StartRender(bool bColor, bool bDepth, bool bstencil);
	void EndRender();
	void ClearBuffer(bool bColor, bool bDepth, bool bstencil);
	void CreateStaticBuffer(Vertextype vTpye, PrimType primType, int totalVertex, int totalIndices, int stride, void** data, unsigned int* indices, int* staticID);
	void ShutDown();
	void Render(int staticID);
	void SetMaterial(dxMaterial* mat);
	void SetLight(dxLight* light, int lightIndex);
	void DisableLight(int index);
	void SetTranspancy(RenderState state, TransState src, TransState dst);
	int AddTexture2D(wchar_t* file, int* texID);
	void SetTextureFilter(int index, int filter, int val);
	void SetMultiTexture();
	void ApplyTexture(int index, int texID);
	void SaveScreenShot(wchar_t* file);
	void EnablePointSprites(float size, float min, float a, float b, float c);
	void DisableSprites();
	virtual int GetScreenWidth();
	virtual	int GetScreenHeight();
};


#endif
