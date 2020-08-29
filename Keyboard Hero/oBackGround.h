#pragma once
#include "oStar.h"
#include "oClouds.h"

class oBackGround : public System
{
protected:

	vector<shared_ptr<oStar>> vec_Star;
	vector<shared_ptr<Star2>> vec_Star_Float;
	vector<shared_ptr<Shape>> vec_Lines_Hor,vec_Lines_Ver;
	Shape shpGalaxy[2];
	oClouds clouds;
	Shape shpBG;
	float alpha;

public:

	oBackGround(void) : alpha(0)
	{
		ConstructShape(shpBG, v2f(0,0), v2f(scr_W/scr_1, 100), texture->SpaceBlack, true);

		for(int i = 0; i < 80; i++)
		{
			v2f pos(rand()%101-50,rand()%101-50);
			vec_Star_Float.push_back(make_shared<Star2>(Star2(pos, v2f(0.1,0.1)*float(rand()%25+20))));
		}

		vec_Star.push_back(make_shared<Star1>(Star1(v2f(-46,-46), v2f(3,3))));
		vec_Star.push_back(make_shared<Star1>(Star1(v2f(-26,-45), v2f(4,4))));
		vec_Star.push_back(make_shared<Star1>(Star1(v2f(-42,-37), v2f(5,5))));
		vec_Star.push_back(make_shared<Star1>(Star1(v2f(-17,-35), v2f(3,3))));
		vec_Star.push_back(make_shared<Star1>(Star1(v2f( 11,-41), v2f(4,4))));
		vec_Star.push_back(make_shared<Star1>(Star1(v2f( 34,-45), v2f(5,5))));
		vec_Star.push_back(make_shared<Star1>(Star1(v2f( 45,-31), v2f(3,3))));
		vec_Star.push_back(make_shared<Star1>(Star1(v2f( 41,-14), v2f(4,4))));
		vec_Star.push_back(make_shared<Star1>(Star1(v2f( 17,-13), v2f(5,5))));
		vec_Star.push_back(make_shared<Star1>(Star1(v2f(  3, 20), v2f(3,3))));
		vec_Star.push_back(make_shared<Star1>(Star1(v2f(-41, -6), v2f(4,4))));
		vec_Star.push_back(make_shared<Star1>(Star1(v2f(-21, 14), v2f(5,5))));
		vec_Star.push_back(make_shared<Star1>(Star1(v2f(-22, 40), v2f(3,3))));
		vec_Star.push_back(make_shared<Star1>(Star1(v2f(-39, 46), v2f(4,4))));
		vec_Star.push_back(make_shared<Star1>(Star1(v2f(-47, 40), v2f(5,5))));
		vec_Star.push_back(make_shared<Star1>(Star1(v2f( 44, 20), v2f(3,3))));
		vec_Star.push_back(make_shared<Star1>(Star1(v2f( 48, 29), v2f(4,4))));
		vec_Star.push_back(make_shared<Star1>(Star1(v2f( 41, 42), v2f(5,5))));
		vec_Star.push_back(make_shared<Star1>(Star1(v2f( 14, 44), v2f(3,3))));

		vec_Star.push_back(make_shared<Star3>(Star3(v2f(-43, 20), v2f(4,4))));
		vec_Star.push_back(make_shared<Star3>(Star3(v2f( 41, 33), v2f(5,5))));
		vec_Star.push_back(make_shared<Star3>(Star3(v2f(-35, -43), v2f(5,5))));
		vec_Star.push_back(make_shared<Star3>(Star3(v2f( 41, -27), v2f(4,4))));

		vec_Star.push_back(make_shared<Star4>(Star4(v2f( -42, -25), v2f(10,10))));
		vec_Star.push_back(make_shared<Star4>(Star4(v2f( 45, -5), v2f(8,8))));


		for(int i = 0; i*12.5f*scr_1 <= scr_H; i++)
		{
			vec_Lines_Hor.push_back(make_shared<Shape>(Shape(v2f(scr_W, 2))));
			vec_Lines_Hor.back()->setPosition(v2f(0, i*12.5f*scr_1 - (scr_H/2.f)));
			vec_Lines_Hor.back()->setOrigin(vec_Lines_Hor.back()->getSize()/2.f);
			vec_Lines_Hor.back()->setFillColor(sf::Color(255,255,255,75));
		}

		for(int i = 0; i*12.5f*scr_1 <= scr_W; i++)
		{
			vec_Lines_Ver.push_back(make_shared<Shape>(Shape(v2f(2, scr_H))));
			vec_Lines_Ver.back()->setPosition(v2f(i*12.5*scr_1 - (scr_W/2.f), 0));
			vec_Lines_Ver.back()->setOrigin(vec_Lines_Ver.back()->getSize()/2.f);
			vec_Lines_Ver.back()->setFillColor(sf::Color(255,255,255,75));
		}
	}

