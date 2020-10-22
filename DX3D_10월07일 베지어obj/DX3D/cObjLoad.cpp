#include "stdafx.h"
#include "cObjLoad.h"



cObjLoad::cObjLoad()
{
}


cObjLoad::~cObjLoad()
{
}

void cObjLoad::Setup()
{
	objFileLoad();
	mtlFileLoad();
}

void cObjLoad::Update()
{
}

void cObjLoad::Render()
{
	D3DXMATRIXA16 matWorld, matS;
	D3DXMatrixIdentity(&matWorld);
	m_vecVertexPTNList;
	//스케일 만들어서 world에 곱해주기
	D3DXMatrixScaling(&matS, 0.2f, 0.2f, 0.2f);
	matWorld = matS;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->SetMaterial(&m_stMtl01);
	g_pD3DDevice->SetTexture(0, m_Texture);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertexPTNList.size() / 3, &m_vecVertexPTNList[0], sizeof(ST_PNT_VERTEX));
	g_pD3DDevice->SetTexture(0, NULL);
}

void cObjLoad::objFileLoad()
{
	FILE* fp;
	fp = fopen("../obj/box.obj", "r");
	char getObj[256];
	D3DXVECTOR3 v;


	while (fscanf(fp, "%s %f %f %f", &getObj, &v.x, &v.y, &v.z) != EOF)
	{
		if (getObj[0] == 'v' && getObj[1] == NULL)
		{
			m_vecVertexList.push_back(v);
		}
		if (getObj[0] == 'v' && getObj[1] == 't' && getObj[2] == NULL) 
		{
			m_vecTextureList.push_back(v);
		}
		if (getObj[0] == 'v' && getObj[1] == 'n' && getObj[2] == NULL) 
		{
			m_vecNormalList.push_back(v);
		}
	}
	//MessageBox(g_hWnd, L"check", L"check", MB_YESNO);

	fseek(fp, 0, SEEK_SET);
	
	face face1, face2, face3;
	ST_PNT_VERTEX vPTN;
	while (fscanf(fp, "%s %d/%d/%d %d/%d/%d %d/%d/%d", 
		&getObj, &face1.v, &face1.t, &face1.n
		,&face2.v, &face2.t, &face2.n
		,&face3.v, &face3.t, &face3.n) != EOF)
	{
		if ((getObj[0] =='f') && (getObj[1] == NULL))
		{
			m_vecFace.push_back(face1);
			m_vecFace.push_back(face2);
			m_vecFace.push_back(face3);
		}
			
	}

	
	for (int i = 0; i < 36; i++)
	{
		vPTN.p = m_vecVertexList[m_vecFace[i].v - 1];
		
		vPTN.t.x = m_vecTextureList[m_vecFace[i].t - 1].x;
		vPTN.t.y = m_vecTextureList[m_vecFace[i].t - 1].y;

		vPTN.n = m_vecNormalList[m_vecFace[i].n - 1];
		m_vecVertexPTNList.push_back(vPTN);
	}
	

	fclose(fp);

}

void cObjLoad::mtlFileLoad()
{
	FILE* fp;
	fp = fopen("../obj/box.mtl", "r");
	char getMtl[256];
	D3DXCOLOR color;
	ZeroMemory(&m_stMtl01, sizeof(D3DMATERIAL9));

	color.a = 1.0f;
	while (fscanf(fp, "%s %f %f %f", &getMtl, &color.r, &color.g, &color.b)) 
	{
		
		if (strcmp(getMtl, "Ka") == 0)
		{
			m_stMtl01.Ambient = color;
		}
		if (strcmp(getMtl, "Kd") == 0) 
		{
			m_stMtl01.Diffuse = color;
		}
		if (strcmp(getMtl, "Ks") == 0) 
		{
			m_stMtl01.Specular = color;
			break;
		}
	}
	char name[256];
	while (fscanf(fp, "%s %s", &getMtl, &name))
	{
		if (strcmp(getMtl, "map_Kd") == 0) 
		{
			break;
		}
	}

	char root[50] = "../obj/";
	strcat(root, name);
	wchar_t destination[256] = L"";
	ZeroMemory(&destination,sizeof(wstring));

	mbstowcs(destination, root, strlen(root) * sizeof(char));
	D3DXCreateTextureFromFile(g_pD3DDevice, destination, &m_Texture);//destination를 넣을 때 LPCWSTR형태로 넣어야한다
	//D3DXCreateTextureFromFile(g_pD3DDevice, L"../obj/box.jpg", &m_Texture);

}
