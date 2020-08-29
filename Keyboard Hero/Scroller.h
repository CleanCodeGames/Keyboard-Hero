#pragma once
#include "System.h"

class Scroller : public System
{
private:

	Shape shpScr;
	Shape shpInd;
	sf::Text text;
	int result;
	string name_ID;
	bool isPressed;

public:

	Scroller(v2f pos, uint indicator, string name_id, string descript) : 
		result(indicator), name_ID(name_id), text(descript, *font_modeka), isPressed(false)
	{
		text.setCharacterSize(uint(scr_1*2));
		text.setStyle(sf::Text::Bold);
		ConstructShape(shpInd, pos, v2f(25,4), texture->VolumeScroll, true);
		ConstructShape(shpScr, v2f((shpInd.getPosition().x - shpInd.getSize().x/2.f) + (shpInd.getSize().x / 100 * indicator), shpInd.getPosition().y), v2f(1.5f,4), texture->Scroller, false);
		text.setPosition(v2f(shpInd.getPosition().x - text.getGlobalBounds().width/2.f, shpInd.getPosition().y-(scr_1*3.25 + text.getGlobalBounds().height/2.f)));
		shpInd.setScale(1.1f, 1);
	}

	virtual string getNameID() const
	{
		return name_ID;
	}

	virtual bool isActive()
	{
		if(event.type == sf::Event::MouseButtonPressed)
		{
			if(event.key.code == sf::Mouse::Left)
			{
				if(shpInd.getGlobalBounds().contains(cur_p))
				{
					isPressed = true;
				}
			}
		}

		if(event.type == sf::Event::MouseButtonReleased)
		{
			if(event.key.code == sf::Mouse::Left)
			{
				isPressed = false;
			}
		}

		if(event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseMoved)
		{
			if(isPressed)
			{
				shpScr.setPosition(v2f(cur_p.x, shpInd.getPosition().y));
				if(cur_p.x > shpInd.getPosition().x + shpInd.getSize().x/2.f) shpScr.setPosition(v2f(shpInd.getPosition().x + shpInd.getSize().x/2.f, shpInd.getPosition().y));
				if(cur_p.x < shpInd.getPosition().x - shpInd.getSize().x/2.f) shpScr.setPosition(v2f(shpInd.getPosition().x - shpInd.getSize().x/2.f, shpInd.getPosition().y));
				result = 100 + (shpScr.getPosition().x - shpInd.getSize().x) / shpInd.getSize().x * 100;
				return true;
			}
		}
		return false;
	}

	virtual void Draw()
	{
		wnd->draw(shpInd);
		wnd->draw(shpScr);
		wnd->draw(text);
	}

	virtual uint getResult() const
	{
		return result;
	}

	virtual ~Scroller(void)
	{

	}
};