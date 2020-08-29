#pragma once
#include "oLevel.h"

class Level_2 : public oLevel
{
public:

	Level_2(void)
	{
		percent_need = 90;
		music = &sound->Theme[1];
		count_key_max = 70;

		vec_BG.push_back(make_shared<BackGround_L2>(BackGround_L2()));

		CreateBonusBar(7,10,10,10);

		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Up or Down\"", font_modeka);

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-10, 0), v2f(12,12), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f( 10, 0), v2f(12,12), "Crematory")));

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-10, 60), v2f(12,12), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f( 10, 60), v2f(12,12), "Crematory")));

		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( 10, 30), v2f(12, 12), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-10, 30), v2f(12, 12), "Creator", false)));

		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(-10,15), v2f(12,12), "Fire1")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(-10,45), v2f(12,12), "Frost1")));
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(10,15), v2f(12,12), "Epic1")));
		vec_Portal.push_back(make_shared<PortalTornadoNature>(PortalTornadoNature(v2f(10,45), v2f(12,12), "Nature1")));
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
				if(timer_key_spawn > 2500/modifier_speed)
				{
					if(key_type < 2)
					{
						v2f siz(7,7), spd(0,0.0055);
						uint type = rand()%2;
						if(key_type == 0) {
							if(type > 0) CreateFireKey(v2f(-10,30), siz, -spd);
								else CreateFrosKey(v2f(-10,30), siz, spd);
						}
						if(key_type == 1) {
							if(type > 0) CreateLifeKey(v2f(10,30), siz, spd);
								else CreateEpicKey(v2f(10,30), siz, -spd);
						}
						key_type++;
						if(key_type >= 2) key_type = 0;
					}
					timer_key_spawn = 0;
					KeyGenWhiteBlack(1,5);
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

	virtual ~Level_2(void)
	{
	}
};