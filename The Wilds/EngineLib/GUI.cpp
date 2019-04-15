#include<d3d9.h>
#include<d3dx9.h>
#include"GUI.h"
#include<iostream>

//self version
/* 
CD3DUIManager::CD3DUIManager(/*IDirect3DDevice9* fp_device, int w, int h) {
	fontsList = NULL;
	controls = NULL;
	m_vertexBuffer = NULL;

	fontsCount = controlsCount = m_vertexBuffersCount = 0;
	m_width = w;
	m_height = h;
	m_useBackDrop = false;
	m_mainPicture = NULL;
}

bool CD3DUIManager::CreateFonts(IDirect3DDevice9* device, LPCWSTR fontName, int size, int* fontID) {
	if (!device) return false;
	if (!fontsList){
		fontsList = new LPD3DXFONT[1];
		if (!fontsList){
			return false;
		}
	}else{
		LPD3DXFONT* temp;
		temp = new LPD3DXFONT[fontsCount + 1];
		if (!temp){
			return false;
		}
		memcpy(temp, fontsList, sizeof(LPD3DXFONT)*fontsCount);
		delete[] fontsList;
		fontsList = temp;
	}
	if (FAILED(D3DXCreateFont(device, size, 
		                      0, 0, 1, 0,DEFAULT_CHARSET, 0, 0, 0, 
							  fontName, 
								&fontsList[fontsCount]))) {
		return false;
	}
	if (!fontsList[fontsCount]){
		return false;
	}
	if (fontID){
		*fontID = fontsCount;
		fontsCount++;
	}
	return true;
}
bool CD3DUIManager::AddBackDrop(IDirect3DDevice9* device, LPCWSTR fileName) {


	if (!fileName){
		MessageBox(0, 0, L"PictureName Can't be Null", 0);
		return false;
	}
	
	//m_mainBackDrop.m_type = BACKDROP;
	if (!device){
		MessageBox(0, 0, L"No Device", 0);
		return false;
	}
	if (D3DXCreateTextureFromFile(device, fileName, &m_mainPicture)!=D3D_OK) {
		MessageBox(0, 0,L"CreatUIBackGroundError", 0);
		return false;
	}
	float w = 800;// (float)m_width;
	float h = 600;// (float)m_height;
	GUIVertex obj[] = {
		{0,0,0.0f,1,D3DCOLOR_XRGB(255,255,255),0.1f,0.05f},
		{0,h,0.0f,1,D3DCOLOR_XRGB(255,255,255),0.1f,1.0f},
		{w,h,0.0f,1,D3DCOLOR_XRGB(255,255,255),0.9f,1.0f},
		{w,h,0.0f,1,D3DCOLOR_XRGB(255,255,255),0.9f,1.0f},
		{w,0,0.0f,1,D3DCOLOR_XRGB(255,255,255),0.9f,0.05f},
		{0,0,0.0f,1,D3DCOLOR_XRGB(255,255,255),0.1f,0.05f}
	};
	if (FAILED(device->CreateVertexBuffer(sizeof(obj), 0, D3DFVF_GUI, D3DPOOL_DEFAULT, &m_backDropBuffer, NULL))){
		return false;
	}
	void* ptr;
	if (FAILED(m_backDropBuffer->Lock(0, sizeof(obj), (void**)&ptr, 0))){
		return false;
	}
	memcpy	(ptr, obj, sizeof(obj));
	m_backDropBuffer->Unlock();
	m_useBackDrop = true;
	return true;
}
bool CD3DUIManager::AddStaticText(int id,LPCWSTR text, float x, float y, unsigned long color, int fontID) {
	if (!text||fontID<0||fontID>=fontsCount){
		return false;
	}
	if (!controls){
		controls = new GUIControl[1];
		if (!controls){
			return false;
		}
		memset(&controls[0], 0, sizeof(GUIControl));
	}
	else{
		GUIControl* temp;
		temp = new GUIControl[controlsCount + 1];
		if (!temp) {
			return false;
		}
		memset(temp, 0, sizeof(GUIControl)*(controlsCount + 1));
		memcpy(temp, controls, sizeof(GUIControl)*controlsCount);

		delete[] controls;
		controls = temp;
	}
	
	controls[controlsCount].m_type = STATICTEXT;
	controls[controlsCount].m_id = id;
	controls[controlsCount].m_color = color;
	controls[controlsCount].m_xPos = x;
	controls[controlsCount].m_yPos = y;
	controls[controlsCount].m_listID = fontID;
	
	size_t len = wcslen(text);
	std::cout << len;
	controls[controlsCount].m_text = new LPCWSTR[len+1];
	if (!controls[controlsCount].m_text){
		return false;
	}
	memcpy(controls[controlsCount].m_text, text, len);
	controls[controlsCount].m_text[len] = L'\0';
	controlsCount++;
	return true;
}
bool CD3DUIManager::AddButton(int id, float x, float y, char* up, char* over, char* down) {
	
	return true;
}
void CD3DUIManager::Shutdown() {
	if (m_useBackDrop){
		//m_mainBackDrop.m_backDrop->Release();
		delete m_mainPicture;
	}

	if (m_backDropBuffer){
		m_backDropBuffer->Release();
	}

	//m_mainBackDrop.m_backDrop = nullptr;
	m_mainPicture = nullptr;
	m_backDropBuffer = nullptr;
}
*/

