#pragma once
#ifndef D3DRENDER_H
#define D3DRENDER_H

#include "RenderInterface.h"
#include<d3d9.h>
#include<d3dx9.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

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
struct meshTexture
{
	wchar_t* fileName;
	int width, height;
	IDirect3DTexture9* image;
};

bool CreateD3DRender(RenderInterface** g_Render);


//�̳���RenderInterface�Ľӿ�,ʵ��DirectX��Ⱦ,�����OpenGL,���½�OpenGLRender
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
	bool Initialize(int w, int h, WinHWND wh, int fullScreen);//����D3D�豸
	void OneTimeInit();//���ó�ʼ��Ⱦ״̬
	void SetBackColor(float r, float g, float b);
	
	//��Ⱦ��������õƹ�,����,��ͼ�ķ���
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
