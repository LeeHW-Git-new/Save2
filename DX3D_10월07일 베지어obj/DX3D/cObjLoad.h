#pragma once
class cObjLoad
{

protected:
	vector<D3DXVECTOR3> m_vecVertexList;
	vector<D3DXVECTOR3> m_vecTextureList;
	vector<D3DXVECTOR3> m_vecNormalList;

	vector<face> m_vecFace;
	vector<ST_PNT_VERTEX> m_vecVertexPTNList;

	D3DMATERIAL9                m_stMtl01;
	LPDIRECT3DTEXTURE9            m_Texture;


public:
	cObjLoad();
	~cObjLoad();

	void Setup();
	void Update();
	void Render();

	void objFileLoad();
	void mtlFileLoad();
};