	virtual void Update()
	{
		clouds.Update(alpha);
		static float timer = 0;
		timer += time;
		if(timer > 100)
		{
			timer = 0;
			vec_Star_Float.push_back(make_shared<Star2>(Star2(v2f(0,0), v2f(0.1,0.1)*float(rand()%25+20), float(rand()%36000)/100.f)));
		}

		for(auto star: vec_Star) star->Update(alpha);
		for(auto it = vec_Star_Float.begin(); it != vec_Star_Float.end();)
		{
			auto& star = *(*it);
			if(getVisible().contains(star.getPosition()))
			{
				star.Update(alpha);
				it++;
			}
			else it = vec_Star_Float.erase(it);
		}
		const sf::Color color(255 * (1.f+sin(alpha))/2.f, 255 * (1.f+sin(alpha*2))/2.f, 255 * (1.f+sin(alpha*3))/2.f, 70);
		for(auto hor: vec_Lines_Hor) hor->setFillColor(color);
		for(auto ver: vec_Lines_Ver) ver->setFillColor(color);
		shpGalaxy[0].rotate( 0.01*time);
		shpGalaxy[1].rotate(-0.01*time);
		alpha += 0.0001*time;

		if(timer_Star2_sEff >= 90) timer_Star2_sEff = 0;
	}

	virtual void Draw()
	{
		wnd->draw(shpBG);
		for(auto hor: vec_Lines_Hor) wnd->draw(*hor);
		for(auto ver: vec_Lines_Ver) wnd->draw(*ver);
		for(auto star: vec_Star) star->Draw();
		for(auto star: vec_Star_Float) star->Draw();
		for(int i = 0; i < 2; i++) 
			wnd->draw(shpGalaxy[i]);
		clouds.Draw();
	}
	virtual ~oBackGround(void){}
};

class BackGround_L1 : public oBackGround
{
public:

	BackGround_L1(void)
	{
		ConstructShape(shpGalaxy[0], v2f(0,0), v2f(100,100), texture->Galaxy1, true);
		shpGalaxy[1] = shpGalaxy[0];
		shpGalaxy[1].setTextureRect(sf::IntRect(1024,0,-1024,1024));
	}

	virtual ~BackGround_L1(void){}
};

class BackGround_L2 : public oBackGround
{
public:

	BackGround_L2(void)
	{
		ConstructShape(shpGalaxy[0], v2f(0,0), v2f(100,100), texture->Galaxy2, true);
		shpGalaxy[1] = shpGalaxy[0];
		shpGalaxy[1].setTextureRect(sf::IntRect(1024,0,-1024,1024));
	}

	virtual ~BackGround_L2(void){}
};

class BackGround_L3 : public oBackGround
{
public:

	BackGround_L3(void)
	{
		ConstructShape(shpGalaxy[0], v2f(0,0), v2f(100,100), texture->Galaxy3, true);
		shpGalaxy[1] = shpGalaxy[0];
		shpGalaxy[1].setTextureRect(sf::IntRect(1024,0,-1024,1024));
	}

	virtual ~BackGround_L3(void){}
};

class BackGround_L4 : public oBackGround
{
public:

	BackGround_L4(void)
	{
		ConstructShape(shpGalaxy[0], v2f(0,0), v2f(100,100), texture->Galaxy4, true);
		shpGalaxy[1] = shpGalaxy[0];
		shpGalaxy[1].setTextureRect(sf::IntRect(1024,0,-1024,1024));
	}

	virtual ~BackGround_L4(void){}
};

class BackGround_L5 : public oBackGround
{
public:

	BackGround_L5(void)
	{
		ConstructShape(shpGalaxy[0], v2f(0,0), v2f(100,100), texture->Galaxy5, true);
		shpGalaxy[1] = shpGalaxy[0];
		shpGalaxy[1].setTextureRect(sf::IntRect(1024,0,-1024,1024));
	}

	virtual ~BackGround_L5(void){}
};

class BackGround_L6 : public oBackGround
{
public:

	BackGround_L6(void)
	{
		ConstructShape(shpGalaxy[0], v2f(0,0), v2f(100,100), texture->Galaxy6, true);
		shpGalaxy[1] = shpGalaxy[0];
		shpGalaxy[1].setTextureRect(sf::IntRect(1024,0,-1024,1024));
	}

	virtual ~BackGround_L6(void)
	{

	}
};

class BackGround_L7 : public oBackGround
{
public:

	BackGround_L7(void)
	{
		ConstructShape(shpGalaxy[0], v2f(0,0), v2f(100,100), texture->Galaxy7, true);
		shpGalaxy[1] = shpGalaxy[0];
		shpGalaxy[1].setTextureRect(sf::IntRect(1024,0,-1024,1024));
	}

	virtual ~BackGround_L7(void)
	{

	}
};

class BackGround_L8 : public oBackGround
{
public:

	BackGround_L8(void)
	{
		ConstructShape(shpGalaxy[0], v2f(0,0), v2f(100,100), texture->Galaxy8, true);
		shpGalaxy[1] = shpGalaxy[0];
		shpGalaxy[1].setTextureRect(sf::IntRect(1024,0,-1024,1024));
	}

	virtual ~BackGround_L8(void)
	{

	}
};