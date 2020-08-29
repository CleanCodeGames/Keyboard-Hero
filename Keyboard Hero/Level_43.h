#pragma once
#include "oLevel.h"

class Level_43 : public oLevel
{
private:

	Shape shpWhite;
	float timer_white;
public:

	Level_43(void) : timer_white(0)
	{
		ConstructShape(shpWhite, v2f(25,-20), v2f(18,18), texture->White, true);
		percent_need = 99;
		music = &sound->Theme[2];
		count_key_max = 280;

		vec_BG.push_back(make_shared<BackGround_L3>(BackGround_L3()));

		CreateBonusBar(42,52,52,68);

		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::White, L"\"White 2\"", font_modeka);

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-50, 30), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( 50, 30), v2f(10, 10), "Creator", true)));

		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(40,30), v2f(10,10), "Fire1")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(30,30), v2f(10,10), "Frost1")));
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(20,30), v2f(10,10), "Epic1")));
		vec_Portal.push_back(make_shared<PortalTornadoNature>(PortalTornadoNature(v2f(10,30), v2f(10,10), "Nature1")));

		vec_PortalMulti.push_back(make_shared<PortalMulticolor>(PortalMulticolor(v2f(0,30), v2f(10,10), "Epic", "Epic")));

		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(-40,30), v2f(10,10), "Fire2")));
		vec_Portal.push_back(make_shared<PortalTornadoFrost>(PortalTornadoFrost(v2f(-30,30), v2f(10,10), "Frost2")));
		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f(-20,30), v2f(10,10), "Epic2")));
		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(-10,30), v2f(10,10), "Nature2")));
	}

	virtual void Update()
	{
		oLevel::Update();
		switch(state)
		{
		case STATE::welcome: Welcome(); break;

		case STATE::play:
			
			timer_white += time;
			if(timer_white > 40000) timer_white = 0;
			if(count_key < count_key_max)
			{
				timer_key_spawn += time;
				if(timer_key_spawn > 900/modifier_speed)
				{
					CreateFrosKey(v2f(50,30), v2f(7,7), v2f(-0.0135,0));
					timer_key_spawn = 0;
					KeyGenWhiteBlack(70,10);
				}
			}
			break;
		}
	}

	virtual void Draw()
	{
		oLevel::Draw();
		if(state == welcome) 
			wnd->draw(text_welcome);
		if(state == play && timer_white < 3000) 
			wnd->draw(shpWhite);
	}

	virtual ~Level_43(void)
	{
	}
};