#pragma once
#include "oLevel.h"

class Level_6 : public oLevel
{
public:

	Level_6(void)
	{
		percent_need = 95;
		music = &sound->Theme[0];
		count_key_max = 100;

		vec_BG.push_back(make_shared<BackGround_L6>(BackGround_L6()));

		CreateBonusBar(10,15,15,20);

		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Nice\"", font_modeka);

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(40, 0), v2f(15,15), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(40,20), v2f(15,15), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(40,40), v2f(15,15), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(40,60), v2f(15,15), "Crematory")));

		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-40, 0), v2f(15,15), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-40,20), v2f(15,15), "Creator", false)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-40,40), v2f(15,15), "Creator", false)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-40,60), v2f(15,15), "Creator", false)));

		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(-20,0), v2f(15,15), "Nature1")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(-5,20), v2f(15,15), "Frost1")));
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(5,40), v2f(15,15), "Epic1")));
		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(20,60), v2f(15,15), "Fire1")));
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
				if(timer_key_spawn > 7000/modifier_speed)
				{
					v2f siz(10,10), spd(0.0065,0);
					CreateLifeKey(v2f(-40,0), siz, spd); KeyGenWhiteBlack(4,5);
					CreateFrosKey(v2f(-40,20), siz, spd); KeyGenWhiteBlack(4,5);
					CreateEpicKey(v2f(-40,40), siz, spd); KeyGenWhiteBlack(4,5);
					CreateFireKey(v2f(-40,60), siz, spd); KeyGenWhiteBlack(4,5);
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

	virtual ~Level_6(void)
	{
	}
};