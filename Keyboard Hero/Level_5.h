#pragma once
#include "oLevel.h"
class Level_5 : public oLevel
{
public:

	Level_5(void)
	{
		percent_need = 90;
		music = &sound->BossTheme;
		count_key_max = 90;

		vec_BG.push_back(make_shared<BackGround_L5>(BackGround_L5()));

		CreateBonusBar(8,12,12,15);

		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Galaxian\"", font_modeka);

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(0,20), v2f(15,15), "Crematory")));

		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(50, 0), v2f(15,15), "T_1S", true)));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(-50, 20), v2f(15,15), "T_1E", false)));

		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(-50, 40), v2f(15,15), "T_2S", true)));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(50, 20), v2f(15,15), "T_2E", false)));

		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-50, 0), v2f(15, 15), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(50, 40), v2f(15, 15), "Creator", false)));

		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(0, 40), v2f(15,15), "Fire1")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(0,0), v2f(15,15), "Frost1")));
		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f(-25, 20), v2f(15,15), "Epic1")));
		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(25,20), v2f(15,15), "Nature1")));
	}

	virtual void Action()
	{
		oLevel::Action();

		if(!isPauseGame)
			for(auto boss: vec_Boss) 
				boss->Action();
	}
	
	virtual void Update()
	{
		oLevel::Update();
		if(state == play)
		{
			Teleport("T_1S", "T_1E", v2f(0.0055,0));
			Teleport("T_2S", "T_2E", v2f(-0.0055,0));
		}

		if(!isBoss)
		{
			switch(state)
			{
			case STATE::welcome: Welcome(); break;

			case STATE::play:
				
				if(count_key < count_key_max)
				{
					timer_key_spawn += time;
					if(timer_key_spawn > 2450/modifier_speed)
					{
						if(key_type < 2)
						{
							const v2f spd(0.0055,0);
							const v2f siz(7,7);
							uint type = rand()%2;
							if(key_type == 0) {
								if(type > 0) CreateEpicKey(v2f(-50,0), siz, spd);
								else CreateFrosKey(v2f(-50,0), siz, spd);
							}
							if(key_type == 1) {
								if(type > 0) CreateLifeKey(v2f(50,40), siz, -spd);
								else CreateFireKey(v2f(50,40), siz, -spd);
							}
							
							key_type++;
							if(key_type >= 2) key_type = 0;
						}
						timer_key_spawn = 0;
						// Активируем босса, и ждём пока все символы будут поглощены
						if(count_key != 10) KeyGenWhiteBlack(3, 5);
						else isBoss = true;
					}
				}
				break;
			}
		}
		else
		{
			if(state == play && vec_Key.empty() && vec_Boss.empty()) 
				vec_Boss.push_back(make_shared<Boss_3>(Boss_3(1,3)));
		}
	}

	virtual void Draw()
	{
			oLevel::Draw();
			if(state == welcome) 
				wnd->draw(text_welcome);
	}

	virtual ~Level_5(void)
	{
	}
};