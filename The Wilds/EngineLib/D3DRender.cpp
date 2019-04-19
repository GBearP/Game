#include"D3DRender.h"
#include<stdio.h>
inline unsigned long FtoDW(float v) {
	return *((unsigned long*)&v);
}

unsigned long CreateD3DFVF(Vertextype flags) {
	unsigned long fvf = 0;
	if (flags == D3DFVF_GUI) fvf = D3DFVF_GUI;
	return fvf;
}

//D3DRender头文件继承于RenderInterface的接口
//在头文件中定义函数
//此处实现接口的函数
D3DRender::D3DRender() {
	m_Direct3D = NULL;
	m_Direct3DDevice = NULL;
	m_rengderingScene = false;
	m_StaticBufferList = NULL;
	m_StaticBufferCount = 0;
	m_ActiveBufferCount = 0;
	m_textureList = nullptr;
	fontList = NULL;
	fontCount = 0;
	GUIList = NULL;
	GUICount = 0;
	m_TextureCount = 0;
}

D3DRender::~D3DRender() {
	ShutDown();
}

bool D3DRender::Initialize(int w, int h, WinHWND wh, int Screen) {
	m_mainHandle = wh;
	m_full = Screen;

	ShutDown();//关闭上次的游戏引擎;

	if (!m_mainHandle)return false;

	//获得创建D3D对象所需设备信息等
	D3DDISPLAYMODE mode;
	D3DCAPS9 caps;
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	//创建D3D对象
	m_Direct3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_Direct3D)return false;

	//获得第一张显卡的信息
	if (FAILED(m_Direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode))) {
		return false;
	}
	if (FAILED(m_Direct3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps))) {
		return false;
	}

	DWORD processing = 0;
	if (caps.VertexProcessingCaps != 0) {
		processing = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE;
	}
	else {
		processing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
	if (m_full==0) {
		//d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_INTERVAL_IMMEDIATE;
		d3dpp.FullScreen_RefreshRateInHz = 0;
	}
	else {
		d3dpp.FullScreen_RefreshRateInHz = mode.RefreshRate;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	}

	d3dpp.Windowed = !m_full;//WIN 0 ;  FULL 1   Windowed True is window ,false is fullscreen
	d3dpp.BackBufferWidth = w;
	d3dpp.BackBufferHeight = h;
	d3dpp.hDeviceWindow = wh;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = mode.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	m_screenWitdth = w;
	m_screenHeight = h;

	if (FAILED(m_Direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_mainHandle, processing, &d3dpp, &m_Direct3DDevice))) {

		return false;
	}
	if (m_Direct3DDevice == NULL)
	{
		return false;
	}

	// 关闭Alpha混合等
	OneTimeInit();
	return true;
}

void D3DRender::CalculateProjMatrix(float fov, float n, float f) {
	if (!m_Direct3DDevice)
	{
		return;
	}
	D3DXMATRIX projection;
	D3DXMatrixPerspectiveLH(&projection, fov, (float)m_screenWitdth / m_screenHeight, n, f);
	m_Direct3DDevice->SetTransform(D3DTS_PROJECTION, &projection);

}

void  D3DRender::CalculateOrhtojMatrix(float n, float f) {
	if (!m_Direct3DDevice) {
		return;
	}
	D3DXMATRIX ortho;
	D3DXMatrixOrthoLH(&ortho, float(m_screenWitdth), float(m_screenHeight), n, f);
	m_Direct3DDevice->SetTransform(D3DTS_PROJECTION, &ortho);
}

void D3DRender::OneTimeInit() {
	if (!m_Direct3DDevice) {
		return;
	}
	m_Direct3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_Direct3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	CalculateProjMatrix(D3DX_PI / 4, 0.1f, 1000);

}

void D3DRender::SetBackColor(float r, float g, float b) {
	m_color = D3DCOLOR_COLORVALUE(r, g, b, 1.0f);
}

