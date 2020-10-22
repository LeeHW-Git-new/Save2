#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManage.h"
#include "cCamera.h"
#include "cCubePC.h"
#include "cGrid.h"
#include "cCubeMan.h"
#include "cLight.h"

#include "cObjLoad.h"
#include "cGroup.h"
#include "cObjMap.h"
#include "cAseLoader.h"
#include "cFrame.h"
#include "cRay.h"


cMainGame::cMainGame()
	:m_pCubePC(NULL)
	, m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pCubeMan(NULL)
	//,m_pTexture(NULL)
	, m_pMap(NULL)
	, m_pRootFrame(NULL)
	, m_ncount(0)
	, g_Fps(0)
	, m_pMeshSphere(NULL)
	, m_pMeshTeapot(NULL)
	, m_pObjMesh(NULL)
{

}


cMainGame::~cMainGame()
{
	SafeDelete(m_pCubePC);
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);
	SafeDelete(m_pCubeMan);
	//SafeRelease(m_pTexture);
	SafeDelete(m_pMap);
	SafeRelease(m_pMeshSphere);
	SafeRelease(m_pMeshTeapot);
	SafeRelease(m_pObjMesh);

	for each(auto p in m_vecObjMtlTex)
	{
		SafeRelease(p);
	}

	for each(auto p in m_vecGroup)
	{
		SafeRelease(p);
	}
	m_vecGroup.clear();
	m_pRootFrame->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	m_nTime = GetTickCount();


	m_pCubePC = new cCubePC;
	m_pCubePC->Setup();

	m_pCubeMan = new cCubeMan;
	m_pCubeMan->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_pCubeMan->GetPosition());

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	for (int i = 0; i < 5; i++)
	{
		D3DXVECTOR3 vSpherePos(0, 0, i*2.0f);
		ST_SPHERE sphere;
		sphere.vCenter = vSpherePos;
		sphere.fRadius = 1.0f;
		sphere.isPicked = false;

		D3DXCreateSphere(g_pD3DDevice, sphere.fRadius, 10, 10, &sphere.m_pSphere, nullptr);
		m_vecSphere.push_back(sphere);
	}
	

	m_pLight = new cLight;
	m_pLight->Setup();
	//m_pLight->DirectionalLight();
	//m_pLight->SpotLight();
	//m_pLight->PointLight();

	//Setup_MeshObject();

	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 45;
	fd.Width = 28;
	fd.Weight = FW_MEDIUM;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	//strcpy_s(fd.FaceName, "궁서체");   //글꼴 스타일
	AddFontResource(L"umberto.ttf");
	strcpy((char*)fd.FaceName, "umberto");

	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);

	//Setup_Obj();

	{
		cAseLoader l;
		m_pRootFrame = l.Load("woman/woman_01_all.ASE");
	}


	ZeroMemory(&stWhiteMtl, sizeof(D3DMATERIAL9));
	stWhiteMtl.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stWhiteMtl.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stWhiteMtl.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	ZeroMemory(&stRedMtl, sizeof(D3DMATERIAL9));
	stRedMtl.Ambient = D3DXCOLOR(0.8f, 0.0f, 0.0f, 1.0f);
	stRedMtl.Diffuse = D3DXCOLOR(0.8f, 0.0f, 0.0f, 1.0f);
	stRedMtl.Specular = D3DXCOLOR(0.8f, 0.0f, 0.0f, 1.0f);


	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);



}

void cMainGame::Update()
{
	
	if (m_pCubePC)
		m_pCubePC->Update();
	

	if (m_pCubeMan)
		m_pCubeMan->Update(m_pMap);

	if (m_pCamera)
		m_pCamera->Update();

	if (m_pRootFrame)
		m_pRootFrame->Update(m_pRootFrame->GetKeyFrame(), NULL);

	if (m_pLight)
		m_pLight->Update();

}

