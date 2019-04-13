#pragma once
#ifndef GUI_H
#define GUI_H

#define STATICTEXT 1
#define BUTTON 2
#define BACKDROP 3

#define BUTTON_UP 1
#define BUTTON_OVER 2
#define BUTTON_DOWN 3

#define D3DFVF_GUI (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

struct GUIVertex{
	float x, y, z, rhw;
	unsigned long color;
	float tu, tv;
};

struct GUIControl {
	int m_type;//�ؼ�����,button.�������
	int m_id;//�ؼ�ID
	unsigned long m_color;//��ɫ
	int m_listID;//�ؼ����б��е�ID
	float m_xPos, m_yPos;//�ؼ��ڴ��ڵ�λ��
	float m_width, m_height;//�ؼ����Ⱥ͸߶�
	LPCWSTR* m_text;//�ı�ָ��
	LPDIRECT3DTEXTURE9* m_backTexture;//������ͼ,
	IDirect3DTexture9* m_upTex;//button����
	IDirect3DTexture9* m_downTex;
	IDirect3DTexture9* m_voerTex;
};

enum UIType
{
	ENTER,GAMING,EXIT
}; 

//ʹ��D3D�ӿڵ�GUIϵͳ
//����ģʽ,���������
class CD3DUIManager
{
private:
	LPD3DXFONT* fontsList;//�����б���ָ��
	IDirect3DVertexBuffer9** m_vertexBuffer;//���ֿؼ�ͼƬ�Ķ��㻺���б�
	GUIControl* controls;    //button�ؼ��б���ָ��
	LPDIRECT3DVERTEXBUFFER9 m_backDropBuffer;//����ͼ�Ķ��㻺��
	IDirect3DTexture9* m_mainPicture;//������ͼ   //����ʹ�ñ����ؼ�,��ֻ��ͼƬ������
	
	//IDirect3DDevice9* device;//����D3D��Ⱦ�ӿڵ��豸����
	bool m_useBackDrop;
	int fontsCount;
	int controlsCount;
	int m_vertexBuffersCount;
	int m_width;
	int m_height;
public:
	CD3DUIManager(int w, int h);
	~CD3DUIManager() { Shutdown(); };
	
	//����������������б���
	bool CreateFonts(IDirect3DDevice9*device, LPCWSTR fontName, int size, int* fontID);
	//����ͼ���ļ�,��Ϊ����
	bool AddBackDrop(IDirect3DDevice9* device, LPCWSTR fileName);
	//����û���¼���Ӧ�ľ�̬�ı�,��ʾ������ȵ�
	bool AddStaticText(int id,  LPCWSTR text, float x, float y, unsigned long color,int fontID);
	//����button
	bool AddButton(int id,float x,float y,char* up,char* over,char* down);
	//�Ƿ����ñ���
	bool UseBackDrop(){
		return m_useBackDrop;
	}
	//���ô��ڴ�С
	void SetWindowSize(int w, int h) {
		m_width = w;
		m_height = h;
	}
	void Shutdown();
	
	//�������λ������
	LPD3DXFONT GetFont(int id) {
		
		if (id<0||id>=fontsCount)
		{
			return NULL;
		}
		return fontsList[id];
	}
	//��ÿؼ�
	GUIControl* GetGUIControl(int id) {
			if (id < 0 || id >= controlsCount)
			{
				return NULL;
			}
			return &controls[id];
		}
	//��ÿؼ����㻺��
	LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer(int id) {
		if (id < 0 || id >= m_vertexBuffersCount)
		{
			return NULL;
		}
		return m_vertexBuffer[id];
	}	
	int GetTotalFonts() {
		return fontsCount;
	}
	int GetControlsCount() {
		return controlsCount;
	}
	int GetBuffersCount() {
		return m_vertexBuffersCount;
	}
	int GetWinWidth() {
		return m_width;
	}
	int GetWinHeight() {
		return m_height;
	}

	IDirect3DTexture9* GetBackDrop() {
		return m_mainPicture;
	}	 
	LPDIRECT3DVERTEXBUFFER9 GetBackDropBuffer() {
		return m_backDropBuffer;
	}
};
#endif // !GUI_H
