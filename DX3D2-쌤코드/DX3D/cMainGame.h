#pragma once
class cCube;
class cCamera;
class cGrid;
class cBody;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();
private:
	HDC	m_MemDC;
	HBITMAP m_hOldBitmap, m_hBitmap;

	vector<ST_PC_VERTEX> m_vecLineVertex;
	vector<ST_PC_VERTEX> m_vecTriangleVertex;
	vector<ST_PC_VERTEX> m_vecVertex;
	D3DXVECTOR3 m_vCamRotAngle;
	D3DXVECTOR3 m_vPosition;
	D3DXVECTOR3 m_vBoxDirection;
	vector<int> m_vecIndex;

	D3DXVECTOR3 m_vEye;
	D3DXVECTOR3 m_vLookAt;
	D3DXVECTOR3 m_vUp;

	D3DXMATRIXA16 m_matWorld;
	D3DXMATRIXA16 m_matView;
	D3DXMATRIXA16 m_matProj;

	D3DXMATRIXA16 m_matTrans;


	POINT m_ptPrevMouse;
	bool m_isLButtonDown;
	float m_fCameraDistance;

	float m_fBoxRotY;


	cCube* m_pCube;
	cCamera* m_pCamera;
	cGrid* m_pGrid;
	cBody* m_pBody;

public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message,
		WPARAM wParam, LPARAM lParam);
};

