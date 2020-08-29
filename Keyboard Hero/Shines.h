#pragma once
#include"System.h"

class Shines : public System
{
private:

	Shape shp_Shine[2];
	float timer;

public:

	Shines(v2f pos) : timer(1000)
	{
		uint rColor = rand()%6;
		sf::Color color;
		if(rColor == 0) color = sf::Color::Red;
		if(rColor == 1) color = sf::Color::Green;
		if(rColor == 2) color = sf::Color::Blue;
		if(rColor == 3) color = sf::Color::Cyan;
		if(rColor == 4) color = sf::Color::Magenta;
		if(rColor == 5) color = sf::Color::Yellow;

		for(int i = 0; i < 2; i++) 
		{
			ConstructShape(shp_Shine[i], pos, v2f(4.5f, 4.5f), texture->Shine, color, false);
			shp_Shine[i].setScale(v2f(0.01,0.01));
		}
		shp_Shine[1].setTextureRect(sf::IntRect(64,0,-64,64));
	}

	bool getKill() const
	{
		return timer <= 0 ? true : false;
	}

	virtual ~Shines()
	{
	}

	virtual void Update()
	{
		timer -= time;
		if(timer < 0) timer = 0;
		shp_Shine[0].rotate( 0.05*time);
		shp_Shine[1].rotate(-0.05*time);
		const float rate = timer/1000.f;
		for(int i = 0; i < 2; i++)
		{
			shp_Shine[i].setScale(v2f(1.f-rate,1.f-rate));
			shp_Shine[i].setFillColor(sf::Color(
				shp_Shine[i].getFillColor().r, 
				shp_Shine[i].getFillColor().g, 
				shp_Shine[i].getFillColor().b, 
				255.f*rate));
		}
	}

	virtual void Draw()
	{
		for(int i = 0; i < 2; i++) 
			wnd->draw(shp_Shine[i]);
	}
};