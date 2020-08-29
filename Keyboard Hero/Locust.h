#pragma once
#include "oKeyMove.h"

class Locust : public oKeyMove
{
private:

	Shape shpLocust;
	v2f start_pos;

public:

	Locust(v2f pos, v2f siz, v2f speed) : oKeyMove(getRandKeyNum(), v2f(pos.x, pos.y + 20.5f), siz, speed, "")
	{
		type = "Locust";
		ConstructShape(shpLocust, pos, siz*1.33f, texture->Locust, true);
		start_pos = shpLocust.getPosition();

		int type = rand()%5;
		if(type == 0) ConstructShape(shape[0], v2f(pos.x, pos.y+0.5f), siz, texture->RingWhite, true);
		if(type == 1) ConstructShape(shape[0], v2f(pos.x, pos.y+0.5f), siz, texture->RingFrost, true);
		if(type == 2) ConstructShape(shape[0], v2f(pos.x, pos.y+0.5f), siz, texture->RingFire, true);
		if(type == 3) ConstructShape(shape[0], v2f(pos.x, pos.y+0.5f), siz, texture->RingEpic, true);
		if(type == 4) ConstructShape(shape[0], v2f(pos.x, pos.y+0.5f), siz, texture->RingNature, true);
		shape[1] = shape[0];
		shape[1].setTextureRect(sf::IntRect(256,0,-256,256));
		timer_Effect = 0;
		setKeyInBoss();
	}

	virtual void Move(v2f speed)
	{
		shpLocust.move((speed*time)*scr_1);
		setPostion(v2f(shpLocust.getPosition().x, shpLocust.getPosition().y + (scr_1*0.5f)));
	}

	virtual v2f getPosition() const
	{
		return shpLocust.getPosition();
	}

	virtual void Update(float alpha)
	{
		oKeyMove::Update();
		shpLocust.move(speed*scr_1*time);
		shpLocust.setPosition(v2f(start_pos.x + ((42.5 * scr_1) * cos(alpha)), shpLocust.getPosition().y));
		setPostion(v2f(shpLocust.getPosition().x, shpLocust.getPosition().y + (scr_1*0.5f)));
	}

	virtual void setPosition(v2f pos)
	{
		shpLocust.setPosition(pos);
		setPostion(v2f(pos.x, pos.y+(scr_1*0.5f)));
	}

	virtual void Draw()
	{
		wnd->draw(shpLocust);
		oKeyMove::Draw();
	}

	~Locust(void) { }
};