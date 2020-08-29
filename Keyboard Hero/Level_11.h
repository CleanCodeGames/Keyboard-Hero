#pragma once
#include "oLevel.h"

class Level_11 : public oLevel
{
public:

	Level_11(void)
	{
		percent_need = 97;
		music = &sound->Theme[0];
		count_key_max = 140;
		vec_BG.push_back(make_shared<BackGround_L3>(BackGround_L3()));
		CreateBonusBar(25,32,32,35);
		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);
		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Small Confusion\"", font_modeka);
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-55,0), v2f(15,15), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f( 55,20), v2f(15,15), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-55,40), v2f(15,15), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f( 55,60), v2f(15,15), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( 50,0), v2f(15,15), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-50,20), v2f(15,15), "Creator", false)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( 50,40), v2f(15,15), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-50,60), v2f(15,15), "Creator", false)));
		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(-35,0), v2f(15,15), "Fire1")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(35,20), v2f(15,15), "Frost1")));
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(-35,40), v2f(15,15), "Epic1")));
		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(35,60), v2f(15,15), "Nature1")));
		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f( 20,0), v2f(15,15), "Fire2")));
		vec_Portal.push_back(make_shared<PortalTornadoNature>(PortalTornadoNature(v2f(-20,20), v2f(15,15), "Frost2")));
		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f( 20,40), v2f(15,15), "Epic2")));
		vec_Portal.push_back(make_shared<PortalTornadoFrost>(PortalTornadoFrost(v2f(-20,60), v2f(15,15), "Nature2")));
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
				if(timer_key_spawn > 1600/modifier_speed)
				{
					if(key_type < 4)
					{
						uint type = rand()%2;
						v2f siz(9,9), spd(0.0085,0);
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
					KeyGenWhiteBlack(6,8);
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

	virtual ~Level_11(void)
	{
	}
};