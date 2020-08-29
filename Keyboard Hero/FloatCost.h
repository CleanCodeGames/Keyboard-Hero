#pragma once
#include "System.h"

class FloatCost : public System
{
private:

	sf::Text text;
	float timer_Life;
	float alpha;

public:


	bool isKill() { if(timer_Life >= 0)  return false; return true; }

	FloatCost(v2f pos, uint cost) 
	{
		alpha = 0;
		timer_Life = 2000.f;
		text.setFont(*font_modeka);
		text.setStyle(sf::Text::Bold);
		text.setCharacterSize(scr_1*1.5f);
		text.setString("+"+to_string(cost));
		text.setPosition(v2f(pos.x+text.getGlobalBounds().width/2, pos.y+text.getGlobalBounds().height/2));
		text.setColor(sf::Color::Yellow);
	}

	void Update()
	{
		timer_Life -= time;
		alpha += 0.005*time;
		const v2f p = text.getPosition();
		text.setPosition(p.x + 0.15f * cos(alpha), p.y);
		text.move(v2f(0,-0.005)*scr_1*time);
	}

	void Draw()
	{
		wnd->draw(text);
	}
};