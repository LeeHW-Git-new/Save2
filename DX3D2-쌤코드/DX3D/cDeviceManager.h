#pragma once

#define g_pDeviceManager cDeviceManager::GetInstance()
#define g_pD3DDevice cDeviceManager::GetInstance()->GetDevice()
class cDeviceManager
{
	Singletone(cDeviceManager);

private:
	LPDIRECT3D9	m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3Device;
public:
	LPDIRECT3DDEVICE9 GetDevice();
	void Destroy();
};

