#include "stdafx.h"
#include "Heightmap.h"


Heightmap::Heightmap()
{
}


Heightmap::~Heightmap()
{
}

void Heightmap::Setup(wstring FileName)
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.f);
	m_stMtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.f);
	m_stMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.f);

	D3DXCreateTextureFromFile(g_pD3DDevice, _T("../HeightMapData/terrain.jpg"), &m_pTexture);

	LoadRaw(FileName);
	m_height = m_width = sqrtl(m_vecVertex.size());

	int TileNum = m_height - 1;
	int interval = 1;

	for (int i = 0; i < TileNum + 1; i++)
	{
		for (int j = 0; j < TileNum + 1; j++)
		{
			m_vecVertex[i*(TileNum + 1) + j].p.x = j;
			m_vecVertex[i*(TileNum + 1) + j].p.z = i;

			m_vecVertex[i*(TileNum + 1) + j].t.y = i / (float)TileNum + 1;
			m_vecVertex[i*(TileNum + 1) + j].t.x = j / (float)TileNum + 1;
		}
	}

	for (int i = 0; i < TileNum; i++)
	{
		for (int j = 0; j < TileNum; j++)
		{
			D3DXVECTOR3 a = m_vecVertex[i*(TileNum + 1) + j].p - m_vecVertex[(i + 1) *(TileNum + 1) + j].p;
			D3DXVECTOR3 b = m_vecVertex[i*(TileNum + 1) + j].p - m_vecVertex[i*(TileNum + 1) + (j + 1)].p;
			D3DXVECTOR3 n;
			D3DXVec3Cross(&n, &a, &b);

			m_vecDrawVertex.push_back(m_vecVertex[i*(TileNum + 1) + j]);
			m_vecDrawVertex[m_vecDrawVertex.size() - 1].n = n;
			m_vecDrawVertex.push_back(m_vecVertex[(i + 1) *(TileNum + 1) + j]);
			m_vecDrawVertex[m_vecDrawVertex.size() - 1].n = n;
			m_vecDrawVertex.push_back(m_vecVertex[i*(TileNum + 1) + (j + 1)]);
			m_vecDrawVertex[m_vecDrawVertex.size() - 1].n = n;

			a = m_vecVertex[(i + 1)*(TileNum + 1) + (j + 1)].p - m_vecVertex[i*(TileNum + 1) + (j + 1)].p;
			b = m_vecVertex[(i + 1)*(TileNum + 1) + (j + 1)].p - m_vecVertex[(i + 1)*(TileNum + 1) + j].p;
			D3DXVec3Cross(&n, &a, &b);

			m_vecDrawVertex.push_back(m_vecVertex[(i + 1)*(TileNum + 1) + (j + 1)]);
			m_vecDrawVertex[m_vecDrawVertex.size() - 1].n = n;
			m_vecDrawVertex.push_back(m_vecVertex[i*(TileNum + 1) + (j + 1)]);
			m_vecDrawVertex[m_vecDrawVertex.size() - 1].n = n;
			m_vecDrawVertex.push_back(m_vecVertex[(i + 1)*(TileNum + 1) + j]);
			m_vecDrawVertex[m_vecDrawVertex.size() - 1].n = n;

		}
	}

}

void Heightmap::LoadRaw(wstring FileName)
{
	ifstream fin;
	fin.open(FileName, ios_base::binary|ios_base::in);
	if (fin.is_open())
	{
		while (true)
		{
			ST_PNT_VERTEX* newVer = new ST_PNT_VERTEX;
			newVer->p.y = fin.get() / 5.f - 17.f;
			if (fin.eof())
				break;
			m_vecVertex.push_back(*newVer);
		}
	}
	else
	{
	}
}

void Heightmap::Render()
{

}