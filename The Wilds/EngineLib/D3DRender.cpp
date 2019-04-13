#include"D3DRender.h"

inline unsigned long FtoDW(float v) {
	return *((unsigned long*)&v);
}


bool CreateD3DRender(RenderInterface** g_Render) {

	if (!*g_Render) {
		*g_Render = new D3DRender();
	}
	else {
		return false;
	}
	return true;
}

unsigned long CreateD3DFVF(Vertextype flags) {
	unsigned long fvf = 0;
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
	m_texture = nullptr;
	unsigned int m_numTextures = 0;
}

D3DRender::~D3DRender() {
	ShutDown();
}

bool D3DRender::Initialize(int w, int h, WinHWND wh, int Screen) {
	m_mainHandle = wh;
	m_full = Screen;

	ShutDown();//关闭上次的游戏引擎;

	if (!m_mainHandle) {
		return false;
	}

	//获得创建D3D对象所需设备信息等
	D3DDISPLAYMODE mode;
	D3DCAPS9 caps;
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	//创建D3D对象
	m_Direct3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_Direct3D) {
		return false;

	}

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
	if (!m_Direct3DDevice)
	{
		return;
	}
	DWORD flags = 0;
	if (bColor) {
		flags |= D3DCLEAR_TARGET;  /* Clear target surface */
	}
	if (bDepth) {
		flags |= D3DCLEAR_ZBUFFER;  /* Clear target Zbufer */
	}
	if (bstencil) {
		flags |= D3DCLEAR_STENCIL;  /* Clear stencil planes */
	}

	if (!m_Direct3DDevice->Clear(0, NULL, flags, m_color, 1, 0)) {
		return;
	}//第三个参数为是否清除颜色缓存,深度缓存,后台缓存
	if (!m_Direct3DDevice->BeginScene())
	{
		return;
	}

	bool RenderState = true;// m_rengderingScene
}

void D3DRender::EndRender() {
	if (!m_Direct3DDevice)
	{
		return;
	}
	m_Direct3DDevice->EndScene();
	m_Direct3DDevice->Present(NULL, NULL, NULL, NULL);
	m_rengderingScene = false;
}

