#pragma once
class cBody;

class cCube
{
public:
	cCube(D3DXMATRIXA16* bodymat, D3DXVECTOR3 Vector2Center, D3DXVECTOR3 Scale);
	~cCube();

private:
	std::vector<ST_PC_VERTEX>   m_vecVertex;
	float                  m_fRotY;
	//D3DXVECTOR3               m_vDirection;
	D3DXVECTOR3               m_vPosition;
	D3DXMATRIXA16            m_matWorld;
	D3DXMATRIXA16*            m_BodyWorld;
	D3DXMATRIXA16				m_Scale;

public:
	void Setup();
	void Update();
	void Render();
	D3DXVECTOR3&            GetPosition();
};