void D3DRender::StartRender(bool bColor, bool bDepth, bool bstencil) {
	if (!m_Direct3DDevice) return;
	DWORD flags = 0;
	if (bColor)		flags |= D3DCLEAR_TARGET;  /* Clear target surface */
	if (bDepth)		flags |= D3DCLEAR_ZBUFFER;  /* Clear target Zbufer */
	if (bstencil)	flags |= D3DCLEAR_STENCIL;  /* Clear stencil planes */
	
	if (FAILED(m_Direct3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, m_color, 1, 0))) {
		MessageBox(0, 0, L"ClearBufferError", 0);
		return;
	}//第三个参数为是否清除颜色缓存,深度缓存,后台缓存
	if (FAILED(m_Direct3DDevice->BeginScene())){
		return;
	}
	bool RenderState = true;// m_rengderingScene
}

void D3DRender::EndRender() {
	if (!m_Direct3DDevice) return;
	m_Direct3DDevice->EndScene();
	m_Direct3DDevice->Present(NULL, NULL, NULL, NULL);
	m_rengderingScene = false;
}

void  D3DRender::ClearBuffer(bool bColor, bool bDepth, bool bstencil) {
	if (!m_Direct3DDevice){return;
	}
	m_Direct3DDevice->EndScene();
	DWORD flags = 0;
	if (bColor) {
		flags |= D3DCLEAR_TARGET;
	}
	if (bDepth) {
		flags |= D3DCLEAR_ZBUFFER;
	}
	if (bstencil) {
		flags |= D3DCLEAR_STENCIL;
	}
	if (FAILED( m_Direct3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, m_color, 1, 0))) {
		MessageBox(0, 0, L"ClearBufferError", 0);
		return;
	}
	if (m_rengderingScene)
	{
		if (FAILED(m_Direct3DDevice->BeginScene())) {
			return;
		}
	}
}

bool D3DRender::CreateStaticBuffer(Vertextype vTpye, PrimType primType, int totalVertex, int totalIndices, int stride, void** data, unsigned int* indices, int* staticID) {
	void* ptr;
	int index = m_StaticBufferCount;
	if (!m_StaticBufferList){
		m_StaticBufferList = new StaticPrimitiveBuffer[1];
	if (!m_StaticBufferList) return false;
	}else{
		StaticPrimitiveBuffer* temp;
		temp = new StaticPrimitiveBuffer[m_StaticBufferCount + 1];
		memcpy(temp, m_StaticBufferList, sizeof(StaticPrimitiveBuffer)*m_StaticBufferCount);
		delete[] m_StaticBufferList;
		m_StaticBufferList = temp;
		temp = nullptr;
	}
	m_StaticBufferList[index].numVertexs = totalVertex;
	m_StaticBufferList[index].numIndex = totalIndices;
	m_StaticBufferList[index].primType = primType;
	m_StaticBufferList[index].stride = stride;
	m_StaticBufferList[index].fvf = CreateD3DFVF(vTpye);
	//创建索引缓存
	if (totalIndices > 0){
		if (FAILED(m_Direct3DDevice->CreateIndexBuffer(sizeof(unsigned int)*totalIndices, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_StaticBufferList[index].pt_IndexBuffer, NULL))) {
			return false;
		}
		if (FAILED(m_StaticBufferList[index].pt_IndexBuffer->Lock(0, 0, (void**)&ptr, 0))) {
			return false;
		}
		memcpy(ptr, indices, sizeof(unsigned int)*totalIndices);
		m_StaticBufferList[index].pt_IndexBuffer->Unlock();
	}else {
		m_StaticBufferList[index].pt_IndexBuffer = NULL;
	}
	//创建顶点缓存
	if (FAILED(m_Direct3DDevice->CreateVertexBuffer(totalVertex*stride, D3DUSAGE_WRITEONLY, m_StaticBufferList[index].fvf, D3DPOOL_DEFAULT, &m_StaticBufferList[index].pt_VertexBuffer, NULL))) {
		return false;
	}
	if (FAILED(m_StaticBufferList[index].pt_VertexBuffer->Lock(0, 0, (void**)&ptr, 0))) {
		return false;
	}
	memcpy(ptr, data, totalVertex*stride);
	if (FAILED(m_StaticBufferList[index].pt_VertexBuffer->Unlock())) {
		return false;
	}
	*staticID = m_StaticBufferCount;
	m_StaticBufferCount++;
	return true;
}

