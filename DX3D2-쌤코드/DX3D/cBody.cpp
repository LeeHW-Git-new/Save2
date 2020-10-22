#include "stdafx.h"
#include "cBody.h"
#include "cCube.h"


cBody::cBody()
	: m_vPosition(0, 0, 0)
	, m_vDirection(0, 0, 1)
	, m_fRotY(0.f)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cBody::~cBody()
{
	for each(auto p in parts)
	{
		SafeDelete(p);
	}
	parts.clear();
}

void cBody::Setup()
{
	cCube* body = new cCube(&m_matWorld, D3DXVECTOR3(0,5,0), D3DXVECTOR3(1.5, 1.5, 1));
	parts.push_back(body);

	cCube* head = new cCube(&m_matWorld, D3DXVECTOR3(0, 7.5, 0),D3DXVECTOR3(1,1,1));
	parts.push_back(head);

	cCube* Rarm = new cCube(&m_matWorld, D3DXVECTOR3(2, 5, 0), D3DXVECTOR3(0.5, 1.5, 0.8));
	parts.push_back(Rarm);

	cCube* Larm = new cCube(&m_matWorld, D3DXVECTOR3(-2, 5, 0), D3DXVECTOR3(0.5, 1.5, 0.8));
	parts.push_back(Larm);

	cCube* RLag = new cCube(&m_matWorld, D3DXVECTOR3(1, 2, 0), D3DXVECTOR3(0.5, 1.5, 0.8));
	parts.push_back(RLag);

	cCube* LLag = new cCube(&m_matWorld, D3DXVECTOR3(-1, 2, 0), D3DXVECTOR3(0.5, 1.5, 0.8));
	parts.push_back(LLag);

	for (auto part : parts)
		part->Setup();
}

void cBody::Update()
{
	if (GetKeyState('A') & 0x8000)
	{
		m_fRotY -= 0.1f;
	}

	if (GetKeyState('D') & 0x8000)
	{
		m_fRotY += 0.1f;
	}

	if (GetKeyState('W') & 0x8000)
	{
		m_vPosition += (m_vDirection*0.1f);
	}

	if (GetKeyState('S') & 0x8000)
	{
		m_vPosition -= (m_vDirection*0.1f);
	}

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matR * matT;

	for (auto part : parts)
	{
		part->Update();
	}


}

void cBody::Render()
{
	for (auto part : parts)
	{
		part->Render();
	}
}

D3DXVECTOR3 & cBody::GetPosition()
{
	return this->m_vPosition;
}
