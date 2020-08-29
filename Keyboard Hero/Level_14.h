#pragma once
#include "oLevel.h"

class Level_14 : public oLevel
{
public:

	Level_14(void)
	{
		percent_need = 97;
		music = &sound->Theme[3];
		count_key_max = 160;
		vec_BG.push_back(make_shared<BackGround_L6>(BackGround_L6()));
		CreateBonusBar(25,30,30,35);
		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);
		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Big Alone\"", font_modeka);
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-50,0), v2f(15,15), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-50,40), v2f(15,15), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( 50,0), v2f(15, 15), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( 50,40), v2f(15, 15), "Creator", false)));
		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(-30,0), v2f(15,15), "Fire1")));
		vec_Portal.push_back(make_shared<PortalTornadoFrost>(PortalTornadoFrost(v2f(-10,0), v2f(15,15), "Frost1")));
		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f(10,0), v2f(15,15), "Epic1")));
		vec_Portal.push_back(make_shared<PortalTornadoNature>(PortalTornadoNature(v2f(30,0), v2f(15,15), "Nature1")));
		vec_PortalMulti.push_back(make_shared<PortalMulticolor>(PortalMulticolor(v2f(0,40), v2f(20,20), "Epic", "Epic")));
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
					if(key_type < 2)
					{
						uint type = rand()%4;
						if(key_type == 0)
						{
							v2f siz(9,9), spd(0.0095,0);
							if(type == 0) CreateFireKey(v2f(50,0), siz, -spd);
							if(type == 1) CreateFrosKey(v2f(50,0), siz, -spd);
							if(type == 2) CreateLifeKey(v2f(50,0), siz, -spd);
							if(type == 3) CreateEpicKey(v2f(50,0), siz, -spd);
						}
						else
						{
							v2f siz(10,10), spd(0.0075,0);
							if(type == 0 || type == 1) CreateFrosKey(v2f(50,40), siz, -spd);
							if(type == 2 || type == 3) CreateLifeKey(v2f(50,40), siz, -spd);
						}
						key_type++;
						if(key_type >= 2) key_type = 0;
					}
					timer_key_spawn = 0;
					KeyGenWhiteBlack(7,9);
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

	virtual ~Level_14(void)
	{
	}
};