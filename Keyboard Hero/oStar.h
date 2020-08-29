#pragma once
#include "oSpecEffect.h"

class Logo_Main : public System
{
private:
	
	float alpha;

public:

	Shape shape;

	Logo_Main() : alpha(0)
	{
		ConstructShape(shape, v2f(0, -23), v2f(50, 13), texture->Logo, sf::Color(255,255,255,255), true);
	}

	void Update()
	{
	}

	void Draw()
	{
		wnd->draw(shape);
	}
};

class oStar : public System
{
public:
	oStar(v2f pos, v2f siz) {}
	virtual ~oStar(void) {}
	virtual void Update(float _alpha = 0) = 0;
	virtual void Draw() = 0;
};

class Star1 : public oStar
{
private:

	Shape shape[2];
	const sf::Color color;

public:

	Star1(v2f pos, v2f siz) : oStar(pos, siz), color(sf::Color(rand()%100+155, rand()%100+155, rand()%100+155))
	{
		for(int i = 0; i < 2; i++) 
		{
			ConstructShape(shape[i], v2f(pos.x*scr_1w, pos.y*scr_1), siz, texture->Star1, color, false);
		}
		shape[1].setTextureRect(sf::IntRect(128,0,-128,128));
	}

	virtual ~Star1(void)
	{

	}

	virtual void Update(float _alpha)
	{
		shape[0].rotate(0.1f*time*cos(_alpha));
		shape[1].rotate(0.1f*time*sin(_alpha));
		for(int i = 0; i < 2; i++) shape[i].setScale(1 + 0.3*sin(_alpha), 1 + 0.3*sin(_alpha));
	}

	virtual void Draw()
	{
		for(int i = 0; i < 2; i++) 
			wnd->draw(shape[i]);
	}
};

class Star2 : public oStar
{
private:

	vector<shared_ptr<oSpecEffect>> vec_SpecEffect;
	Shape shape;
	v2f speed;
	float transparent;

public:
	 
	v2f getPosition() const
	{
		return shape.getPosition();
	}

	Star2(v2f pos, v2f siz, float _ang = 0) : oStar(pos, siz)
	{
		ConstructShape(shape, v2f(pos.x*scr_1w, pos.y*scr_1), siz, texture->Star2,sf::Color(rand()%256, rand()%256, rand()%256, 0), false);
		if(_ang==0)
		{
			_ang = atan2f(shape.getPosition().y, shape.getPosition().x);
			transparent = 1500;
		}
		else
		{
			transparent = 0;
			shape.setFillColor(sf::Color(rand()%256, rand()%256, rand()%256, 0));
		}
		speed = v2f(cos(_ang), sin(_ang))*0.006f*scr_1;
	}

	virtual ~Star2(void)
	{
	}

	virtual void Update(float _alpha)
	{
		if(transparent < 1500) transparent += time;
		if(transparent > 1500) transparent =  1500;
		
		shape.setFillColor(sf::Color(
			shape.getFillColor().r, 
			shape.getFillColor().g,
			shape.getFillColor().a,
			255*(transparent/1500)));
		shape.move(speed*time);
		shape.setScale(1 + 0.2*sin(_alpha*10), 1 + 0.2*sin(_alpha*10));
		shape.rotate(0.2 * time);
		v2f size = shape.getSize() + (v2f(0.00035f, 0.00035f) * time);
		shape.setSize(size);
		shape.setOrigin(shape.getSize()/2.f);

		if(timer_Star2_sEff >= 90 && shape.getFillColor().a >= 75)
		{
			vec_SpecEffect.push_back(make_shared<SpecEffect_OneYesRotation>(
			SpecEffect_OneYesRotation(shape.getPosition(), shape.getSize().x, texture->Star2, shape.getFillColor())));
		}

		for(auto it = vec_SpecEffect.begin(); it != vec_SpecEffect.end();)
		{
			oSpecEffect& sEff = *(*it);
			if(sEff.getKill())
			{
				it = vec_SpecEffect.erase(it);
			}
			else 
			{
				sEff.Update();
				it++;
			}
		}
	}

	virtual void Draw()
	{
		for(auto sEff: vec_SpecEffect)
			sEff->Draw();
		wnd->draw(shape);
	}
};

class Star3 : public oStar
{
private:

	Shape shape[2];
	Shape shpGlow;

public:

	Star3(v2f pos, v2f siz) : oStar(pos, siz)
	{
		for(int i = 0; i < 2; i++)
			ConstructShape(shape[i], v2f(pos.x*scr_1w, pos.y*scr_1), siz, texture->Star3, false);
		ConstructShape(shpGlow, v2f(pos.x*scr_1w, pos.y*scr_1), siz*1.8f, texture->Glow, false);
		shpGlow.setFillColor(sf::Color(255,255,0,100));
		shape[1].setTextureRect(sf::IntRect(128,0, -128, 128));
	}

	virtual ~Star3(void)
	{

	}

	void Update(float _alpha)
	{
		shape[0].rotate( 0.05 * time);
		shape[1].rotate(-0.05 * time);
		shpGlow.setScale(1 + 0.33 * sin(_alpha*15), 1 + 0.33 * sin(_alpha*15));
	}

	void Draw()
	{
		wnd->draw(shpGlow);
		for(int i = 0; i < 2; i++)
			wnd->draw(shape[i]);
	}
};

class Star4 : public oStar
{
private:

	Shape shape[2];

public:

	Star4(v2f pos, v2f siz) : oStar(pos, siz)
	{
		for(int i = 0; i < 2; i++)
			ConstructShape(shape[i], v2f(pos.x*scr_1w, pos.y*scr_1), siz, texture->Star4, false);
		shape[1].setTextureRect(sf::IntRect(128,0, -128, 128));
	}

	virtual ~Star4(void)
	{

	}

	void Update(float _alpha)
	{
		shape[0].rotate(-0.07f*time);
		shape[1].rotate( 0.07f*time);
	}

	void Draw()
	{
		for(int i = 0; i < 2; i++)
			wnd->draw(shape[i]);
	}
};