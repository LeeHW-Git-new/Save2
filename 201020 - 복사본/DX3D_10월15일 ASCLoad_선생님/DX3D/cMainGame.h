#pragma once
class cCubePC;
class cCamera;
class cGrid;
class cCubeMan;
class cLight;
class cGroup;
class cFrame;
class cMtlTex;
class Xfile;

class cMainGame
{
private:
	//vector<ST_PC_VERTEX> m_vecLineVertex;
	//vector<ST_PC_VERTEX > m_vecTriangleVertex;

	cCubePC*	m_pCubePC;
	cCamera*	m_pCamera;
	cGrid*		m_pGrid;

	cCubeMan* m_pCubeMan;

	Xfile* m_Xfile;

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


	LPD3DXMESH			m_pObjMesh;
	vector<cMtlTex*>	m_vecObjMtlTex;

	vector<ST_SPHERE>	m_vecSphere;
	D3DMATERIAL9		m_stMtlNone;
	D3DMATERIAL9		m_stMtlPicked;
	D3DMATERIAL9		m_stMtlPlane;
	vector<ST_PN_VERTEX>	m_vecPlaneVertex;
	D3DXVECTOR3			m_vPickedPosition;


public:
	void Setup_MeshObject();
	void Mesh_Render();

	void Setup_PickingObj();
	void PickingObj_Render();

	void Setup_HeightMap();
};	