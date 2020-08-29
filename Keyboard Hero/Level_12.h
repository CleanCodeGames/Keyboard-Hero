#pragma once
#include "oLevel.h"

class Level_12 : public oLevel
{
public:

	Level_12(void)
	{
		percent_need = 97;
		music = &sound->Theme[1];
		count_key_max = 120;

		vec_BG.push_back(make_shared<BackGround_L4>(BackGround_L4()));

		CreateBonusBar(15,18,18,27);

		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Four-to-one\"", font_modeka);

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(0,0), v2f(15,15), "Crematory")));

		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(-20, 45), v2f(12,12), "T_1S", true)));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(-40, 45), v2f(12,12), "T_2S", true)));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f( 20, 45), v2f(12,12), "T_3S", true)));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f( 40, 45), v2f(12,12), "T_4S", true)));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f( 0,  45), v2f(12,12), "T_1E", false)));

		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-20, 0), v2f(12, 12), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-40, 0), v2f(12, 12), "Creator", false)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( 20, 0), v2f(12, 12), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( 40, 0), v2f(12, 12), "Creator", false)));

		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(-40,15), v2f(12,12), "Nature1")));
		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(-20,15), v2f(12,12), "Fire1")));
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f( 20,15), v2f(12,12), "Epic1")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f( 40,15), v2f(12,12), "Frost1")));

		vec_Portal.push_back(make_shared<PortalTornadoNature>(PortalTornadoNature(v2f(20,30), v2f(12,12), "Nature2")));
		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(40,30), v2f(12,12), "Fire2")));
		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f(-20,30), v2f(12,12), "Epic2")));
		vec_Portal.push_back(make_shared<PortalTornadoFrost>(PortalTornadoFrost(v2f(-40,30), v2f(12,12), "Frost2")));

		vec_PortalMulti.push_back(make_shared<PortalMulticolor>(PortalMulticolor(v2f(0, 20), v2f(20,20), "Epic", "Epic")));
		
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
				if(timer_key_spawn > 1800/modifier_speed)
				{
					if(key_type < 4)
					{
						uint type = rand()%3;
						v2f siz(7,7), spd(0,0.0085);
						if(key_type == 0) {
							if(type == 0) CreateEpicKey(v2f(-40,0), siz, spd);
							if(type == 1) CreateFrosKey(v2f(-40,0), siz, spd);
							if(type == 2) CreateLifeKey(v2f(-40,0), siz, spd);
						}
						if(key_type == 1) {
							if(type == 0) CreateEpicKey(v2f(-20,0), siz, spd);
							if(type == 1) CreateFireKey(v2f(-20,0), siz, spd);
							if(type == 2) CreateLifeKey(v2f(-20,0), siz, spd);
						}
						if(key_type == 2) {
							if(type == 0) CreateEpicKey(v2f(20,0), siz, spd);		
							if(type == 1) CreateFrosKey(v2f(20,0), siz, spd);	
							if(type == 2) CreateLifeKey(v2f(20,0), siz, spd);
						}
						if(key_type == 3) {
							if(type == 0) CreateFireKey(v2f(40,0), siz, spd);	
							if(type == 1) CreateFrosKey(v2f(40,0), siz, spd);
							if(type == 2) CreateLifeKey(v2f(40,0), siz, spd);
						}

						key_type++;
						if(key_type >= 4) 
							key_type = 0;
					}
					timer_key_spawn = 0;
					KeyGenWhiteBlack(7,8);
				}
			}

			Teleport("T_1S", "T_1E", v2f(0,-0.01));
			Teleport("T_2S", "T_1E", v2f(0,-0.01));
			Teleport("T_3S", "T_1E", v2f(0,-0.01));
			Teleport("T_4S", "T_1E", v2f(0,-0.01));
			break;
		}
	}

	virtual void Draw()
	{
			oLevel::Draw();
			if(state == welcome) 
				wnd->draw(text_welcome);
	}

	virtual ~Level_12(void)
	{
	}
};