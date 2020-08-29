#pragma once
#include "System.h"

class BonusBar : public System
{
protected:

	bool isActive;
	uint count_Need;
	uint count;
	Shape shp_Bar;
	Shape shp_Indr;
	Shape shp_Indr_Sphere[2];
	sf::Text text_Fn;
	const string type;
	const float size_x;

public:

	BonusBar(uint count_need, v2f pos, const string type) : 
		isActive(false),
		count_Need(count_need),
		type(type),
		count(0),
		size_x(scr_1*25)
	{
		shp_Indr.setPosition(pos*scr_1);
		ConstructText(text_Fn, v2f(0,0), 3, sf::Color::White, "", font_modeka);
		for(int i = 0; i < 2; i++)
		{
			shp_Indr_Sphere[i].setSize(v2f(scr_1*4,scr_1*4));
			shp_Indr_Sphere[i].setOrigin(shp_Indr_Sphere[i].getSize()/2.f);
		}

		if(type == "Fire") 
		{
			text_Fn.setString("F1");
			shp_Indr.setTexture(&texture->BonusIndFire);
			for(int i = 0; i < 2; i++) 
				shp_Indr_Sphere[i].setTexture(&texture->SphereFire);
		}
		if(type == "Frost") 
		{
			text_Fn.setString("F2");
			shp_Indr.setTexture(&texture->BonusIndFrost);
			for(int i = 0; i < 2; i++) 
				shp_Indr_Sphere[i].setTexture(&texture->SphereFrost);
		}
		if(type == "Epic") 
		{
			text_Fn.setString("F3");
			shp_Indr.setTexture(&texture->BonusIndEpic);
			for(int i = 0; i < 2; i++) 
				shp_Indr_Sphere[i].setTexture(&texture->SphereEpic);
		}
		if(type == "Nature") 
		{
			text_Fn.setString("F4");
			shp_Indr.setTexture(&texture->BonusIndNature);
			for(int i = 0; i < 2; i++) 
				shp_Indr_Sphere[i].setTexture(&texture->SphereNature);
		}

		ConstructShape(shp_Bar,  pos, v2f(25,3), texture->BonusIndBar, true);
		shp_Bar.setOrigin(0,0);
		shp_Indr.setSize(v2f(0, 3*scr_1));
		for(int i = 0; i < 2; i++) 
			shp_Indr_Sphere[i].setPosition(v2f(shp_Indr.getPosition().x + shp_Indr.getSize().x, shp_Indr.getPosition().y + shp_Indr.getSize().y/2.f));
	}

	virtual void addCount()
	{
		if(count < count_Need) 
		{
			count++;
			shp_Indr.setSize(v2f(float(count)/float(count_Need)*size_x, 3*scr_1));
			shp_Indr.setTextureRect(sf::IntRect(0,0,int(float(count)/float(count_Need)*256.f),36));
			for(int i = 0; i < 2; i++) shp_Indr_Sphere[i].setPosition(v2f(shp_Indr.getPosition().x + shp_Indr.getSize().x, shp_Indr.getPosition().y + shp_Indr.getSize().y/2.f));
		}
		if(count >= count_Need)
		{
			isActive = true;
			for(int i = 0; i < 2; i++) 
			shp_Indr_Sphere[i].setScale(v2f(1.5f,1.5f));
			text_Fn.setPosition(v2f(shp_Indr_Sphere[0].getPosition().x-scr_1*2.f,shp_Indr_Sphere[0].getPosition().y-scr_1*2));
		}
	}

	const string& getType() const
	{
		return type;
	}

	v2f getSpherePosition()
	{
		return shp_Indr_Sphere[0].getPosition();
	}

	virtual bool getActive()
	{
		return isActive;
	}

	virtual void clear()
	{
		isActive = false;
		count = 0;
		shp_Indr.setSize(v2f(0, 3*scr_1));
		shp_Indr.setTextureRect(sf::IntRect(0,0,0,36));
		for(int i = 0; i < 2; i++) shp_Indr_Sphere[i].setPosition(v2f(shp_Indr.getPosition().x + shp_Indr.getSize().x, shp_Indr.getPosition().y + shp_Indr.getSize().y/2.f));
		for(int i = 0; i < 2; i++) 
			shp_Indr_Sphere[i].setScale(v2f(1.f,1.f));
	}

	virtual void use()
	{
		isActive = false;
		count = 0;
		shp_Indr.setSize(v2f(0, 3*scr_1));
		shp_Indr.setTextureRect(sf::IntRect(0,0,0,36));
		for(int i = 0; i < 2; i++) shp_Indr_Sphere[i].setPosition(v2f(shp_Indr.getPosition().x + shp_Indr.getSize().x, shp_Indr.getPosition().y + shp_Indr.getSize().y/2.f));
		for(int i = 0; i < 2; i++) 
			shp_Indr_Sphere[i].setScale(v2f(1.f,1.f));
	}

	virtual void Draw()
	{
		wnd->draw(shp_Indr);
		wnd->draw(shp_Bar);
		shp_Indr_Sphere[0].rotate( 0.08*time);
		shp_Indr_Sphere[1].rotate(-0.08*time);
		for(int i = 0; i < 2; i++) 
			wnd->draw(shp_Indr_Sphere[i]);
		if(isActive) wnd->draw(text_Fn);
	}

	virtual ~BonusBar(void)
	{
	}
};