#pragma once
class Heightmap
{
private:
	int m_height;
	int m_width;

	vector<ST_PNT_VERTEX> m_vecVertex;
	vector<ST_PNT_VERTEX> m_vecDrawVertex;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DMATERIAL9 m_stMtl;

public:
	Heightmap();
	~Heightmap();
	void Setup(wstring FileName);
	void LoadRaw(wstring FileName);
	void Render();
};

