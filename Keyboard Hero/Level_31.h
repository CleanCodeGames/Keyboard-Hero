#pragma once
#include "oLevel.h"

class Level_31 : public oLevel
{
public:

	Level_31(void)
	{
		percent_need = 97;
		music = &sound->Theme[0];
		count_key_max = 200;
		vec_BG.push_back(make_shared<BackGround_L7>(BackGround_L7()));
		CreateBonusBar(30,36,36,42);
		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);
		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Small Confusion 2\"", font_modeka);
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-55,0), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f( 55,20), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-55,40), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f( 55,60), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( 50,0), v2f(10,10), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-50,20), v2f(10,10), "Creator", false)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( 50,40), v2f(10,10), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-50,60), v2f(10,10), "Creator", false)));
		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(-35,0), v2f(12,12), "Fire1")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(35,20), v2f(12,12), "Frost1")));
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(-35,40), v2f(12,12), "Epic1")));
		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(35,60), v2f(12,12), "Nature1")));
		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f( 20,0), v2f(12,12), "Fire2")));
		vec_Portal.push_back(make_shared<PortalTornadoNature>(PortalTornadoNature(v2f(-20,20), v2f(12,12), "Frost2")));
		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f( 20,40), v2f(12,12), "Epic2")));
		vec_Portal.push_back(make_shared<PortalTornadoFrost>(PortalTornadoFrost(v2f(-20,60), v2f(12,12), "Nature2")));
	}
	
	virtual void Update()
	{
		oLevel::Update();
		switch(state)
		{
		case STATE::welcome: Welcome(); break;

		case STATE::play:
			
			if(count_key < count_key_max)
			{
				timer_key_spawn += time;
				if(timer_key_spawn > 1100/modifier_speed)
				{
					if(key_type < 4)
					{
						uint type = rand()%2;
						v2f siz(7,7), spd(0.011,0);
						if(key_type == 0) {
							if(type > 0) CreateFireKey(v2f(50,0), siz, -spd);
							else CreateEpicKey(v2f(50,0), siz, -spd);
						}
						if(key_type == 1) {
							if(type > 0) CreateFrosKey(v2f(-50,20), siz, spd);
							else CreateLifeKey(v2f(-50,20), siz, spd);
						}
						if(key_type == 2) {
							if(type > 0) CreateEpicKey(v2f(50,40), siz, -spd);
							else CreateFireKey(v2f(50,40), siz, -spd);
						}
						if(key_type == 3) {
							if(type > 0) CreateLifeKey(v2f(-50,60), siz, spd);
							else CreateFrosKey(v2f(-50,60), siz, spd);
						}

						key_type++;
						if(key_type >= 4) key_type = 0;
					}
					timer_key_spawn = 0;
					KeyGenWhiteBlack(10,10);
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
	}

	virtual ~Level_31(void)
	{
	}
};