#pragma once
#include "oLevel.h"

class Level_3 : public oLevel
{
public:

	Level_3(void)
	{
		percent_need = 90;
		music = &sound->Theme[2];
		count_key_max = 70;

		vec_BG.push_back(make_shared<BackGround_L3>(BackGround_L3()));

		CreateBonusBar(6,8,8,10);

		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Be Happy\"", font_modeka);

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(0,20), v2f(15,15), "Crematory")));

		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( 50, 20), v2f(15, 15), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-50, 20), v2f(15, 15), "Creator", false)));

		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(-32,20), v2f(15,15), "Fire1")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(-16, 20), v2f(15,15), "Frost1")));
		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f(32, 20), v2f(15,15), "Epic1")));
		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(16,20), v2f(15,15), "Nature1")));
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
				if(timer_key_spawn > 2400/modifier_speed)
				{
					v2f siz(7,7), spd(0.0055,0);
					if(key_type < 2)
					{
						uint type = rand()%2;
						if(key_type == 0) {
							if(type > 0) CreateFireKey(v2f(-50,20), siz, spd);
								else CreateFrosKey(v2f(-50,20), siz, spd);
						}
						if(key_type == 1) {
							if(type > 0) CreateLifeKey(v2f(50,20), siz, -spd);
								else CreateEpicKey(v2f(50,20), siz, -spd);
						}
						key_type++;
						if(key_type >= 2) key_type = 0;
					}
					timer_key_spawn = 0;
					KeyGenWhiteBlack(2,5);
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

	virtual ~Level_3(void)
	{
	}
};