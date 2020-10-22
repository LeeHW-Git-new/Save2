#include "stdafx.h"
#include "bezier.h"
#include "cCubeMan.h"

bezier::bezier()
	:center(4.0f, 0.0f, 0.0f)
	,m_pCubeMan(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}


bezier::~bezier()
{
}

void bezier::Setup()
{
	ST_PC_VERTEX v;
	v.p = center;
	v.c = D3DCOLOR_XRGB(0,255,0);
	m_vecVertexGreen.push_back(v);

	//육각형 그리기
	D3DXMATRIX rotateYMat;
	for (int i = 0; i <6; i++) 
	{
		D3DXMatrixRotationY(&rotateYMat, 60 * D3DX_PI / 180);
		D3DXVec3TransformNormal(&center, &center, &rotateYMat);
		v.p = center;
		m_vecVertexGreen.push_back(v);
	}

	ST_PC_VERTEX v2;
	float tempT = 0;
	float tempT2 = 0;
	float split = 100;
	//2차 베지어(3개의 점)
	for (int i = 0; i < 3; i++)
	{
		for (float t = 0; t <= 1; t += 1.0f/split)
		{
			tempT = 1 - t;
			tempT2 = pow(tempT, 2);
			v2.p = (tempT2 * m_vecVertexGreen[i*2].p) + (2 * t * tempT*m_vecVertexGreen[i*2 + 1].p) + (pow(t, 2) * m_vecVertexGreen[i*2+2].p);

			m_vecVertexRed.push_back(v2);
		}
	}

	m_pCubeMan = new cCubeMan;
	m_pCubeMan->Setup();




}

void bezier::Update()
{
	if (m_pCubeMan)
		m_pCubeMan->Update2();
	//현재 원점
	//m_vecVertexGeen[0]으로 이동시키기

	//m_vecVertexGeen[0] - 원점 = 방향벡터
	//m_Position -= m_Direction * 0.01f
	//Draw
}

void bezier::Render()
{
	if (m_pCubeMan)
		m_pCubeMan->Render();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, m_vecVertexGreen.size()-1, &m_vecVertexGreen[0], sizeof(ST_PC_VERTEX));
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, m_vecVertexRed.size() - 1, &m_vecVertexRed[0], sizeof(ST_PC_VERTEX));
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}
