#pragma once
#include "System.h"

class BonusBarLogo : public System
{
private:

	Shape shp_Logo;
	Shape shp_Glow;
	float alpha;
	float time_life;
	float time_max;
	string type;

public:

	BonusBarLogo(v2f pos, string type) : type(type), alpha(0), time_life(0), time_max(0)
	{
		ConstructShape(shp_Logo, v2f(pos.x + 12.5, pos.y + 7), v2f(12, 6), true);
		ConstructShape(shp_Glow, v2f(pos.x + 12.5, pos.y + 7), v2f(12, 6)*1.3f, texture->Glow, true);
		if(type == "Fire")
		{
			shp_Glow.setFillColor(sf::Color(229,95,12));
			shp_Logo.setTexture(&texture->Fire);
		}
		if(type == "Frost")
		{
			shp_Glow.setFillColor(sf::Color(49,144,242));
			shp_Logo.setTexture(&texture->Frost);
		}
		if(type == "Epic")
		{
			shp_Glow.setFillColor(sf::Color(140,44,241));
			shp_Logo.setTexture(&texture->Dark);
		}
		if(type == "Nature")
		{
			shp_Glow.setFillColor(sf::Color(21,148,33));
			shp_Logo.setTexture(&texture->Life);
		}
	}

	void Update()
	{
		if(isLife() && !isPauseGame)
		{
			if(time_life > 0) time_life -= time;
			if(time_life < 0) time_life = 0;
			shp_Glow.setFillColor(sf::Color(shp_Glow.getFillColor().r, shp_Glow.getFillColor().g, shp_Glow.getFillColor().b, 255*(time_life/time_max)));
			shp_Logo.setFillColor(sf::Color(255, 255, 255, 255*(time_life/time_max)));
			shp_Glow.setScale(v2f(1.f + (0.33 * sin(alpha)), 1.f + (0.33 * sin(alpha))));
			alpha += 0.015*time;
		}
		else
		{
			shp_Glow.setFillColor(sf::Color(shp_Glow.getFillColor().r, shp_Glow.getFillColor().g, shp_Glow.getFillColor().b, 0));
			shp_Logo.setFillColor(sf::Color(255, 255, 255, 0));
		}
	}

	void Activated(float time)
	{
		time_life = time;
		time_max = time;
	}

	string getType() const
	{
		return type;
	}

	bool isLife() const
	{
		return time_life > 0 ? true : false;
	}

	void Draw()
	{
		wnd->draw(shp_Glow);
		wnd->draw(shp_Logo);
	}
};