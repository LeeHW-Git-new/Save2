#pragma once
class cCube;

class cBody
{
public:
	cBody();
	~cBody();
private:
	float m_fRotY;
	D3DXVECTOR3 m_vDirection;
	D3DXVECTOR3 m_vPosition;
	D3DXMATRIXA16 m_matWorld;

	vector<cCube*> parts;



public:
	void Setup();
	void Update();
	void Render();

	D3DXVECTOR3& GetPosition();
};

