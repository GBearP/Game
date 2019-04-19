#pragma once
#ifndef D3DRENDER_H
#define D3DRENDER_H

#include "RenderInterface.h"
#include<d3d9.h>
#include<d3dx9.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

enum SCREENMODE
{
	WIN, FULL
};

#define D3DFVF_GUI (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
//用以存储图元信息
struct StaticPrimitiveBuffer {
	StaticPrimitiveBuffer() :pt_VertexBuffer(0), pt_IndexBuffer(0), numVertexs(0), numIndex(0), fvf(0), primType(NULL_TYPE) {}
	LPDIRECT3DVERTEXBUFFER9 pt_VertexBuffer;//顶点缓存指针
	LPDIRECT3DINDEXBUFFER9  pt_IndexBuffer;//索引缓存指针
	unsigned int numVertexs; //顶点数量
	unsigned int numIndex; //索引数量
	int stride;
	unsigned long fvf;//灵活顶点模式
	PrimType primType;//图元类型 三角、线等
};

//用以存储贴图信息
struct meshTexture{
	WCHAR* fileName;
	int width, height;
	IDirect3DTexture9* image;
};



//继承于RenderInterface的接口,实现DirectX渲染,如果用OpenGL,则新建OpenGLRender
class D3DRender :public RenderInterface
{
private:
	LPDIRECT3D9 m_Direct3D;
	LPDIRECT3DDEVICE9 m_Direct3DDevice;

	//图元列表
	StaticPrimitiveBuffer* m_StaticBufferList;
	int m_StaticBufferCount;
	int m_ActiveBufferCount;
	
	//贴图列表和材质计数
	meshTexture* m_textureList;
	D3DCOLOR m_color;
	unsigned int m_TextureCount;
	D3DMATERIAL9* m_materialList;
	
	//灯光列表
	D3DLIGHT9* lightList;
	
	//字体列表
	LPD3DXFONT* fontList;

	bool m_rengderingScene;
public:
	D3DRender();
	~D3DRender();

	//初始化3步
	bool Initialize(int w, int h, WinHWND wh, int fullScreen);//创建D3D设备
	void OneTimeInit();//设置初始渲染状态
	void SetBackColor(float r, float g, float b);
	
	//创建静态缓存
	bool CreateStaticBuffer(Vertextype vTpye, PrimType primType, int totalVertex, int totalIndices, int stride, void** data, unsigned int* indices, int* staticID);

	//GUI部分
	int AddTexture2D(LPCWSTR file, int* texID);
	void ApplyTexture(int index, int texID);
	virtual int GetScreenWidth();
	virtual	int GetScreenHeight();
	virtual bool CreateGUI(int& id);
	virtual bool AddGUIBackTexure(int id_GUI, LPCWSTR fileName);
	virtual bool AddGUIStaticText(int id_GUI, int id, LPCWSTR text, int x, int y, unsigned long color, int fontID);
	virtual bool AddGUIButton(int id_GUI, int id, int x, int y, LPCWSTR up, LPCWSTR over, LPCWSTR down);
	virtual void ProcessGUI(int id_GUI, bool LMBDwon, int mouseX, int mouseY, void(*funcPtr)(int id, int state));
	virtual bool CreateText(LPCWSTR font, int weigth, int heigth, bool italic, int size, int &id) ;
	virtual void DisplayText(int id, long x, long y, int r, int g, int b, LPCWSTR text, ...) ;
	virtual void DisplayText(int id, long x, long y, unsigned long color, LPCWSTR text, ...) ;

	//渲染所需的设置灯光,材质,贴图的方法
	void SetMaterial(dxMaterial* mat);
	void SetLight(dxLight* light, int lightIndex);
	void DisableLight(int index);
	void SetTextureFilter(int index, int filter, int val);
	void SetTranspancy(RenderState state, TransState src, TransState dst);
	void EnablePointSprites(float size, float min, float a, float b, float c);
	void DisableSprites();
	void SetMultiTexture();
	void SaveScreenShot(wchar_t* file);

	//渲染的设置
	void CalculateProjMatrix(float fov, float n, float f);
	void CalculateOrhtojMatrix(float n, float f);
	void StartRender(bool bColor, bool bDepth, bool bstencil);
	void EndRender();
	void ClearBuffer(bool bColor, bool bDepth, bool bstencil);
	void ShutDown();
	void Render(int staticID);
};


#endif
