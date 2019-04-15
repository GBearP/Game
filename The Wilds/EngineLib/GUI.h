#pragma once
#ifndef GUI_H
#define GUI_H

#define STATICTEXT 1
#define BUTTON 2
#define BACKDROP 3

#define BUTTON_UP 1
#define BUTTON_OVER 2
#define BUTTON_DOWN 3




//self beta
/*
struct GUIVertex{
	float x, y, z, rhw;
	unsigned long color;
	float tu, tv;
};

struct GUIControl {
	int m_type;//控件类型,button.滚动轴等
	int m_id;//控件ID
	unsigned long m_color;//颜色
	int m_listID;//控件在列表中的ID
	float m_xPos, m_yPos;//控件在窗口的位置
	float m_width, m_height;//控件宽度和高度
	LPCWSTR* m_text;//文本指针
	LPDIRECT3DTEXTURE9* m_backTexture;//背景贴图,
	IDirect3DTexture9* m_upTex;//button纹理
	IDirect3DTexture9* m_downTex;
	IDirect3DTexture9* m_voerTex;
};

enum UIType
{
	ENTER,GAMING,EXIT
}; 

//使用D3D接口的GUI系统
//门面模式,有三个组件
class CD3DUIManager
{
private:
	LPD3DXFONT* fontsList;//字体列表的指针
	IDirect3DVertexBuffer9** m_vertexBuffer;//各种控件图片的顶点缓存列表
	GUIControl* controls;    //button控件列表的指针
	LPDIRECT3DVERTEXBUFFER9 m_backDropBuffer;//背景图的顶点缓存
	IDirect3DTexture9* m_mainPicture;//背景贴图   //可以使用背景控件,但只有图片来代表
	
	//IDirect3DDevice9* device;//引用D3D渲染接口的设备对象
	bool m_useBackDrop;
	int fontsCount;
	int controlsCount;
	int m_vertexBuffersCount;
	int m_width;
	int m_height;
public:
	CD3DUIManager(int w, int h);
	~CD3DUIManager() { Shutdown(); };
	
	//创建字体加入字体列表中
	bool CreateFonts(IDirect3DDevice9*device, LPCWSTR fontName, int size, int* fontID);
	//加载图像文件,成为背景
	bool AddBackDrop(IDirect3DDevice9* device, LPCWSTR fileName);
	//创建没有事件响应的静态文本,显示工作组等等
	bool AddStaticText(int id,  LPCWSTR text, float x, float y, unsigned long color,int fontID);
	//创建button
	bool AddButton(int id,float x,float y,char* up,char* over,char* down);
	//是否启用背景
	bool UseBackDrop(){
		return m_useBackDrop;
	}
	//设置窗口大小
	void SetWindowSize(int w, int h) {
		m_width = w;
		m_height = h;
	}
	void Shutdown();
	
	//获得索引位置字体
	LPD3DXFONT GetFont(int id) {
		
		if (id<0||id>=fontsCount)
		{
			return NULL;
		}
		return fontsList[id];
	}
	//获得控件
	GUIControl* GetGUIControl(int id) {
			if (id < 0 || id >= controlsCount)
			{
				return NULL;
			}
			return &controls[id];
		}
	//获得控件顶点缓存
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
*/

/*****************************************book version***********************************************/
//book beta
struct GUIVertex {
	float x, y, z, rhw;
	unsigned long color;
	float tu, tv;
};

struct GUIControl {
	int m_type;//控件类型,button.滚动轴等
	int m_id;//控件ID
	unsigned long m_color;//颜色
	int m_listID;//控件在列表中的ID
	float m_xPos, m_yPos;//控件在窗口的位置
	float m_width, m_height;//控件宽度和高度
	WCHAR* m_text;//文本指针	
	int m_upTex, m_downTex, m_overTex;
};


class GUISystem
{
private:
	GUIControl* p_controls;    //button控件列表的指针
	int controlsCount;
	int m_backDropID;

public:
	GUISystem();
	~GUISystem() { Shutdown(); };

	
	//加载图像文件,成为背景
	bool AddBackDrop(int texID, int sID);
	//创建没有事件响应的静态文本,显示工作组等等
	bool AddStaticText(int id,WCHAR* text, float x, float y, unsigned long color, int fontID);
	//创建button
	bool AddButton(int id, float x, float y, int width, int height, int upID, int overID, int downID, unsigned int staticID);
	void Shutdown();

	//创建控件,获得控件,获得控件的计数
	bool AddControl();
	GUIControl* GetGUIControl(int id) {
		if (id < 0 || id >= controlsCount) return NULL;
		return &p_controls[id];
	}
	GUIControl* GetBackdrop() {
		if (m_backDropID>=0&& controlsCount)
		{
			return &p_controls[m_backDropID];
		}
		return NULL;
	}
	int GetControlsCount() {
		return controlsCount;
	}

};
#endif // !GUI_H