void D3DRender::ShutDown() {
	//清理顶点缓存和索引缓存
	for (int i = 0; i < m_StaticBufferCount; i++){
		if (m_StaticBufferList[i].pt_VertexBuffer) {
			m_StaticBufferList[i].pt_VertexBuffer->Release();
			m_StaticBufferList[i].pt_VertexBuffer = nullptr;
		}
		if (m_StaticBufferList[i].pt_IndexBuffer) {
			m_StaticBufferList[i].pt_IndexBuffer->Release();
			m_StaticBufferList[i].pt_IndexBuffer = nullptr;
		}
	}
	for (unsigned int i = 0; i<m_TextureCount; i++)
	{
		if (m_textureList[i].fileName) {
			delete[]m_textureList->fileName;
			m_textureList[i].fileName = NULL;
		}
		if (m_textureList->image){
			m_textureList[i].image->Release();
			m_textureList[i].image = NULL;
		}
	}
	m_TextureCount = 0;
	m_StaticBufferCount = 0;
	if (m_StaticBufferList) {
		delete[] m_StaticBufferList;
		m_StaticBufferList = nullptr;
	}

	//清除字体列表
	for (int i = 0; i < fontCount; i++)
	{
		if (fontList[i]) {
			fontList[i]->Release();
			fontList[i] = NULL;
		}
	}
	fontCount = 0;
	if (fontList)
	{
		delete[] fontList;
	}
	fontList = NULL;
	if (m_textureList)
	{
		delete[] m_textureList;
		m_textureList = NULL;
	}

	for (int i = 0; i < GUICount; i++){
		GUIList[i].Shutdown();
	}
	if (GUIList) delete[] GUIList;
	GUIList = nullptr;
	GUICount = 0;

	if (m_Direct3DDevice) {
		m_Direct3DDevice->Release();
	}
	if (m_Direct3D) {
		m_Direct3D->Release();
	}
	m_Direct3DDevice = nullptr;
	m_Direct3D = nullptr;
}

