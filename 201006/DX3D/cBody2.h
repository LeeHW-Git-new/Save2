#pragma once
#include "cCubeNode.h"
class cBody2 :
	public cCubeNode
{
public:
	cBody2();
	~cBody2();

	virtual void Setup() override;
};

