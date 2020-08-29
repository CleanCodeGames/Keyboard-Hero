#include "System.h"
class LastKey : public System
{
private:

	float alpha;
	Shape shape[2];

public:

	LastKey() : alpha(0)
	{
		if(language == EN)ConstructShape(shape[0], v2f(-50,-35), v2f(10,10), texture->Symbols_EN, sf::Color::Cyan, true);
		if(language == RU)ConstructShape(shape[0], v2f(-50, -35), v2f(10, 10), texture->Symbols_RU, sf::Color::Cyan, true);
	}

	void Draw()
	{
		if(alpha > 0)
			for(int i = 0; i < 2; i++) wnd->draw(shape[i]);
	}

	void setKeyNum(uint num)
	{
		alpha = 1.0f;
		if(num <= 7) shape[0].setTextureRect(sf::IntRect(num*64, 0, 64, 64));
		else if(num >= 8 && num <= 15) shape[0].setTextureRect(sf::IntRect((num-8)*64, 64, 64, 64));
		else if(num >= 16 && num <= 23) shape[0].setTextureRect(sf::IntRect((num-16)*64, 128, 64, 64));
		else if(num >= 24 && num <= 26) shape[0].setTextureRect(sf::IntRect((num-24)*64, 192, 64, 64));
		else if(language == RU && (num >= 46 && num <= 51)) shape[0].setTextureRect(sf::IntRect((num-44)*64, 192, 64, 64));
		shape[1] = shape[0];
		shape[1].setPosition(v2f(scr_1*50, -scr_1*35));
	}

	void Update()
	{
		if(alpha > 0) alpha -= (time*0.001);
		for(int i = 0; i < 2; i++) 
		{
			shape[i].setFillColor(sf::Color(
			shape[i].getFillColor().r,
			shape[i].getFillColor().g,
			shape[i].getFillColor().b,
			255*alpha));

			shape[i].setScale(v2f(1-(-alpha), 1-(-alpha)));
		}
	}
};