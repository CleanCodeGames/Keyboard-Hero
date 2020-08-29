#pragma once
#include"System.h"

class CheckBox : public System
{
private:

	bool is_Check;
	Shape shape;
	string name_ID;
	sf::Text text;

public:

	CheckBox(v2f pos, bool is_Check, string name_id, string descript) : is_Check(is_Check), name_ID(name_id), text(descript, *font_modeka)
	{
		text.setCharacterSize(uint(scr_1*2));
		text.setStyle(sf::Text::Bold);
		ConstructShape(shape, pos, v2f(3,3), texture->CheckBox, true);
		if(is_Check) shape.setTextureRect(sf::IntRect(32,0,32,32));
		else shape.setTextureRect(sf::IntRect(0,0,32,32));
		text.setPosition(v2f(shape.getPosition().x + scr_1*2, shape.getPosition().y-text.getGlobalBounds().height/2));
	}

	virtual bool isActive()
	{
		
		if(event.type == sf::Event::MouseButtonPressed)
		{
			if(shape.getGlobalBounds().contains(cur_p))
			{
				if(event.key.code == sf::Mouse::Left)
				{
					if(is_Check)
					{
						is_Check = false;
						shape.setTextureRect(sf::IntRect(0,0,32,32));
					}
					else
					{
						is_Check = true;
						shape.setTextureRect(sf::IntRect(32,0,32,32));
					}
					return true;
				}
			}
		}
		return false;
	}

	string getNameID() const
	{
		return name_ID;
	}

	bool isCheck() const
	{
		return is_Check;
	}

	virtual void Draw()
	{
		wnd->draw(shape);
		wnd->draw(text);
	}

	virtual ~CheckBox(void)
	{
	}
};