#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManage.h"
#include "cCamera.h"
#include "cCubePC.h"
#include "cGrid.h"
#include "cCubeMan.h"
#include "cLight.h"
#include "bezier.h"
#include "cObjLoad.h"

cMainGame::cMainGame()
	:m_pCubePC(NULL)
	,m_pCamera(NULL)
	,m_pGrid(NULL)
	,m_pCubeMan(NULL)
	//,m_pTexture(NULL)
	, m_pBezier(NULL)
{

}


cMainGame::~cMainGame()
{
	SafeDelete(m_pCubePC);
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);
	SafeDelete(m_pCubeMan);
	//SafeRelease(m_pTexture);
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{

	m_pCubePC = new cCubePC;
	m_pCubePC->Setup();

	m_pCubeMan = new cCubeMan;
	m_pCubeMan->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_pCubePC->GetPosition());


	m_pGrid = new cGrid;
	m_pGrid->Setup();

	
	m_pLight = new cLight;
	m_pLight->Setup();
	m_pLight->DirectionalLight();
	m_pLight->SpotLight();
	m_pLight->PointLight();

	m_pBezier = new bezier;
	m_pBezier->Setup();
	
	
	m_pObjLoad = new cObjLoad;
	m_pObjLoad->Setup();
	



	// >> : texture
	/*
	{
		D3DXCreateTextureFromFile(g_pD3DDevice, L"../image/수지.png", &m_pTexture);
		ST_PT_VERTEX v;
		v.p = D3DXVECTOR3(0, 0, 0);	//월드의 좌표
		v.t = D3DXVECTOR2(0, 1);	//수지 이미지상의 좌표
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(0, 2, 0);
		v.t = D3DXVECTOR2(0, 0);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(2, 2, 0);
		v.t = D3DXVECTOR2(1, 0);
		m_vecVertex.push_back(v);
	}
	*/
	// << :

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);


}

void cMainGame::Update()
{
	/*
	if (m_pCubePC)
		m_pCubePC->Update();
	*/

	/*
	if (m_pCubeMan)
		m_pCubeMan->Update();

	*/

	if (m_pCamera)
		m_pCamera->Update();

	if (m_pLight)
		m_pLight->Update();
	
	if (m_pBezier)
		m_pBezier->Update();

}

void cMainGame::Render()
{
	
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(47, 121, 112), 1.0F, 0);

	g_pD3DDevice->BeginScene();

	if (m_pGrid)
		m_pGrid->Render();

	/*
	if (m_pCubePC)
		m_pCubePC->Render();
	*/
	/*
	if (m_pCubeMan)
		m_pCubeMan->Render();
	*/

	if (m_pBezier)
		m_pBezier->Render();

	
	if (m_pObjLoad)
		m_pObjLoad->Render();
	
	//Draw_Texture();


	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

/*
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
*/

