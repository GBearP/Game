#pragma once
#ifndef D3DRENDER_H
#define D3DRENDER_H

#include "RenderInterface.h"
#include<d3d9.h>
#include<d3dx9.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

enum FULLSCREEN
{
	WIN, FULL
};

#define D3DFVF_GUI (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
//���Դ洢ͼԪ��Ϣ
struct StaticVertexBuffer {
	StaticVertexBuffer() :pt_VertexBuffer(0), pt_IndexBuffer(0), numVertexs(0), numIndex(0), fvf(0), primType(NULL_TYPE) {}
	LPDIRECT3DVERTEXBUFFER9 pt_VertexBuffer;//���㻺��ָ��
	LPDIRECT3DINDEXBUFFER9  pt_IndexBuffer;//��������ָ��
	int numVertexs; //��������
	int numIndex; //������������
	int stride;
	unsigned long fvf;//����ģʽ
	PrimType primType;//ͼԪ���� ���ǡ��ߵ�
};

//���Դ洢��ͼ��Ϣ
struct meshTexture{
	wchar_t* fileName;
	int width, height;
	IDirect3DTexture9* image;
};



//�̳���RenderInterface�Ľӿ�,ʵ��DirectX��Ⱦ,�����OpenGL,���½�OpenGLRender
class D3DRender :public RenderInterface
{
private:
	StaticVertexBuffer* m_StaticBufferList;
	meshTexture* m_textureList;
	D3DCOLOR m_color;
	D3DMATERIAL9* m_materialList;
	D3DLIGHT9* lightList;
	LPD3DXFONT* fontList;

	LPDIRECT3D9 m_Direct3D;
	LPDIRECT3DDEVICE9 m_Direct3DDevice;
	bool m_rengderingScene;
	int m_StaticBufferCount;
	int m_ActiveBufferCount;
	unsigned int m_TextureCount;
	
	
public:
	D3DRender();
	~D3DRender();

	//��ʼ��3��
	bool Initialize(int w, int h, WinHWND wh, int fullScreen);//����D3D�豸
	void OneTimeInit();//���ó�ʼ��Ⱦ״̬
	void SetBackColor(float r, float g, float b);
	
	//��Ⱦ��������õƹ�,����,��ͼ�ķ���
	void* GetDevice() { return m_Direct3DDevice; }
	void CalculateProjMatrix(float fov, float n, float f);
	void CalculateOrhtojMatrix(float n, float f);
	void StartRender(bool bColor, bool bDepth, bool bstencil);
	void EndRender();
	void ClearBuffer(bool bColor, bool bDepth, bool bstencil);
	bool CreateStaticBuffer(Vertextype vTpye, PrimType primType, int totalVertex, int totalIndices, int stride, void** data, unsigned int* indices, int* staticID);
	void ShutDown();
	void Render(int staticID);
	void SetMaterial(dxMaterial* mat);
	void SetLight(dxLight* light, int lightIndex);
	void DisableLight(int index);
	void SetTextureFilter(int index, int filter, int val);
	void SetTranspancy(RenderState state, TransState src, TransState dst);
	void EnablePointSprites(float size, float min, float a, float b, float c);
	void DisableSprites();
	void SaveScreenShot(wchar_t* file);
	int AddTexture2D(LPCWSTR file, int* texID);
	void ApplyTexture(int index, int texID);
	void SetMultiTexture();
	virtual int GetScreenWidth();
	virtual	int GetScreenHeight();
	virtual bool CreateGUI(int& id);
	virtual bool AddGUIBackTexure(int GUIID, LPCWSTR fileName);
	virtual bool AddGUIStaticText(int GUIID, int id, LPCWSTR text, int x, int y, unsigned long color, int fontID);
	virtual bool AddGUIButton(int GUIID, int id, int x, int y, LPCWSTR up, LPCWSTR over, LPCWSTR down);
	virtual void ProcessGUI(int GUIID, bool LMBDwon, int mouseX, int mouseY, void(*funcPtr)(int id, int state));
	virtual bool CreateText(LPCWSTR font, int weigth, int heigth, bool italic, int size, int &id) ;
	virtual void DisplayText(int id, long x, long y, int r, int g, int b, LPCWSTR text, ...) ;
	virtual void DisplayText(int id, long x, long y, unsigned long color, LPCWSTR text, ...) ;
};


#endif
