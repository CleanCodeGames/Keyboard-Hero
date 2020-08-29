#pragma once
#include "oLevel.h"

class Level_36 : public oLevel
{
public:

	Level_36(void)
	{
		percent_need = 97;
		music = &sound->Theme[0];
		count_key_max = 224;

		vec_BG.push_back(make_shared<BackGround_L4>(BackGround_L4()));

		CreateBonusBar(32,36,36,42);

		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"The Portal Key 2\"", font_modeka);

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-7.5,7.5), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(7.5,52.5), v2f(10,10), "Crematory")));

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-37.5,22.5), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-37.5,37.5), v2f(10,10), "Crematory")));

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(37.5,22.5), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(37.5,37.5), v2f(10,10), "Crematory")));

		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( 7.5,22.5), v2f(10, 10), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-7.5,37.5), v2f(10, 10), "Creator", false)));

		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(7.5, 7.5), v2f(12,12), "T_1S", true)));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(-7.5,52.5), v2f(12,12), "T_2S", true)));

		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(-37.5, 7.5), v2f(12,12), "T_1E", false)));
		vec_Teleport.push_back(make_shared<PortalTeleport>(PortalTeleport(v2f(37.5,52.5), v2f(12,12), "T_2E", false)));

		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(-7.5, 22.5), v2f(12,12), "Fire1")));
		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(7.5, 37.5), v2f(12,12), "Fire2")));

		vec_Portal.push_back(make_shared<PortalTornadoFrost>(PortalTornadoFrost(v2f(-22.5, 22.5), v2f(12,12), "Frost1")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(22.5, 37.5), v2f(12,12), "Frost2")));

		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f(-22.5, 37.5), v2f(12,12), "Epic1")));
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(22.5, 22.5), v2f(12,12), "Epic2")));

		vec_Portal.push_back(make_shared<PortalTornadoNature>(PortalTornadoNature(v2f(-22.5,7.5), v2f(12,12), "Nature1")));
		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(22.5,52.5), v2f(12,12), "Nature2")));
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
				if(timer_key_spawn > 1200/modifier_speed)
				{
					if(key_type < 2)
					{
						uint type = rand()%4;
						if(key_type == 0) 
						{
							if(type == 0) CreateLifeKey(v2f(7.5,22.5), v2f(7,7), v2f(0,-0.013));
							if(type == 1) CreateEpicKey(v2f(7.5,22.5), v2f(7,7), v2f(0.013,0));
							if(type == 2) CreateFireKey(v2f(7.5,22.5), v2f(7,7), v2f(0,0.013));
							if(type == 3) 
							{
								uint type2 = rand()%2;
								if(type2 == 0) CreateFireKey(v2f(7.5,22.5), v2f(7,7), v2f(-0.013,0));
								if(type2 == 1) CreateFrosKey(v2f(7.5,22.5), v2f(7,7), v2f(-0.013,0));
							}
						}
						if(key_type == 1) 
						{
							if(type == 0) CreateFireKey(v2f(-7.5,37.5), v2f(7,7), v2f(0,-0.013));
							if(type == 1)
							{
								uint type3 = rand()%2;
								if(type3 == 0) CreateFireKey(v2f(-7.5,37.5), v2f(7,7), v2f(0.013,0));
								if(type3 == 1) CreateFrosKey(v2f(-7.5,37.5), v2f(7,7), v2f(0.013,0));
							}
							if(type == 2) CreateLifeKey(v2f(-7.5,37.5), v2f(7,7), v2f(0, 0.013));
							if(type == 3) CreateEpicKey(v2f(-7.5,37.5), v2f(7,7), v2f(-0.013,0));
							
						}
						key_type++;
						if(key_type >= 2) 
							key_type = 0;
					}
					timer_key_spawn = 0;
					KeyGenWhiteBlack(10,10);
				}
			}
			Teleport("T_1S", "T_1E", v2f(0.013,0));
			Teleport("T_2S", "T_2E", v2f(-0.013,0));
			break;
		}
	}

	virtual void Draw()
	{
			oLevel::Draw();
			if(state == welcome) 
				wnd->draw(text_welcome);
	}

	virtual ~Level_36(void)
	{
	}
};