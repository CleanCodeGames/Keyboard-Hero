#pragma once
#include "oLevel.h"

class Level_44 : public oLevel
{
public:

	Level_44(void)
	{
		percent_need = 99;
		music = &sound->Theme[3];
		count_key_max = 300;

		vec_BG.push_back(make_shared<BackGround_L8>(BackGround_L8()));

		CreateBonusBar(40,55,55,65);

		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Chance 2\"", font_modeka);
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-50, 15), v2f(10, 10), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-50, 45), v2f(10, 10), "Creator", false)));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(50,30), v2f(10,10), "Crematory")));

		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(50, 15), v2f(10,10), "T_1S", true)));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(50, 45), v2f(10,10), "T_2S", true)));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(-50, 30), v2f(10,10), "T_1E", false)));

		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(-30,15), v2f(10,10), "Fire")));
		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(-10,15), v2f(10,10), "Nature")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(10,15), v2f(10,10), "Frost")));
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(30,15), v2f(10,10), "Epic")));

		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(30,45), v2f(10,10), "Fire1")));
		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(10,45), v2f(10,10), "Nature1")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(-10,45), v2f(10,10), "Frost1")));
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(-30,45), v2f(10,10), "Epic1")));

		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(-10,30), v2f(15,15), "Fire2")));
		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(-30,30), v2f(15,15), "Nature2")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(30,30), v2f(15,15), "Frost2")));
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(10,30), v2f(15,15), "Epic2")));
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
					if(key_type < 2)
					{
						uint type = rand()%4;
						v2f siz(7,7), spd(0.011,0);
						if(key_type == 0) {
							if(type == 0) CreateEpicKey(v2f(-50,15), siz, spd);
							if(type == 1) CreateFrosKey(v2f(-50,15), siz, spd);
							if(type == 2) CreateLifeKey(v2f(-50,15), siz, spd);
							if(type == 3) CreateLifeKey(v2f(-50,15), siz, spd);
						}
						if(key_type == 1) {
							if(type == 0) CreateEpicKey(v2f(-50,45), siz, spd);
							if(type == 1) CreateFireKey(v2f(-50,45), siz, spd);
							if(type == 2) CreateLifeKey(v2f(-50,45), siz, spd);
							if(type == 3) CreateLifeKey(v2f(-50,45), siz, spd);
						}

						key_type++;
						if(key_type >= 2) 
							key_type = 0;
					}
					timer_key_spawn = 0;
					KeyGenWhiteBlack(12,12);
				}
			}

			Teleport("T_1S", "T_1E", v2f(0.013,0));
			Teleport("T_2S", "T_1E", v2f(0.013,0));
			break;
		}
	}

	virtual void Draw()
	{
			oLevel::Draw();
			if(state == welcome) 
				wnd->draw(text_welcome);
	}

	virtual ~Level_44(void)
	{
	}
};