void D3DRender::Render(int staticID) {
	if (staticID >= m_StaticBufferCount) return;
	if (m_ActiveBufferCount != staticID)
	{
		if (m_StaticBufferList[staticID].pt_IndexBuffer != nullptr){
			m_Direct3DDevice->SetIndices(m_StaticBufferList[staticID].pt_IndexBuffer);
		}
		m_Direct3DDevice->SetStreamSource(0,
										m_StaticBufferList[staticID].pt_VertexBuffer, 
										0, 
										m_StaticBufferList[staticID].stride);//0为第一个数据流,0为第一个顶点
		m_Direct3DDevice->SetFVF(m_StaticBufferList[staticID].fvf);
		m_ActiveBufferCount = staticID;
	}
	//根据图元类型绘制
	if (m_StaticBufferList[staticID].pt_IndexBuffer != nullptr) {
		switch (m_StaticBufferList[staticID].primType)
		{
		case POIST_LIST:
			if (FAILED(m_Direct3DDevice->DrawPrimitive(D3DPT_POINTLIST, 0, m_StaticBufferList[staticID].numVertexs))) {
				return;
			}
			break;
		case TRANGLE_LIST:
			if (FAILED(m_Direct3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, (int)m_StaticBufferList[staticID].numVertexs / 3, 0, m_StaticBufferList[staticID].numIndex))) {
				return;
			}
			break;
		case TRANGLE_STRIP:
			if (FAILED(m_Direct3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (int)m_StaticBufferList[staticID].numVertexs / 2, 0, m_StaticBufferList[staticID].numIndex))) {
				return;
			}
			break;
		case TRANGLE_FAN:
			if (FAILED(m_Direct3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN, 0, 0, (int)m_StaticBufferList[staticID].numVertexs / 2, 0, m_StaticBufferList[staticID].numIndex))) {
				return;
			}
			break;
		case LINE_STRIP:
			if (FAILED(m_Direct3DDevice->DrawIndexedPrimitive(D3DPT_LINESTRIP, 0, 0, m_StaticBufferList[staticID].numVertexs, 0, m_StaticBufferList[staticID].numIndex))) {
				return;
			}
			break;
		case LINE_LIST:
			if (FAILED(m_Direct3DDevice->DrawIndexedPrimitive(D3DPT_LINELIST, 0, 0, (int)m_StaticBufferList[staticID].numVertexs / 2, 0, m_StaticBufferList[staticID].numIndex))) {
				return;
			}
			break;
		default:
			return;
		}
	}
	else {
		switch (m_StaticBufferList[staticID].primType)
		{
		case POIST_LIST:
			if (FAILED(m_Direct3DDevice->DrawPrimitive(D3DPT_POINTLIST, 0, m_StaticBufferList[staticID].numVertexs))) {
				return;
			}
			break;
		case TRANGLE_LIST:
			if (FAILED(m_Direct3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, (int)m_StaticBufferList[staticID].numVertexs / 3))) {
				//MessageBox(0, 0, L"TRANGLE_LIST DrawError", 0);
				return;
			}
			break;
		case TRANGLE_STRIP:

			if (FAILED(m_Direct3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, (int)m_StaticBufferList[staticID].numVertexs / 2))) {
				//MessageBox(0, 0, L"TRANGLE_STRIP", 0);
				return;
			}
			break;
		case TRANGLE_FAN:
			if (FAILED(m_Direct3DDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, (int)m_StaticBufferList[staticID].numVertexs / 2))) {
				return;
			}
			break;
		case LINE_STRIP:
			if (FAILED(m_Direct3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, (int)m_StaticBufferList[staticID].numVertexs))) {
				return;
			}
			break;
		case LINE_LIST:
			if (FAILED(m_Direct3DDevice->DrawPrimitive(D3DPT_LINELIST, 0, (int)m_StaticBufferList[staticID].numVertexs / 2))) {
				return;
			}
			break;
		default:
			return;
		}
	}
	return;
}

void D3DRender::SetMaterial(dxMaterial* mat) {
	if (!mat || !m_Direct3DDevice)
	{

	}
	D3DMATERIAL9 m = { mat->diffuseR, mat->diffuseG, mat->diffuseB, mat->diffuseA,
						mat->ambientA, mat->ambientG, mat->ambientB, mat->ambientA,
						mat->specularR, mat->specularG, mat->specularB, mat->specularA,
						mat->emissiveR, mat->emissiveG, mat->emissiveB, mat->emissiveA,
						mat->power };

	m_Direct3DDevice->SetMaterial(&m);
}

