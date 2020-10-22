#pragma once
class cCubePC;
class cCamera;
class cGrid;
class cCubeMan;
class cLight;
class cGroup;
class cFrame;
class cMtlTex;

class cMainGame
{
private:
	//vector<ST_PC_VERTEX> m_vecLineVertex;
	//vector<ST_PC_VERTEX > m_vecTriangleVertex;

	cCubePC*	m_pCubePC;
	cCamera*	m_pCamera;
	cGrid*		m_pGrid;

	cCubeMan* m_pCubeMan;

	cLight* m_pLight;

	LPD3DXFONT m_pFont;
	float m_nTime;
	int m_ncount;
	int g_Fps;
	// >> :
	
	LPDIRECT3DTEXTURE9 m_pTexture;	//텍스쳐를 관리할 텍스쳐 객체
	vector<ST_PT_VERTEX> m_vecVertex;
	
	// << :
	
	vector<cGroup*> m_vecGroup;
	iMap* m_pMap;

	cFrame* m_pRootFrame;

public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lparam);

	void Draw_Texture();
	void Setup_Obj();
	void Obj_Render();

	void Load_Surface();

private:
	LPD3DXMESH		m_pMeshTeapot;
	LPD3DXMESH		m_pMeshSphere;
	D3DMATERIAL9	m_stMtlTeapot;
	D3DMATERIAL9	m_stMtlSphere;
	D3DMATERIAL9	stWhiteMtl;
	D3DMATERIAL9	stRedMtl;

	LPD3DXMESH			m_pObjMesh;
	vector<cMtlTex*>	m_vecObjMtlTex;
	vector<ST_SPHERE>	m_vecSphere;
public:
	void Setup_MeshObject();
	void Mesh_Render();
};

	