void cMainGame::Render()
{
	m_ncount++;

	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(47, 121, 112), 1.0F, 0);

	g_pD3DDevice->BeginScene();

	if (m_pGrid)
		m_pGrid->Render();

	if (GetTickCount() - m_nTime >= 1000)
	{
		m_nTime = GetTickCount();
		g_Fps = m_ncount;
		m_ncount = 0;
	}


	if (m_pFont)
	{
		RECT rc;
		SetRect(&rc, 100, 100, 103, 103);
		char szTemp[1024];
		sprintf(szTemp, "FPS = %d", g_Fps);
		m_pFont->DrawTextA(nullptr,
			szTemp,
			strlen(szTemp),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 0, 0));
	}

	if (m_pCubeMan)
		m_pCubeMan->Render();


	for (int i = 0; i < m_vecSphere.size(); ++i)
	{
		D3DXMATRIXA16 matWorld, matT;
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixIdentity(&matT);
		D3DXMatrixTranslation(&matT, 0, 0, (i*2.0f));
		matWorld = matWorld * matT;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		if (m_vecSphere[i].isPicked)
			g_pD3DDevice->SetMaterial(&stRedMtl);
		else
			g_pD3DDevice->SetMaterial(&stWhiteMtl);
		m_vecSphere[i].m_pSphere->DrawSubset(0);
	}

		if (m_pRootFrame)
			m_pRootFrame->Render();

		//Obj_Render();
		//Mesh_Render();


	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		cRay r = cRay::RayAtWorldSpace(LOWORD(lParam), HIWORD(lParam));
		for (size_t i = 0; i < m_vecSphere.size(); ++i)
		{
			if (r.IsPicked(m_vecSphere[i].vCenter, m_vecSphere[i].fRadius))
				m_vecSphere[i].isPicked ^= 1;
		}
	}
	break;
	}
}

void cMainGame::Setup_Obj()
{
	cObjLoad l;
	l.Load(m_vecGroup, "obj", "Map.obj");

	Load_Surface();
}

void cMainGame::Obj_Render()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.03f, 0.03f, 0.03f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);

	matWorld = matS * matR;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	for each(auto p in m_vecGroup)
	{
		p->Render();
	}

	//D3DXIntersectTri(v1, v2, v3, rayPos, rayDir, u, v, f);
	//바닥 정점 정보 v1, v2, v3;모든 폴리곤을 검사
}

void cMainGame::Load_Surface()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.03f, 0.03f, 0.03f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	matWorld = matS * matR;
	m_pMap = new cObjMap("obj", "map_surface.obj", &matWorld);

}

void cMainGame::Setup_MeshObject()
{
	D3DXCreateTeapot(g_pD3DDevice, &m_pMeshTeapot,NULL);
	D3DXCreateSphere(g_pD3DDevice,0.5f,10,10,&m_pMeshSphere, NULL);
	ZeroMemory(&m_stMtlTeapot, sizeof(D3DMATERIAL9));
	m_stMtlTeapot.Ambient = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_stMtlTeapot.Diffuse = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_stMtlTeapot.Specular = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);

	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.f, 1.0f);
	m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.f, 1.0f);
	m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.f, 1.0f);

	cObjLoad l;
	m_pObjMesh = l.LoadMesh(m_vecObjMtlTex , "obj" , "map.obj");
}

void cMainGame::Mesh_Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTexture(0, NULL);
	
	D3DXMATRIXA16 matWorld, matS, matR;
	{
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		matWorld = matS * matR;
		D3DXMatrixTranslation(&matWorld, 0, 0, 10);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetMaterial(&m_stMtlTeapot);
		m_pMeshTeapot->DrawSubset(0);
	}

	{
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		matWorld = matS * matR;
		D3DXMatrixTranslation(&matWorld, 5, 0, 0);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetMaterial(&m_stMtlSphere);
		m_pMeshSphere->DrawSubset(0);
	}

	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
		D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);
		matWorld = matS * matR;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		for (size_t i = 0; i < m_vecObjMtlTex.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&m_vecObjMtlTex[i]->GetMaterial());
			g_pD3DDevice->SetTexture(0, m_vecObjMtlTex[i]->GetTexture());

			m_pObjMesh->DrawSubset(i);
		}
	}
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
