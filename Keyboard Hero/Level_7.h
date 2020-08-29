#pragma once
#include "oLevel.h"

class Level_7 : public oLevel
{
public:

	Level_7(void)
	{
		percent_need = 95;
		music = &sound->Theme[1];
		count_key_max = 100;

		vec_BG.push_back(make_shared<BackGround_L7>(BackGround_L7()));

		CreateBonusBar(10,15,15,20);

		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"First Rainbow\"", font_modeka);

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(50,20), v2f(16,16), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( -50, 20), v2f(16, 16), "Creator", false)));

		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(-25,20), v2f(15,15), "Fire1")));
		vec_PortalMulti.push_back(make_shared<PortalMulticolor>(PortalMulticolor(v2f(25,  20), v2f(20,20), "Nature", "Nature")));
		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f(0, 20), v2f(15,15), "Frost1")));
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
				if(timer_key_spawn > 2100/modifier_speed)
				{
					if(key_type < 2)
					{
						v2f siz(9,9), spd(0.0065,0);
						uint type = rand()%2;
						if(key_type == 0) {
							if(type > 0) CreateFireKey(v2f(-50,20), siz, spd);
								else CreateFrosKey(v2f(-50,20), siz, spd);
						}
						if(key_type == 1) {
							if(type > 0) CreateLifeKey(v2f(-50,20), siz, spd);
								else CreateEpicKey(v2f(-50,20), siz, spd);
						}
						key_type++;
						if(key_type >= 2) key_type = 0;
					}
					timer_key_spawn = 0;
					KeyGenWhiteBlack(10, 10);
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

	virtual ~Level_7(void)
	{
	}
};