void D3DRender::SetLight(dxLight* light, int lightIndex) {
	if (!light || !m_Direct3DDevice || !lightIndex)
	{
		return;
	}
	D3DLIGHT9 lig;
	lig.Direction.x = light->dirX;
	lig.Direction.y = light->dirY;
	lig.Direction.z = light->dirZ;
	lig.Position.x = light->posX;
	lig.Position.y = light->posY;
	lig.Position.z = light->posZ;

	lig.Ambient.r = light->ambientR;
	lig.Ambient.g = light->ambientG;
	lig.Ambient.b = light->ambientB;
	lig.Ambient.a = light->ambientA;
	lig.Diffuse.r = light->diffuseR;
	lig.Diffuse.g = light->diffuseG;
	lig.Diffuse.b = light->diffuseB;
	lig.Diffuse.a = light->diffuseA;
	lig.Specular.r = light->specularR;
	lig.Specular.g = light->specularG;
	lig.Specular.b = light->specularB;
	lig.Specular.a = light->specularA;

	lig.Range = light->range;
	lig.Falloff = light->falloffRange;
	lig.Phi = light->thi;
	lig.Theta = light->theta;
	if (light->type == SPOTLIGHT) {
		lig.Type = D3DLIGHT_SPOT;
	}
	else if (light->type == POINTLIGHT)
	{
		lig.Type = D3DLIGHT_POINT;
	}
	else
	{
		lig.Type = D3DLIGHT_DIRECTIONAL;
	}
	m_Direct3DDevice->SetLight(lightIndex, &lig);
	m_Direct3DDevice->LightEnable(lightIndex, true);
}

void D3DRender::DisableLight(int index) {
	if (!m_Direct3DDevice) {
		return;
	}
	m_Direct3DDevice->LightEnable(index, false);
}

void D3DRender::SetTranspancy(RenderState state, TransState src, TransState dst) {
	if (!m_Direct3DDevice) {
		return;
	}
	if (state == TRANSPARENCY_NONE)
	{
		m_Direct3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		return;
	}
	if (state == TRANSPARENCY_ENABLE)
	{
		m_Direct3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		switch (src)
		{
		case TRANS_ZERO:
			m_Direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
			break;
		case TRANS_ONE:
			m_Direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			break;
		case TRANS_SRCCOLOR:
			m_Direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
			break;
		case TRANS_INVSRCOLOR:
			m_Direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVSRCCOLOR);
			break;
		case TRANS_SRCALPHA:
			m_Direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			break;
		case TRANS_INVSRCALPHA:
			m_Direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVSRCALPHA);
			break;
		case TRANS_DSTALPHA:
			m_Direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTALPHA);
			break;
		case TRANS_INVDSTALPHA:
			m_Direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTALPHA);
			break;
		case TRANSA_SRCALPHASAT:
			m_Direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHASAT);
			break;
		case TRANS_BOTHSRCALPHA:
			m_Direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BOTHSRCALPHA);
			break;
		case TRANS_INVBOTHSRCALPHA:
			m_Direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BOTHINVSRCALPHA);
			break;
		case TRANS_BLENDFACTOR:
			m_Direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BLENDFACTOR);
			break;
		case TRANS_INVBLENDFACTOR:
			m_Direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVBLENDFACTOR);
			break;
		default:
			m_Direct3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
			break;
		}
		switch (dst)
		{
		case TRANS_ZERO:
			m_Direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		case TRANS_ONE:
			m_Direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		case TRANS_SRCCOLOR:
			m_Direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
			break;
		case TRANS_INVSRCOLOR:
			m_Direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			break;
		case TRANS_SRCALPHA:
			m_Direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);
			break;
		case TRANS_INVSRCALPHA:
			m_Direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			break;
		case TRANS_DSTALPHA:
			m_Direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);
			break;
		case TRANS_INVDSTALPHA:
			m_Direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVDESTALPHA);
			break;
		case TRANSA_SRCALPHASAT:
			m_Direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHASAT);
			break;
		case TRANS_BOTHSRCALPHA:
			m_Direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BOTHSRCALPHA);
			break;
		case TRANS_INVBOTHSRCALPHA:
			m_Direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BOTHINVSRCALPHA);
			break;
		case TRANS_BLENDFACTOR:
			m_Direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BLENDFACTOR);
			break;
		case TRANS_INVBLENDFACTOR:
			m_Direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVBLENDFACTOR);
			break;
		default:
			m_Direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		}

	}
}

