#pragma once
class cRay
{
public:
	cRay();
	~cRay();
	enum
	{
		E_NONE,
		E_VIEW,
		E_WORLD,
		E_LOCAL
	};
protected:
	D3DXVECTOR3 m_vOriginal;
	D3DXVECTOR3 m_vDirection;
public:
	static cRay RayAtViewSpace(int nScreenX, int nScreenY);
	static cRay RayAtWorldSpace(int nScreenX, int nScreenY);
	bool IsPicked(D3DXVECTOR3& vSphereCenter, float fSphereRadius);
	bool IntersectTri(IN D3DXVECTOR3 & v0, 
		IN D3DXVECTOR3 & v1, 
		IN D3DXVECTOR3 & v2, 
		OUT D3DXVECTOR3 vPickedPostion);
	cRay Transform(D3DXMATRIXA16& mat);
};

