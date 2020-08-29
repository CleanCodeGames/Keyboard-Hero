#pragma once
#include "System.h"

class oClouds : public System
{
private:

	Shape shape[2];

public:

	oClouds(void)
	{
		ConstructShape(shape[0], v2f(0,-25), v2f(scr_W/scr_1, 50), texture->Cloud, true);
		ConstructShape(shape[1], v2f(0, 25), v2f(scr_W/scr_1, 50), texture->Cloud, true);
		shape[1].setTextureRect(sf::IntRect(1280,0,-1280,512));
	}

	virtual ~oClouds(void) { }

	virtual void Update(float _alpha = 0)
	{
		const sf::Color color(255 * (1.f+sin(_alpha))/2.f, 255 * (1.f+sin(_alpha*2))/2.f, 255 * (1.f+sin(_alpha*3))/2.f, 70);
		for(int i = 0; i < 2; i++) shape[i].setFillColor(sf::Color(color.r, color.g, color.b, 255));
		shape[0].setPosition((scr_1w*25.f) * cos(_alpha),-25.f*scr_1 + (scr_1*8.f) * sin(_alpha));
		shape[1].setPosition((scr_1w*25.f) * sin(_alpha), 25.f*scr_1 + (scr_1*8.f) * cos(_alpha));
	}

	virtual void Draw()
	{
		for(int i = 0; i < 2; i++) wnd->draw(shape[i]);
	}
};