void  D3DRender::ClearBuffer(bool bColor, bool bDepth, bool bstencil) {
	if (!m_Direct3DDevice)
	{
		return;
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
	if (!m_Direct3DDevice->Clear(0, NULL, flags, m_color, 1, 0)) {
		return;
	}
	if (m_rengderingScene)
	{
		if (FAILED(m_Direct3DDevice->BeginScene())) {
			return;
		}
	}
}

void D3DRender::CreateStaticBuffer(Vertextype vTpye, PrimType primType, int totalVertex, int totalIndices, int stride, void** data, unsigned int* indices, int* staticID) {
	void* ptr;
	int index = m_StaticBufferCount;
	if (!m_StaticBufferList)
	{
		m_StaticBufferList = new StaticVertexBuffer();
	}
	if (!m_StaticBufferList)
	{
		return;
	}
	else
	{
		StaticVertexBuffer* temp;
		temp = new StaticVertexBuffer[m_StaticBufferCount + 1];
		memcpy(temp, m_StaticBufferList, sizeof(StaticVertexBuffer)*m_StaticBufferCount);
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
	if (totalIndices > 0)
	{
		if (FAILED(m_Direct3DDevice->CreateIndexBuffer(sizeof(unsigned int)*totalIndices, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_StaticBufferList[index].pt_IndexBuffer, NULL))) {
			return;
		}
		if (FAILED(m_StaticBufferList[index].pt_IndexBuffer->Lock(0, 0, (void**)&ptr, 0))) {
			return;
		}
		memcpy(ptr, indices, sizeof(unsigned int)*totalIndices);
		m_StaticBufferList[index].pt_IndexBuffer->Unlock();
	}
	else {
		m_StaticBufferList[index].pt_IndexBuffer = NULL;
		return;
	}

	//创建顶点缓存
	if (FAILED(m_Direct3DDevice->CreateVertexBuffer(totalVertex*stride, D3DUSAGE_WRITEONLY, m_StaticBufferList[index].fvf, D3DPOOL_DEFAULT, &m_StaticBufferList[index].pt_VertexBuffer, NULL))) {
		return;
	}
	if (FAILED(m_StaticBufferList[index].pt_VertexBuffer->Lock(0, 0, (void**)ptr, 0))) {
		return;
	}
	memcpy(ptr, data, totalVertex*stride);
	if (FAILED(m_StaticBufferList[index].pt_VertexBuffer->Unlock())) {
		return;
	}
	*staticID = m_StaticBufferCount;
	m_StaticBufferCount++;
}

void D3DRender::ShutDown() {
	for (int i = 0; i < m_StaticBufferCount; i++)
	{
		if (m_StaticBufferList[i].pt_VertexBuffer) {
			m_StaticBufferList[i].pt_VertexBuffer->Release();
			m_StaticBufferList[i].pt_VertexBuffer = nullptr;
		}
		if (m_StaticBufferList[i].pt_IndexBuffer) {
			m_StaticBufferList[i].pt_IndexBuffer->Release();
			m_StaticBufferList[i].pt_IndexBuffer = nullptr;
		}
	}
	for (unsigned int i = 0; i<m_TexturesCount; i++)
	{
		if (m_texture[i].fileName) {
			delete[]m_texture;
			m_texture[i].fileName = NULL;
		}
		if (m_texture->image)
		{
			m_texture[i].image->Release();
			m_texture[i].image = NULL;
		}
	}
	m_TexturesCount = 0;
	m_StaticBufferCount = 0;
	if (m_texture)
	{
		delete[] m_texture;
		m_texture = NULL;
	}
	if (m_StaticBufferList) {
		delete[] m_StaticBufferList;
		m_StaticBufferList = nullptr;
	}
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
	if (staticID > m_StaticBufferCount)
	{
		return;
	}
	if (m_ActiveBufferCount != staticID)
	{
		if (m_StaticBufferList[staticID].pt_IndexBuffer != nullptr)
		{
			m_Direct3DDevice->SetIndices(m_StaticBufferList[staticID].pt_IndexBuffer);
		}
		m_Direct3DDevice->SetStreamSource(0, m_StaticBufferList[staticID].pt_VertexBuffer, 0, m_StaticBufferList[staticID].stride);//0为第一个数据流,0为第一个顶点
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
				return;
			}
			break;
		case TRANGLE_STRIP:
			if (FAILED(m_Direct3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, (int)m_StaticBufferList[staticID].numVertexs / 2))) {
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

int D3DRender::AddTexture2D(wchar_t* file, int* texID) {
	if (!file || !m_Direct3DDevice){
		return 0;
	}
	size_t len = wcslen(file);
	if (!len){
		return 0;
	}
	unsigned int index = m_TexturesCount;
	if (!m_texture){
		m_texture = new meshTexture[1];
		if (!m_texture){
			return 0;
		}
	}
	else {
		meshTexture* temp;
		temp = new meshTexture[m_TexturesCount + 1];
		memcpy(temp, m_texture, sizeof(meshTexture)*m_TexturesCount);

		delete[] m_texture;
		m_texture = temp;
	}
	m_texture[index].fileName = new wchar_t[len];
	memcpy(m_texture[index].fileName, file, len);
	D3DCOLOR colorkey = 0xff000000;
	D3DXIMAGE_INFO info;
	if (D3DXCreateTextureFromFileEx(m_Direct3DDevice,
		file, 0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, colorkey,
		&info, NULL, &m_texture[index].image) != D3D_OK) {
		return true;
	}
	m_texture[index].width = info.Width;
	m_texture[index].height = info.Height;
	*texID = m_TexturesCount;
	m_TexturesCount++;

	return 1;
}

void D3DRender::SetTextureFilter(int index, int filter, int val) {
	if (!m_Direct3DDevice || index < 0) {
		return;
	}
	D3DSAMPLERSTATETYPE fil = D3DSAMP_MINFILTER;
	int v = D3DTEXF_POINT;

	if (filter==MIN_FILTER)
	{
		fil = D3DSAMP_MINFILTER;
	}
	else if (filter == MAG_FILTER)
	{
		fil = D3DSAMP_MAGFILTER;
	}else if (filter == MIP_FILTER)
	{
		fil = D3DSAMP_MIPFILTER;
	}
	
	if (val == POINT_TYPE)
	{
		v = D3DTEXF_POINT;
	}else if (val== LINEAR_TYPE)
	{
		v = D3DTEXF_LINEAR;
	}else if (val == ANISOTROPIC_TYPE)
	{
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
	if (!m_Direct3DDevice)
	{
		return;
	}
	if (index<0||texID<0)
	{
		m_Direct3DDevice->SetTexture(0, NULL);
	}
	else {
		m_Direct3DDevice->SetTexture(index, m_texture[index].image);
	}
}

void D3DRender::SaveScreenShot(wchar_t* file) {
	if (!file)
	{
		return;
	}
	IDirect3DSurface9* surface = NULL;
	D3DDISPLAYMODE mode;
	m_Direct3DDevice->GetDisplayMode(0, &mode);
	m_Direct3DDevice->CreateOffscreenPlainSurface(mode.Width, mode.Height, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &surface, NULL);
	m_Direct3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &surface);
	D3DXSaveSurfaceToFile(file, D3DXIFF_JPG, surface, NULL, NULL);
	if (surface!=NULL)
	{
		surface->Release();
		surface = nullptr;
	}
}
void D3DRender::EnablePointSprites(float size, float min, float a, float b, float c) {
	if (!m_Direct3DDevice)
	{
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
