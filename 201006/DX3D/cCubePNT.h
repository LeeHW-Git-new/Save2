#pragma once
class cCubePNT
{
public:
	cCubePNT();
protected:
	vector<ST_PNT_VERTEX> m_vecVertex;
public:
	virtual ~cCubePNT(void);
	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

