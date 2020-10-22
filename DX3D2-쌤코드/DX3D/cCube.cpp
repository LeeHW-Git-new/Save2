#include "stdafx.h"
#include "cCube.h"


cCube::cCube(D3DXMATRIXA16* bodymat, D3DXVECTOR3 Vector2Center, D3DXVECTOR3 Scale)
	: m_vPosition(Vector2Center)
	, m_fRotY(0.f)
{
	D3DXMatrixIdentity(&m_matWorld);
	m_BodyWorld = bodymat;
	D3DXMatrixScaling(&m_Scale, Scale.x, Scale.y, Scale.z);
}


cCube::~cCube()
{
}

void cCube::Setup()
{
	ST_PC_VERTEX v;
	// 앞면
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.f, 1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, -1.f, -1.f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.f, -1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, -1.f);
	m_vecVertex.push_back(v);
	// 뒤
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.f, -1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, 1.f, 1.f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.f, -1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, 1.f);
	m_vecVertex.push_back(v);

	// 왼
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.f, -1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, 1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, 1.f, -1.f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.f, -1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, 1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, -1.f, -1.f);
	m_vecVertex.push_back(v);

	//오른
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(1.f, -1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, 1.f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(1.f, -1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, 1.f);
	m_vecVertex.push_back(v);

	//위
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.f, 1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, 1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, 1.f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.f, 1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, 1.f, -1.f);
	m_vecVertex.push_back(v);

	//아래
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.f, -1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, -1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, -1.f);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.f, -1.f, 1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, -1.f);
	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, 1.f);
	m_vecVertex.push_back(v);

}

void cCube::Update()
{

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);


	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = m_Scale* matR * matT * (*m_BodyWorld);

}

void cCube::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0],
		sizeof(ST_PC_VERTEX));

}

D3DXVECTOR3& cCube::GetPosition()
{
	return this->m_vPosition;
}