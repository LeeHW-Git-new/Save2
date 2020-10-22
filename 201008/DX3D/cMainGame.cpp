#include "stdafx.h"
#include "cMainGame.h"
#include "cCube.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCubeMan.h"
#include "cGroup.h"
#include "cObjLoader.h"


cMainGame::cMainGame()
	:m_pCube(NULL)
	,m_pCamera(NULL)
	,m_pGrid(NULL)
	, m_pCubeMan(NULL)
	,m_pTexture(NULL)
{
}


cMainGame::~cMainGame()
{
	SafeDelete(m_pCube);
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);
	SafeDelete(m_pCubeMan);
	SafeRelease(m_pTexture);

	for each(auto p in m_vecGroup)
	{
		SafeRelease(p);
	}
	m_vecGroup.clear();
	g_pObjectManager->Destroy();

	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	//m_pCube = new cCube;
	//m_pCube->Setup();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	m_pCubeMan = new cCubeMan;
	m_pCubeMan->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_pCubeMan->GetPosition());
	
	m_pGrid = new cGrid;
	m_pGrid->Setup();
	
	{
		D3DXCreateTextureFromFile(g_pD3DDevice, L"2020_09_28_mumbo-jumbo-with-mask-15377344.png", &m_pTexture);
		ST_PT_VERTEX v;

		v.p = D3DXVECTOR3(0, 0, 0);
		v.t = D3DXVECTOR2(0, 1);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(0, 1, 0);
		v.t = D3DXVECTOR2(0, 0);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(1, 1, 0);
		v.t = D3DXVECTOR2(1, 0);
		m_vecVertex.push_back(v);

	}

	Setup_Obj();
	Set_Light();
}

void cMainGame::Update()
{
	//if (m_pCube)
	//	m_pCube->Update();
	if (m_pCubeMan)
		m_pCubeMan->Update();

	if (m_pCamera)
		m_pCamera->Update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(47,121,112), 1.0F, 0);
	g_pD3DDevice->BeginScene();

	if (m_pGrid)
		m_pGrid->Render();

	//if (m_pCube)
	//	m_pCube->Render();

	Obj_Render();

	if (m_pCubeMan)
		m_pCubeMan->Render();

	
	//Draw_Texture();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

		return;
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera != NULL)
		m_pCamera->WndProc(hWnd,message,wParam,lParam);
}

void cMainGame::Set_Light()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	D3DXVECTOR3 vDir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
}

void cMainGame::Draw_Texture()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PT_VERTEX));
	g_pD3DDevice->SetTexture(0, NULL);
}

void cMainGame::Setup_Obj()
{
	cObjLoader l;
	l.Load(m_vecGroup, "obj", "map.obj");
}

void cMainGame::Obj_Render()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);

	matWorld = matS*matR;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	for each(auto p in m_vecGroup)
	{
		p->Render();
	}

	//D3DXIntersectTri(v1, v2, v3, rayPos, rayDir, u, v, f);
}

