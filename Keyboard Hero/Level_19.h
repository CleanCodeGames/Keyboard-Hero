#pragma once
#include "oLevel.h"

class Level_19 : public oLevel
{
public:

	Level_19(void)
	{
		percent_need = 96;
		music = &sound->Theme[3];
		count_key_max = 150;

		vec_BG.push_back(make_shared<BackGround_L3>(BackGround_L3()));

		CreateBonusBar(20,24,28,32);

		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Easier to nowhere\"", font_modeka);

		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-50,0), v2f(17.5,17.5), "Creator", true)));
		vec_PortalMulti.push_back(make_shared<PortalMulticolor>(PortalMulticolor(v2f(-25,0), v2f(17.5,17.5), "Rainbow", "Nature")));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(25, 0), v2f(15,15), "T_5E", false)));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(50, 0), v2f(15,15), "T_1S", true)));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(-50, 20), v2f(15,15), "T_4S", true)));
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(-25, 20), v2f(15,15), "Epic1")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(0, 20), v2f(15,15), "Frost1")));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(25, 20), v2f(15,15), "T_3E", false)));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(50, 20), v2f(15,15), "T_2S", true)));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(-50, 40), v2f(15,15), "T_4E", false)));
		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(-25, 40), v2f(15,15), "Fire1")));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(0, 40), v2f(15,15), "T_5S", true)));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(25,40), v2f(17.5,17.5), "Crematory")));
		vec_Portal.push_back(make_shared<PortalTornadoNature>(PortalTornadoNature(v2f(50,40), v2f(15,15), "Nature1")));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(-50, 60), v2f(15,15), "T_2E", false)));
		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(-25,60), v2f(15,15), "Nature2")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(0, 60), v2f(15,15), "Frost2")));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(25, 60), v2f(15,15), "T_3S", true)));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(50, 60), v2f(15,15), "T_1E", false)));
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
					uint type = rand()%4;
					if(type == 0) CreateLifeKey(v2f(-50,0), v2f(9,9), v2f(0.010,0));
					if(type == 1) CreateFireKey(v2f(-50,0), v2f(9,9), v2f(0.010,0));
					if(type == 2) CreateEpicKey(v2f(-50,0), v2f(9,9), v2f(0.010,0));
					if(type == 3) CreateFrosKey(v2f(-50,0), v2f(9,9), v2f(0.010,0));
					timer_key_spawn = 0;
					KeyGenWhiteBlack(8,9);
				}
			}
			Teleport("T_1S","T_1E", v2f(0,-0.010));
			Teleport("T_2S","T_2E", v2f(0.010,0));
			Teleport("T_3S","T_3E", v2f(-0.010,0));
			Teleport("T_4S","T_4E", v2f(0.010,0));
			Teleport("T_5S","T_5E", v2f(0,0.02));
			break;
		}
	}
	virtual void Draw()
	{
			oLevel::Draw();
			if(state == welcome) 
				wnd->draw(text_welcome);
	}

	virtual ~Level_19(void)
	{
	}
};