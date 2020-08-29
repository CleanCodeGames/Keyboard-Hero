#pragma once
#include "oSpecEffect.h"

class FloatSphere : public System
{
private:

	vector<shared_ptr<oSpecEffect>> vec_Effect;
	float alpha;
	v2f e_pos;
	Shape shape[2];
	string type;
	float timer_Effect;
	bool is_Kill;

public:

	FloatSphere(v2f s_pos, v2f e_pos, string type) : e_pos(e_pos), timer_Effect(0), alpha(0), type(type), is_Kill(false)
	{
		for(int i = 0; i < 2; i++)
		{
			ConstructShape(shape[i], s_pos/scr_1, v2f(3,3), true);
			if(type == "Fire") shape[i].setTexture(&texture->SphereFire);
			if(type == "Frost") shape[i].setTexture(&texture->SphereFrost);
			if(type == "Epic") shape[i].setTexture(&texture->SphereEpic);
			if(type == "Nature") shape[i].setTexture(&texture->SphereNature);
		}
		shape[1].setTextureRect(sf::IntRect(128,0,-128,128));
	}

	const string& getType() const
	{
		return type;
	}

	v2f getPosition()
	{
		return shape[0].getPosition();
	}

	void Kill() { is_Kill = true; }

	bool isKill() const { return is_Kill; }

	void Update()
	{
		timer_Effect+=time;
		if(timer_Effect >= 75)
		{
			timer_Effect = 0;
			if(type == "Fire") vec_Effect.push_back(make_shared<SpecEffect_TwoCircleRotation>(SpecEffect_TwoCircleRotation(shape[0].getPosition(), shape[0].getSize().x, texture->SphereFire)));
			if(type == "Frost") vec_Effect.push_back(make_shared<SpecEffect_TwoCircleRotation>(SpecEffect_TwoCircleRotation(shape[0].getPosition(), shape[0].getSize().x, texture->SphereFrost)));
			if(type == "Epic") vec_Effect.push_back(make_shared<SpecEffect_TwoCircleRotation>(SpecEffect_TwoCircleRotation(shape[0].getPosition(), shape[0].getSize().x, texture->SphereEpic)));
			if(type == "Nature") vec_Effect.push_back(make_shared<SpecEffect_TwoCircleRotation>(SpecEffect_TwoCircleRotation(shape[0].getPosition(), shape[0].getSize().x, texture->SphereNature)));
		}

		shape[0].rotate( 0.05*time);
		shape[1].rotate(-0.05*time);

		const v2f p = shape[0].getPosition();
		const float angle = atan2f(e_pos.y - p.y, e_pos.x - p.x) * 57.2958f;
		const float radian = angle * PI / 180.f;
		const float speed = 0.045*scr_1 * time_in_pause;

		float x = cosf(radian) * speed;
		float y = sinf(radian) * speed;

		for(int i = 0; i < 2; i++) 
		{
			shape[i].setPosition(p.x + 0.75f * cos(alpha), p.y);
			shape[i].move(v2f(x,y));
		}

		alpha += 0.01*time;

		for(auto it = vec_Effect.begin(); it != vec_Effect.end();)
		{
			auto& obj = *(*it);
			if(obj.getKill()) 
			{
				it = vec_Effect.erase(it);
			}
			else
			{
				obj.Update();
				it++;
			}
		}
	}

	void Draw()
	{
		for(auto effect: vec_Effect) effect->Draw();
		for(int i = 0; i < 2; i++) wnd->draw(shape[i]);
	}
	
	virtual ~FloatSphere()
	{
	}
};