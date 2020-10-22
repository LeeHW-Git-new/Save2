#include "stdafx.h"
#include "cRay.h"


cRay::cRay()
{
}


cRay::~cRay()
{
}

cRay cRay::RayAtViewSpace(int nScreenX, int nScreenY)
{
	D3DVIEWPORT9 ViewPort;
	g_pD3DDevice->GetViewport(&ViewPort);
	D3DXMATRIXA16 MatProjection;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &MatProjection);

	cRay r;
	r.m_vDirection.x = ((2.0f * nScreenX) / ViewPort.Width - 1.0f) / MatProjection._11;
	r.m_vDirection.y = ((-2.0f * nScreenX) / ViewPort.Height + 1.0f) / MatProjection._22;
	r.m_vDirection.z = 1.0f;

	return r;
}

cRay cRay::RayAtWorldSpace(int nScreenX, int nScreenY)
{
	cRay r = cRay::RayAtViewSpace(nScreenX, nScreenY);

	D3DXMATRIXA16 matView, matInvView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInvView, 0, &matView);

	D3DXVec3Normalize(&r.m_vDirection, &r.m_vDirection);

	return r.Transform(matInvView);
}

bool cRay::IsPicked(D3DXVECTOR3& vSphereCenter, float fSphereRadius)
{
	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixTranslation(&matInvWorld, -vSphereCenter.x, -vSphereCenter.y, -vSphereCenter.z);
	cRay r = Transform(matInvWorld);

	float vv = D3DXVec3Dot(&m_vDirection, &m_vDirection);
	float qv = D3DXVec3Dot(&m_vOriginal, &m_vDirection);
	float qq = D3DXVec3Dot(&m_vOriginal, &m_vOriginal);
	float rr = fSphereRadius * fSphereRadius;


	return qv * qv - vv * (qq - rr) >= 0;
}

bool cRay::IntersectTri(IN D3DXVECTOR3 & v0, IN D3DXVECTOR3 & v1, IN D3DXVECTOR3 & v2, OUT D3DXVECTOR3 vPickedPostion)
{
	cRay r = (*this);
	float u, v, t;
	bool b = D3DXIntersectTri(&v0, &v1, &v2, &m_vOriginal, &m_vDirection, &u, &v, &t);
	vPickedPostion = m_vOriginal + (t*m_vDirection);

	return b;
}

cRay cRay::Transform(D3DXMATRIXA16 & mat)
{
	cRay r = (*this);
	D3DXVec3TransformNormal(&r.m_vDirection, &r.m_vDirection, &mat);
	D3DXVec3TransformCoord(&r.m_vOriginal, &r.m_vOriginal, &mat);
	D3DXVec3Normalize(&r.m_vDirection, &r.m_vDirection);
	return r;
}
