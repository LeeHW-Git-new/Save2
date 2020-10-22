#include "stdafx.h"
#include "ObjLoader.h"


ObjLoader::ObjLoader()
{
}


ObjLoader::~ObjLoader()
{
}

void ObjLoader::Render()
{

	D3DXMATRIXA16 matWorld, matS;
	D3DXMatrixIdentity(&matWorld);
	m_vecVertexPNTList;
	//스케일 만들어서 world에 곱해주기
	D3DXMatrixScaling(&matS, 0.2f, 0.2f, 0.2f);
	matWorld = matS;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTexture(0, m_Texture);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertexPNTList.size() / 3, &m_vecVertexPNTList[0], sizeof(ST_PNT_VERTEX));
	g_pD3DDevice->SetTexture(0, NULL);

}

void ObjLoader::Update()
{
}

void ObjLoader::Setup()
{
	objFileLoad();
	mtlFileLoad();
}

void ObjLoader::objFileLoad()
{
	FILE* fp;
	fp = fopen("../obj/box.obj", "r");
	char GetObj[256];
	D3DXVECTOR3 v;

	while (fscanf(fp, "%s %f %f %f", &GetObj, &v.x, &v.y, &v.z) != EOF)
	{
		if (GetObj[0] == 'v' && GetObj[1] == NULL)
		{
			m_vecVertexList.push_back(v);
		}
		if (GetObj[0] == 'v' && GetObj[1] == 't'&& GetObj[2] == NULL)
		{
			m_vecTextureList.push_back(v);
		}
		if (GetObj[0] == 'v' && GetObj[1] == 'n' && GetObj[2] == NULL)
		{
			m_vecNormalList.push_back(v);
		}
	}
	fseek(fp, 0, SEEK_SET);

	face face1, face2, face3;
	ST_PNT_VERTEX vPNT;
	while (fscanf(fp, "%s %d/%d/%d %d/%d/%d %d/%d/%d", &GetObj,
		&face1.v, &face1.t, &face1.n,
		&face2.v, &face2.t, &face2.n,
		&face3.v, &face3.t, &face3.n) != EOF)
	{
		if (GetObj[0] == 'f' && (GetObj[1] == NULL))
		{
			m_vecface.push_back(face1);
			m_vecface.push_back(face2);
			m_vecface.push_back(face3);
		}
	}

	for (int i = 0; i < 36; i++)
	{
		vPNT.p = m_vecVertexList[m_vecface[i].v - 1];
		vPNT.t.x = m_vecTextureList[m_vecface[i].t - 1].x;
		vPNT.t.y = m_vecTextureList[m_vecface[i].t - 1].y;
		vPNT.n = m_vecNormalList[m_vecface[i].n - 1];
		m_vecVertexPNTList.push_back(vPNT);
	}

	fclose(fp);
}

void ObjLoader::mtlFileLoad()
{
	
	FILE* fp;
	fp = fopen("../obj/box.mtl", "r");
	char GetMtl[256];
	D3DXCOLOR color;
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	
	color.a = 1.f;
	while (fscanf(fp, "%s %f %f %f", &m_stMtl, &color.r, &color.g, &color.b) != EOF)
	{
		if (strcmp(GetMtl, "Ka") == 0)
		{
			m_stMtl.Ambient = color;
		}
		if (strcmp(GetMtl, "Kd") == 0)
		{
			m_stMtl.Diffuse = color;
		}
		if (strcmp(GetMtl, "Ks") == 0)
		{
			m_stMtl.Specular = color;
			break;
		}
	}
	char name[256];
	while (fscanf(fp, "%s %s", &GetMtl, &name)!=EOF)
	{
		if (strcmp(GetMtl, "map_Kd") == 0)
		{
			break;
		}
	}
	char root[50] = "../obj/";
	strcat(root, name);
	wchar_t destination[256] = L"";
	ZeroMemory(&destination, sizeof(wstring));

	mbstowcs(destination, root, strlen(root) * sizeof(char));
	D3DXCreateTextureFromFile(g_pD3DDevice, destination, &m_Texture);
	
}
