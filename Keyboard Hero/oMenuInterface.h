#pragma once
#include "System.h"

class oMenuInterface : public System
{

public:

	oMenuInterface(void){}
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual ~oMenuInterface(void){}
};