int D3DRender::AddTexture2D(LPCWSTR file, int* texID) {
	if (!file || !m_Direct3DDevice) return 0;
	size_t len = wcslen(file)+1;
	if (!len) return 0;
	unsigned int index = m_TextureCount;
	if (!m_textureList){
		m_textureList = new meshTexture[1];
		if (!m_textureList) return 0;
	}else {
		meshTexture* temp;
		temp = new meshTexture[m_TextureCount + 1];
		memcpy(temp, m_textureList, sizeof(meshTexture)*m_TextureCount);
		delete[] m_textureList;
		m_textureList = temp;
	}
	m_textureList[index].fileName = new WCHAR[len];
	memcpy(m_textureList[index].fileName, file, len);
	D3DCOLOR colorkey = 0xff000000;
	D3DXIMAGE_INFO info;
	if (D3DXCreateTextureFromFileEx(m_Direct3DDevice,
		file, 0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, colorkey,
		&info, NULL, &m_textureList[index].image) != D3D_OK) {
		return true;
	}
	m_textureList[index].width = info.Width;
	m_textureList[index].height = info.Height;
	*texID = m_TextureCount;
	m_TextureCount++;
	return 1;
}

void D3DRender::SetTextureFilter(int index, int filter, int val) {
	if (!m_Direct3DDevice || index < 0) {
		return;
	}
	D3DSAMPLERSTATETYPE fil = D3DSAMP_MINFILTER;
	int v = D3DTEXF_POINT;

	if (filter==MIN_FILTER){
		fil = D3DSAMP_MINFILTER;
	}
	else if (filter == MAG_FILTER){
		fil = D3DSAMP_MAGFILTER;
	}else if (filter == MIP_FILTER){
		fil = D3DSAMP_MIPFILTER;
	}
	
	if (val == POINT_TYPE){
		v = D3DTEXF_POINT;
	}else if (val== LINEAR_TYPE){
		v = D3DTEXF_LINEAR;
	}else if (val == ANISOTROPIC_TYPE){
		v = D3DTEXF_ANISOTROPIC;
	}

	m_Direct3DDevice->SetSamplerState(index, fil, v);
}

void D3DRender::SetMultiTexture() {
	if (!m_Direct3DDevice) {
		return;
	}
	m_Direct3DDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	m_Direct3DDevice->SetTextureStageState(0, D3DTSS_COLOROP,D3DTOP_MODULATE);
	m_Direct3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1,D3DTA_TEXTURE);
	m_Direct3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2,D3DTA_DIFFUSE);

	m_Direct3DDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);
	m_Direct3DDevice->SetTextureStageState(1, D3DTSS_COLOROP,D3DTOP_MODULATE);
	m_Direct3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1,D3DTA_TEXTURE);
	m_Direct3DDevice->SetTextureStageState(1, D3DTSS_COLORARG2,D3DTA_CURRENT);
}

void D3DRender::ApplyTexture(int index, int texID) {
	if (!m_Direct3DDevice)return;
	if (index<0||texID<0){
		MessageBox(0, 0, L"index<0||texID<0", 0);
		m_Direct3DDevice->SetTexture(0, NULL);
	}else {
		m_Direct3DDevice->SetTexture(index, m_textureList[index].image);
	}
}

void D3DRender::SaveScreenShot(wchar_t* file) {
	if (!file)return;
	IDirect3DSurface9* surface = NULL;
	D3DDISPLAYMODE mode;
	m_Direct3DDevice->GetDisplayMode(0, &mode);
	m_Direct3DDevice->CreateOffscreenPlainSurface(mode.Width, mode.Height, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &surface, NULL);
	m_Direct3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &surface);
	D3DXSaveSurfaceToFile(file, D3DXIFF_JPG, surface, NULL, NULL);
	if (surface!=NULL){
		surface->Release();
		surface = nullptr;
	}
}

