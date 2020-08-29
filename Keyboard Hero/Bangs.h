#pragma once
#include "System.h"

class Bangs : public System
{
private:

	Shape shape[2];
	float timer;

public:

	Bangs(v2f pos, v2f siz) : timer(1250)
	{
		ConstructShape(shape[0], pos, siz, texture->BangBoss, false);
		shape[1] = shape[0];
		shape[1].setTextureRect(sf::IntRect(256,0,-256,256));
		for(int i = 0; i < 2; i++) shape[i].setScale(0.01, 0.01);
	}

	bool isEnd() const { return timer <= 0 ? true : false; }

	void Update()
	{
		if(timer > 0) timer -= time;
		if(timer < 0) timer = 0;
		shape[0].rotate(0.05*time);
		shape[1].rotate(-.05*time);

		for(int i = 0; i < 2; i++)
		{
			shape[i].setFillColor(sf::Color(255,255,255,255*(timer/1250)));
			shape[i].setScale(v2f(1.f-(timer/1250),1.f-(timer/1250)));
		}
	}

	void Draw()
	{
		for(int i = 0; i < 2; i++) 
			wnd->draw(shape[i]);
	}

};