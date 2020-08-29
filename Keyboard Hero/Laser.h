#pragma once
#include "System.h"

class Laser : public System
{
private:

	Shape mLaser, Effect[2];
	float timer, TIMER;
	bool is_Boss_Win;

public:

	bool isEnd() const
	{
		return timer > 0 ? false : true;
	}

	bool isBossWin() const
	{
		return is_Boss_Win;
	}

	void Draw()
	{
		wnd->draw(mLaser);
		for(int i = 0; i < 2; i++) 
			wnd->draw(Effect[i]);
	}

	void Update(v2f pos1, v2f pos2)
	{
		Effect[0].rotate( 0.15*time);
		Effect[1].rotate(-0.15*time);

		mLaser.setPosition(pos1);
		mLaser.setSize(v2f(getDist(pos1,pos2),mLaser.getSize().y));
		mLaser.setOrigin(0,mLaser.getSize().y/2.f);
		mLaser.setRotation(atan2f(pos2.y - pos1.y, pos2.x - pos1.x) * 180.f/PI);

		mLaser.setFillColor(sf::Color(mLaser.getFillColor().r,mLaser.getFillColor().g,mLaser.getFillColor().b,255*(timer/TIMER)));

		for(int i = 0; i < 2; i++) 
		{ 
			Effect[i].setFillColor(sf::Color(Effect[i].getFillColor().r,Effect[i].getFillColor().g,Effect[i].getFillColor().b,255*(timer/TIMER)));
			Effect[i].setPosition(pos2);
		}
		timer > 0 ? timer-=time : timer = 0;
	}

	void Update()
	{
		Effect[0].rotate( 0.15*time);
		Effect[1].rotate(-0.15*time);
		mLaser.setFillColor(sf::Color(mLaser.getFillColor().r,mLaser.getFillColor().g,mLaser.getFillColor().b,255*(timer/TIMER)));
		for(int i = 0; i < 2; i++) 
			Effect[i].setFillColor(sf::Color(Effect[i].getFillColor().r,Effect[i].getFillColor().g,Effect[i].getFillColor().b,255*(timer/TIMER)));
		timer > 0 ? timer-=time : timer = 0;
	}

	Laser(v2f pos1, v2f pos2, float width, float sizEff, float timer, sf::Color color) : timer(timer), TIMER(timer), is_Boss_Win(false)
	{
		ConstructShape(mLaser, pos1, v2f(getDist(pos1,pos2)/scr_1,width), texture->Laser, color, false);
		mLaser.setOrigin(0,(width/2.f)*scr_1);
		mLaser.setRotation(atan2f(pos2.y - pos1.y, pos2.x - pos1.x) * 180.f/PI);
		ConstructShape(Effect[0], pos2, v2f(sizEff,sizEff), texture->LaserEffect, false);
		Effect[1].setTextureRect(sf::IntRect(192,0,-192, 192));
	}

	~Laser(void)
	{

	}
};