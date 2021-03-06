#include "stdafx.h"


cDeviceManager::cDeviceManager()
	:m_pD3D(NULL)
	, m_pD3Device(NULL)
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DCAPS9 stCaps;
	int nVertexProcessing = 0;
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stCaps);

	if (stCaps.DevCaps& D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS stD3DPP;
	ZeroMemory(&stD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	stD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stD3DPP.Windowed = TRUE;
	stD3DPP.BackBufferFormat = D3DFMT_UNKNOWN;
	stD3DPP.AutoDepthStencilFormat = D3DFMT_D16;
	stD3DPP.EnableAutoDepthStencil = TRUE;
	m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&stD3DPP, &m_pD3Device);
}


cDeviceManager::~cDeviceManager()
{

}

LPDIRECT3DDEVICE9 cDeviceManager::GetDevice()
{
	return m_pD3Device;
}

void cDeviceManager::Destroy()
{
	SafeRelease(m_pD3D);
	SafeRelease(m_pD3Device);
}
