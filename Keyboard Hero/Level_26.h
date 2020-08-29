#pragma once
#include "oLevel.h"

class Level_26 : public oLevel
{
public:

	Level_26(void)
	{
		percent_need = 97;
		music = &sound->Theme[0];
		count_key_max = 180;

		vec_BG.push_back(make_shared<BackGround_L2>(BackGround_L2()));

		CreateBonusBar(32,36,36,40);

		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Nice 2\"", font_modeka);

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(40, 0), v2f(12,12), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(40,20), v2f(12,12), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(40,40), v2f(12,12), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(40,60), v2f(12,12), "Crematory")));

		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-40, 0), v2f(12,12), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-40,20), v2f(12,12), "Creator", false)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-40,40), v2f(12,12), "Creator", false)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-40,60), v2f(12,12), "Creator", false)));

		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(-20,0), v2f(12,12), "Nature1")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(-5,20), v2f(12,12), "Frost1")));
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(5,40), v2f(12,12), "Epic1")));
		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(20,60), v2f(12,12), "Fire1")));
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
				if(timer_key_spawn > 4000/modifier_speed)
				{
					v2f siz(7,7), spd(0.012,0);
					CreateLifeKey(v2f(-40,0), siz, spd); KeyGenWhiteBlack(10,10);
					CreateFrosKey(v2f(-40,20), siz, spd); KeyGenWhiteBlack(10,10);
					CreateEpicKey(v2f(-40,40), siz, spd); KeyGenWhiteBlack(10,10);
					CreateFireKey(v2f(-40,60), siz, spd); KeyGenWhiteBlack(10,10);
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

	virtual ~Level_26(void)
	{
	}
};