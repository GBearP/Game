#pragma once
#ifndef D3DRENDER_H
#define D3DRENDER_H

#include "RenderInterface.h"
#include<d3d9.h>
#include<d3dx9.h>
#include<Windows.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

// #define D3DFVF_GUI (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//���Դ洢ͼԪ��Ϣ
struct StaticPrimitiveBuffer {
	StaticPrimitiveBuffer() :p_VertexBuffer(0), p_IndexBuffer(0),
						  numVertexs(0), numIndex(0), fvf(0), 
						  primType(NULL_TYPE) {}
	LPDIRECT3DVERTEXBUFFER9 p_VertexBuffer;//���㻺��ָ��
	LPDIRECT3DINDEXBUFFER9  p_IndexBuffer;//��������ָ��
	int numVertexs; //��������
	int numIndex; //������������
	int stride;
	unsigned long fvf;//����ģʽ
	PrimType primType;//ͼԪ���� ���ǡ��ߵ�
};

//���Դ洢��ͼ��Ϣ
struct MeshTexture{
	wchar_t* fileName;
	int width, height;
	IDirect3DTexture9* image;
};

//�̳���RenderInterface�Ľӿ�,ʵ��DirectX��Ⱦ,�����OpenGL,���½�OpenGLRender
class D3DRender :public RenderInterface
{
private:
	D3DCOLOR m_color;
	LPDIRECT3D9 m_Direct3D;
	LPDIRECT3DDEVICE9 m_Direct3DDevice;
	bool m_rengderingScene;

	//��̬���������������б�
	StaticPrimitiveBuffer* m_StaticBufferList;
	int m_StaticBufferCount;
	int m_ActiveBufferCount;
	//��ͼ�б�
	unsigned int m_TextureCount;
	MeshTexture* m_textureList;
	D3DLIGHT9* lightList;
	//D3DMATERIAL9* m_materialList;
	//LPD3DXFONT* fontList;
	void OneTimeInit();//���ó�ʼ��Ⱦ״̬
public:
	D3DRender();
	~D3DRender();

	//��ʼ��3��
	bool Initialize(int w, int h, HWND wh, int fullScreen);//����D3D�豸
	void ShutDown();
	void EndRender();
	void CalculateProjMatrix(float fov, float n, float f);
	void CalculateOrhtojMatrix(float n, float f);
	
	void SetBackColor(float r, float g, float b);
	void StartRender(bool bColor, bool bDepth, bool bstencil);
	void ClearBuffer(bool bColor, bool bDepth, bool bstencil);
	bool CreateStaticBuffer(Vertextype vTpye, PrimType primType, int totalVertex, int totalIndices, int stride, void** data, unsigned int* indices, int* staticID);
	void Render(int staticID);

	//��Ⱦ��������õƹ�,����,��ͼ�ķ���
	void SetLight(dxLight* light, int lightIndex);
	void DisableLight(int index);
	
	void SetMaterial(dxMaterial* mat);

	void SetTranspancy(RenderState state, TransState src, TransState dst);
	int AddTexture2D(LPCWSTR file, int* texID);
	void SetTextureFilter(int index, int filter, int val);
	void SetMultiTexture();
	void ApplyTexture(int index, int texID);
	void EnablePointSprites(float size, float min, float a, float b, float c);
	void DisableSprites();
	void SaveScreenShot(wchar_t* file);
	/*void* GetDevice() { return m_Direct3DDevice; }*/

	//GUI����
	//virtual int GetScreenWidth();
	//virtual	int GetScreenHeight();
	//virtual bool CreateGUI(int& id);
	//virtual bool AddGUIBackTexure(int id_GUI, LPCWSTR fileName);
	//virtual bool AddGUIStaticText(int id_GUI, int id, LPCWSTR text, int x, int y, unsigned long color, int fontID);
	//virtual bool AddGUIButton(int id_GUI, int id, int x, int y, LPCWSTR up, LPCWSTR over, LPCWSTR down);
	//virtual void ProcessGUI(int id_GUI, bool LMBDwon, int mouseX, int mouseY, void(*funcPtr)(int id, int state));
	//virtual bool CreateText(LPCWSTR font, int weigth, int heigth, bool italic, int size, int &id) ;
	//virtual void DisplayText(int id, long x, long y, int r, int g, int b, LPCWSTR text, ...) ;
	//virtual void DisplayText(int id, long x, long y, unsigned long color, LPCWSTR text, ...) ;

};
bool CreateRender(RenderInterface* gameRender);

unsigned long CreateD3DFVF(Vertextype flags) {
	unsigned long fvf = 0;
	//if (flags == D3DFVF_GUI) fvf = D3DFVF_GUI;
	return fvf;
}
#endif
