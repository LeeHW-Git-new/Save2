#include "stdafx.h"
#include "cMainGame.h"
#include "cCube.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cBody.h"
cMainGame::cMainGame()
	:m_pCube(NULL)
	,m_pCamera(NULL)
	,m_pGrid(NULL)
	,m_pBody(NULL)
{
}


cMainGame::~cMainGame()
{
	SafeDelete(m_pCube);
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);
	SafeDelete(m_pBody);
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	//m_pCube = new cCube;
	//m_pCube->Setup();

	m_pBody = new cBody;
	m_pBody->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_pBody->GetPosition());
	
	m_pGrid = new cGrid;
	m_pGrid->Setup();
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}

void cMainGame::Update()
{
	//if (m_pCube)
	//	m_pCube->Update();

	if (m_pBody)
		m_pBody->Update();

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

	if (m_pBody)
		m_pBody->Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

		return;
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera != NULL)
		m_pCamera->WndProc(hWnd,message,wParam,lParam);
}