void D3DRender::EnablePointSprites(float size, float min, float a, float b, float c) {
	if (!m_Direct3DDevice){
		return;
	}
	m_Direct3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	m_Direct3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	m_Direct3DDevice->SetRenderState(D3DRS_POINTSIZE, FtoDW(size));
	m_Direct3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDW(min));
	m_Direct3DDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDW(a));
	m_Direct3DDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDW(b));
	m_Direct3DDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDW(c));
}

void D3DRender::DisableSprites() {
	m_Direct3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
	m_Direct3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
}

int D3DRender::GetScreenWidth() {
	return m_screenWitdth;
	
}
int D3DRender::GetScreenHeight() {
	return m_screenHeight;
}

 bool D3DRender::CreateGUI(int& id) {
	 if (!GUIList) {
		 GUIList = new GUISystem[1];
		 if (!GUIList) return false;
	 }
	 else{
		 GUISystem* temp;
		 temp = new GUISystem[GUICount + 1];
		 memcpy(temp, GUIList, sizeof(GUISystem)*GUICount);
		 delete[] GUIList;
		 GUIList = temp;
		 temp = nullptr;
	 }
	 id = GUICount;
	 GUICount++;
	 return true;
}

 bool D3DRender::AddGUIBackTexure(int id_GUI, LPCWSTR fileName){
	 if (id_GUI>=GUICount) return false;
	 int texID = -1;
	 int staticTexIDs = -1;
	 
	 if (!AddTexture2D(fileName,&texID)) return false;
	 unsigned long col = D3DCOLOR_XRGB(255, 255, 255);
	 GUIVertex obj[] = {
		 {(float)m_screenWitdth,0,0,1,col,1,0},
		 {(float)m_screenWitdth,(float)m_screenHeight,0,1,col,1,1},
		{0,0,0,1,col,0,0},
		{0,(float)m_screenHeight,0,1,col,0,1},
	 };
	 if (!CreateStaticBuffer(D3DFVF_GUI, TRANGLE_STRIP, 4, 0, sizeof(GUIVertex), (void**)&obj, NULL, &staticTexIDs)) return false;
	 return GUIList[id_GUI].AddBackDrop(texID, staticTexIDs);
 }
 bool D3DRender::AddGUIStaticText(int id_GUI, int id, LPCWSTR text, int x, int y, unsigned long color, int fontID){
	 if (id_GUI>=GUICount) return false;
	 return GUIList[id_GUI].AddStaticText(id, text, x, y, color, fontID);
 }
 bool D3DRender::AddGUIButton(int id_GUI, int id, int x, int y, LPCWSTR up, LPCWSTR over, LPCWSTR down){
	 if (id_GUI >=GUICount)return false;
	 int upID = -1,overID=-1,downID=-1,staticID=-1;
	 if (!AddTexture2D(up,&upID)) return false;
	 if (!AddTexture2D(over,&overID)) return false;
	 if (!AddTexture2D(down,&downID)) return false;
	 unsigned long col = D3DCOLOR_XRGB(255, 255, 255);
	 int w = m_textureList[upID].width;
	 int h = m_textureList[upID].height;
	 GUIVertex obj[] = {
		 {(float)(w+x),(float)(0+y),0,1,col,1,0},
		 {(float)(w + x),(float)(h + y),0,1,col,1,1},
		{(float)(0 + x),(float)(0 + y),0,1,col,0,0},
		{(float)(0 + x),(float)(h + y),0,1,col,0,1},
	 };
	 if (!CreateStaticBuffer(D3DFVF_GUI, TRANGLE_STRIP, 4, 0, sizeof(GUIVertex), (void**)&obj, NULL, &staticID)) return false;
	 return GUIList[id_GUI].AddButton(id,x,y,w,h,upID,overID,downID,staticID);
 }
 void D3DRender::ProcessGUI(int GUIID, bool LMBDwon, int mouseX, int mouseY, void(*funcPtr)(int id, int state)){
	 if (GUIID >= GUICount || !m_Direct3DDevice) return;
	 GUISystem* GUI = &GUIList[GUIID];
	 if (GUIID<0) return;
	 GUIControl* backdrop = GUI->GetBackdrop();
	 //绘制自己
	 if (backdrop)
	 {
		 ApplyTexture(0, backdrop->m_upTex);
		 Render(backdrop->m_listID);
		 ApplyTexture(0, -1);
	 }
	 int status = BUTTON_UP;

	 //loop through a;; controls and display them
	 for (int i = 0; i < GUI->GetControlsCount(); i++)
	 {
		 GUIControl* pCnt = GUI->GetGUIControl(i);
		 if (!pCnt)continue;
		// RECT position = {0,0,(long)gui.}
		 //if (!pCnt) return;
		 switch (pCnt->m_type)
		 {
		 case STATICTEXT:
			 DisplayText(pCnt->m_listID, pCnt->m_xPos, pCnt->m_yPos, pCnt->m_color, pCnt->m_text);
			 break;
		 case BUTTON:
			 status = BUTTON_UP;
			 m_Direct3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
			 m_Direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			 m_Direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			 if (( mouseX>pCnt->m_xPos  &&  mouseX<pCnt->m_xPos+pCnt->m_width )    &&
				 (mouseY>pCnt->m_yPos) && (mouseY < pCnt->m_yPos + pCnt->m_height))
			 {
				 if (LMBDwon) {
					 status = BUTTON_DOWN;
				 }else {
					 status = BUTTON_OVER;
				 }
			 }
			 if (status==BUTTON_UP){
				ApplyTexture(0, pCnt->m_upTex);
			 }
			 if (status==BUTTON_OVER){
				 ApplyTexture(0, pCnt->m_overTex);
			 }
			 if (status==BUTTON_DOWN){
				 ApplyTexture(0, pCnt->m_downTex);
			 }
			 Render(pCnt->m_listID);
			 m_Direct3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
			 break;
		 }
		 if (funcPtr) {
			 funcPtr(pCnt->m_id, status);
		 }
	 }
 }

