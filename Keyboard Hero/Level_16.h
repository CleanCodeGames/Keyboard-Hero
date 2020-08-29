#pragma once
#include "oLevel.h"

class Level_16 : public oLevel
{
public:

	Level_16(void)
	{
		percent_need = 96;
		music = &sound->Theme[0];
		count_key_max = 120;

		vec_BG.push_back(make_shared<BackGround_L8>(BackGround_L8()));

		CreateBonusBar(14,18,18,23);

		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"The Portal Key\"", font_modeka);

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-7.5,7.5), v2f(15,15), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(7.5,52.5), v2f(15,15), "Crematory")));

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-37.5,22.5), v2f(15,15), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-37.5,37.5), v2f(15,15), "Crematory")));

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(37.5,22.5), v2f(15,15), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(37.5,37.5), v2f(15,15), "Crematory")));

		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( 7.5,22.5), v2f(12, 12), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-7.5,37.5), v2f(12, 12), "Creator", false)));

		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(7.5, 7.5), v2f(15,15), "T_1S", true)));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(-7.5,52.5), v2f(15,15), "T_2S", true)));

		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(-37.5, 7.5), v2f(15,15), "T_1E", false)));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(37.5,52.5), v2f(15,15), "T_2E", false)));

		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(-7.5, 22.5), v2f(15,15), "Fire1")));
		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(7.5, 37.5), v2f(15,15), "Fire2")));

		vec_Portal.push_back(make_shared<PortalTornadoFrost>(PortalTornadoFrost(v2f(-22.5, 22.5), v2f(15,15), "Frost1")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(22.5, 37.5), v2f(15,15), "Frost2")));

		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f(-22.5, 37.5), v2f(15,15), "Epic1")));
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(22.5, 22.5), v2f(15,15), "Epic2")));

		vec_Portal.push_back(make_shared<PortalTornadoNature>(PortalTornadoNature(v2f(-22.5,7.5), v2f(15,15), "Nature1")));
		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(22.5,52.5), v2f(15,15), "Nature2")));
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
					if(key_type < 2)
					{
						uint type = rand()%4;
						if(key_type == 0) 
						{
							if(type == 0) CreateLifeKey(v2f(7.5,22.5), v2f(9,9), v2f(0,-0.01));
							if(type == 1) CreateEpicKey(v2f(7.5,22.5), v2f(9,9), v2f(0.01,0));
							if(type == 2) CreateFireKey(v2f(7.5,22.5), v2f(9,9), v2f(0,0.01));
							if(type == 3) 
							{
								uint type2 = rand()%2;
								if(type2 == 0) CreateFireKey(v2f(7.5,22.5), v2f(9,9), v2f(-0.01,0));
								if(type2 == 1) CreateFrosKey(v2f(7.5,22.5), v2f(9,9), v2f(-0.01,0));
							}
						}
						if(key_type == 1) 
						{
							if(type == 0) CreateFireKey(v2f(-7.5,37.5), v2f(9,9), v2f(0,-0.01));
							if(type == 1)
							{
								uint type3 = rand()%2;
								if(type3 == 0) CreateFireKey(v2f(-7.5,37.5), v2f(9,9), v2f(0.01,0));
								if(type3 == 1) CreateFrosKey(v2f(-7.5,37.5), v2f(9,9), v2f(0.01,0));
							}
							if(type == 2) CreateLifeKey(v2f(-7.5,37.5), v2f(9,9), v2f(0, 0.01));
							if(type == 3) CreateEpicKey(v2f(-7.5,37.5), v2f(9,9), v2f(-0.01,0));
							
						}
						key_type++;
						if(key_type >= 2) 
							key_type = 0;
					}
					timer_key_spawn = 0;
					KeyGenWhiteBlack(7,9);
				}
			}
			Teleport("T_1S", "T_1E", v2f(0.01,0));
			Teleport("T_2S", "T_2E", v2f(-0.01,0));
			break;
		}
	}

	virtual void Draw()
	{
			oLevel::Draw();
			if(state == welcome) 
				wnd->draw(text_welcome);
	}

	virtual ~Level_16(void)
	{
	}
};