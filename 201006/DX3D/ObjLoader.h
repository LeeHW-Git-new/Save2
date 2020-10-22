#pragma once
#include "cCube.h"

class ObjLoader
{
protected:
	vector<D3DXVECTOR3> m_vecVertexList;
	vector<D3DXVECTOR3> m_vecTextureList;
	vector<D3DXVECTOR3> m_vecNormalList;

	vector<face> m_vecface;
	vector<ST_PNT_VERTEX> m_vecVertexPNTList;

	D3DMATERIAL9 m_stMtl;
	LPDIRECT3DTEXTURE9 m_Texture;

public:
	ObjLoader();
	~ObjLoader();
public:
	void Render();
	void Update();
	void Setup();

	void objFileLoad();
	void mtlFileLoad();
};