//book version
GUISystem::GUISystem() {
	 p_controls=NULL;    //button控件列表的指针
	 controlsCount= 0;
	 m_backDropID=-1;
}

bool GUISystem::AddControl() {
	if (!p_controls) {
		p_controls = new GUIControl[1];
		if (!p_controls) return NULL;
		memset(&p_controls[0], 0, sizeof(GUIControl));
	}
	else {
		GUIControl* temp;
		temp = new	GUIControl[controlsCount+1];
		if (!temp)return NULL;
		memset(temp, 0, sizeof(GUIControl)*(controlsCount+1));
		memcpy(temp, p_controls, sizeof(GUIControl)*(controlsCount));
		delete[] p_controls;
		p_controls = temp;
		temp = nullptr;
	}
	return 1;
}

bool GUISystem::AddBackDrop(int texID, int sID) {


	if (texID < 0 || sID < 0) return false;

	//m_mainBackDrop.m_type = BACKDROP;
	if (m_backDropID < 0)
	{
		if (!AddControl())return false;
		p_controls[controlsCount].m_type = BACKDROP;
		p_controls[controlsCount].m_upTex = texID;
		p_controls[controlsCount].m_listID = sID;
		m_backDropID = controlsCount;
		++controlsCount;
	}else{
		p_controls[controlsCount].m_upTex = texID;
		p_controls[controlsCount].m_listID = sID;
	}
	return true;
}

//每个文本都是一个控件
bool GUISystem::AddStaticText(int id, WCHAR* text, float x, float y, unsigned long color, int fontID) {
	if (!text || fontID < 0)return false;
	if (!AddControl())return false;

	p_controls[controlsCount].m_type = STATICTEXT;
	p_controls[controlsCount].m_id = id;
	p_controls[controlsCount].m_color = color;
	p_controls[controlsCount].m_xPos = x;
	p_controls[controlsCount].m_yPos = y;
	p_controls[controlsCount].m_listID = fontID;

	size_t len = wcslen(text);
	p_controls[controlsCount].m_text = new WCHAR[len + 1];
	if (!p_controls[controlsCount].m_text) return false;
	memcpy(p_controls[controlsCount].m_text,text, len);
	p_controls[controlsCount].m_text[len] = L'0';
	controlsCount++;
	return true;
}

bool GUISystem::AddButton(int id, float x, float y, int width, int height, int upID, int overID, int downID, unsigned int staticID) {
	if (!AddControl()) return false;
	p_controls[controlsCount].m_type = BUTTON;
	p_controls[controlsCount].m_id = id;
	p_controls[controlsCount].m_xPos = x;
	p_controls[controlsCount].m_yPos = y;
	p_controls[controlsCount].m_width = width;
	p_controls[controlsCount].m_height = height;
	p_controls[controlsCount].m_upTex = upID;
	p_controls[controlsCount].m_overTex = overID;
	p_controls[controlsCount].m_listID = staticID;
	++controlsCount;
	return true;
}

void GUISystem::Shutdown() {
	for (int i = 0; i < controlsCount; i++){
		if (p_controls[i].m_text) {
			delete[] p_controls[i].m_text;
			p_controls[i].m_text = nullptr;
		}
	}
	controlsCount = 0;
	if (p_controls) delete[] p_controls;
	p_controls = nullptr;
}