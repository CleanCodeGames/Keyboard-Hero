#pragma once
#include"oSpecEffect.h"

class Meteor : public System
{
private:

	Shape shpMeteor[2];
	float speed;
	float frame_timer;
	uint frame_counter;
	vector<shared_ptr<oSpecEffect>> vec_Mirror;
	
public:

	Meteor(v2f siz, v2f pos, float spd) : speed(spd), frame_timer(0), frame_counter(rand()%20)
	{
		ConstructShape(shpMeteor[0], pos, siz, texture->Meteor, true);
		
		if(frame_counter >= 0 && frame_counter < 5) shpMeteor[0].setTextureRect(sf::IntRect(frame_counter*72,0,72,72));
		if(frame_counter >= 5 && frame_counter < 10) shpMeteor[0].setTextureRect(sf::IntRect((frame_counter-5)*72,72,72,72));
		if(frame_counter >= 10 && frame_counter < 15) shpMeteor[0].setTextureRect(sf::IntRect((frame_counter-10)*72,144,72,72));
		if(frame_counter >= 15 && frame_counter < 20) shpMeteor[0].setTextureRect(sf::IntRect((frame_counter-15)*72,216,72,72));
		shpMeteor[1] = shpMeteor[0];
		shpMeteor[1].setTextureRect(sf::IntRect(shpMeteor[0].getTextureRect().left+72, shpMeteor[0].getTextureRect().top, -shpMeteor[0].getTextureRect().width, shpMeteor[0].getTextureRect().height));
	}

	void Draw()
	{
		for(auto mirror: vec_Mirror)  mirror->Draw();
		for(int i = 0; i < 2; i++) wnd->draw(shpMeteor[i]);
	}

	bool isDead()
	{
		if(shpMeteor[0].getPosition().y > 85*scr_1) return true;
		return false;
	}

	v2f getPosition() const
	{
		return shpMeteor[0].getPosition();
	}

	void Update()
	{
		shpMeteor[0].move(v2f(0,(speed*scr_1)*time));
		shpMeteor[1].setPosition(shpMeteor[0].getPosition());
		shpMeteor[0].rotate(0.3*time);
		shpMeteor[1].rotate(-0.3*time);
		frame_timer += time;
		if(frame_timer >= 80)
		{
			if(frame_counter >= 19) frame_counter = 0;
			if(frame_counter >= 0 && frame_counter < 5) shpMeteor[0].setTextureRect(sf::IntRect(frame_counter*72,0,72,72));
			if(frame_counter >= 5 && frame_counter < 10) shpMeteor[0].setTextureRect(sf::IntRect((frame_counter-5)*72,72,72,72));
			if(frame_counter >= 10 && frame_counter < 15) shpMeteor[0].setTextureRect(sf::IntRect((frame_counter-10)*72,144,72,72));
			if(frame_counter >= 15 && frame_counter < 20) shpMeteor[0].setTextureRect(sf::IntRect((frame_counter-15)*72,216,72,72));
			shpMeteor[1] = shpMeteor[0];
			shpMeteor[1].setTextureRect(sf::IntRect(shpMeteor[0].getTextureRect().left+72, shpMeteor[0].getTextureRect().top, -shpMeteor[0].getTextureRect().width, shpMeteor[0].getTextureRect().height));
			frame_counter++;
			frame_timer = 0;
			vec_Mirror.push_back(make_shared<SpecEffect_OneYesRotation>(SpecEffect_OneYesRotation(
				getPosition(), shpMeteor[0].getSize().x, texture->Meteor, shpMeteor[0].getFillColor())));
			vec_Mirror.back()->setRect(shpMeteor[rand()%2].getTextureRect(), 72);
		}

		for(auto it = vec_Mirror.begin(); it != vec_Mirror.end();)
		{
			oSpecEffect& mirror = *(*it);
			if(mirror.getKill())
			{
				it = vec_Mirror.erase(it);
			}
			else
			{
				mirror.Update();
				mirror.Scaling();
				it++;
			}
		}
	}
};