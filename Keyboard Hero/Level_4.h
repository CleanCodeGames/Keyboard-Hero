#pragma once
#include "oLevel.h"

class Level_4 : public oLevel
{
public:

	Level_4(void)
	{
		percent_need = 90;
		music = &sound->Theme[3];
		count_key_max = 80;

		vec_BG.push_back(make_shared<BackGround_L4>(BackGround_L4()));

		CreateBonusBar(8,10,10,12);

		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Runway\"", font_modeka);

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-50,20), v2f(15,15), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( 50, 20), v2f(15, 15), "Creator", true)));

		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(-30,20), v2f(15,15), "Fire1")));
		vec_Portal.push_back(make_shared<PortalTornadoFrost>(PortalTornadoFrost(v2f(-10,20), v2f(15,15), "Frost1")));
		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f(10,20), v2f(15,15), "Epic1")));
		vec_Portal.push_back(make_shared<PortalTornadoNature>(PortalTornadoNature(v2f(30,20), v2f(15,15), "Nature1")));
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
				if(timer_key_spawn > 2300/modifier_speed)
				{
					if(key_type < 2)
					{
						v2f siz(7,7), spd(0.006,0);
						uint type = rand()%2;
						if(key_type == 0) {
							if(type > 0) CreateFireKey(v2f(50,20), siz, -spd);
								else CreateFrosKey(v2f(50,20), siz, -spd);
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

	virtual ~Level_4(void)
	{
	}
};