bool  D3DRender::CreateText(LPCWSTR font, int weight, int heigth, bool italic, int size, int &id){
	if (!fontList){
		fontList = new LPD3DXFONT[1];
		if (!fontList) return false;
	}
	else{
		LPD3DXFONT* temp;
		temp = new LPD3DXFONT[fontCount + 1];
		memcpy(temp, fontList, sizeof(LPD3DXFONT)*fontCount);
		delete[] fontList;
		fontList = temp;
		temp = nullptr;
	}
	if (FAILED(D3DXCreateFont(m_Direct3DDevice,size,0, weight,1,italic,0,0,0,0,font,&fontList[fontCount]))){
		MessageBox(0, 0, L"创建字体失败", 0);
		return false;
	}
	id = fontCount;
	fontCount++;
	return true;
}
void  D3DRender::DisplayText(int id, long x, long y, int r, int g, int b, LPCWSTR text, ...){
	RECT position = { x,y,m_screenWitdth,m_screenHeight };
	WCHAR message[1024];
	va_list argList;

	if (id>=fontCount)
	{
		return;
	}
	va_start(argList, text);
	wvsprintf(message, text, argList);
	va_end(argList);
	fontList[id]->DrawTextW(NULL, message, -1, &position, DT_SINGLELINE, D3DCOLOR_ARGB(255, r, g, b));
}
void  D3DRender::DisplayText(int id, long x, long y, unsigned long color, LPCWSTR text, ...){
	RECT position = { x,y,m_screenWitdth,m_screenHeight };
	WCHAR message[1024];
	va_list argList;

	if (id >= fontCount)
	{
		return;
	}
	va_start(argList, text);
	wvsprintf(message, text, argList);
	va_end(argList);
	fontList[id]->DrawTextW(NULL, message, -1, &position, DT_SINGLELINE,color);
}