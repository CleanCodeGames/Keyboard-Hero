#pragma once
#include "oLevel.h"

class Level_37 : public oLevel
{
public:

	Level_37(void)
	{
		percent_need = 97;
		music = &sound->Theme[1];
		count_key_max = 300;

		vec_BG.push_back(make_shared<BackGround_L5>(BackGround_L5()));

		CreateBonusBar(38,46,46,58);

		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Double Push 2\"", font_modeka);

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-50,0), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-50,15), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f( 50,30), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f( 50,45), v2f(10,10), "Crematory")));

		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( 50, 0), v2f(10, 10), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( 50, 15), v2f(10, 10), "Creator", false)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-50, 30), v2f(10, 10), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-50, 45), v2f(10, 10), "Creator", false)));

		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(0,0), v2f(12,12), "Fire1")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(0,15), v2f(12,12), "Frost1")));
		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(0,30), v2f(12,12), "Nature1")));
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(0,45), v2f(12,12), "Epic1")));
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
				if(timer_key_spawn > 1200/modifier_speed)
				{
					v2f siz(6.5,6.5), spd(0.011,0);
					uint type = rand()%2;
					if(type == 0) {
						CreateFireKey(v2f(50,0), siz, -spd); KeyGenWhiteBlack(10,10);
						if(count_key < count_key_max) { CreateFrosKey(v2f(50,15), siz, -spd); KeyGenWhiteBlack(10,10); }
					}
					if(type == 1) {
						CreateLifeKey(v2f(-50,30), siz, spd); KeyGenWhiteBlack(10,10);
						if(count_key < count_key_max) { CreateEpicKey(v2f(-50,45), siz, spd); KeyGenWhiteBlack(10,10); }
					}
					if(key_type >= 2) key_type = 0;
					timer_key_spawn = 0;
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

	virtual ~Level_37(void)
	{
	}
};