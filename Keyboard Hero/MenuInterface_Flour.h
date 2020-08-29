#pragma once
#include "oMenuInterface.h"
#include "oPortal.h"

class MenuInterface_Flour : public oMenuInterface
{
private:

	PortalCreator portal;
	float radius;
	float alpha;

public:

	MenuInterface_Flour(void) :
		portal(v2f(-20, 60), v2f(15,15), "", true)
	{
		alpha = 0;
		radius = float(scr_W/8);
	}

	virtual void Update()
	{
		portal.Update();
		portal.setPosition(v2f(radius * cos(alpha),portal.getPosition().y));
		alpha += 0.0005*time;
	}

	virtual void Draw()
	{
		portal.Draw();
	}

	~MenuInterface_Flour(void)
	{
	}
};