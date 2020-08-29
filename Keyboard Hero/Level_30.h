#pragma once
#include "oLevel.h"

class Level_30 : public oLevel
{
public:

	Level_30(void)
	{
		percent_need = 97;
		music = &sound->BossTheme;
		count_key_max = 200;

		vec_BG.push_back(make_shared<BackGround_L6>(BackGround_L6()));

		CreateBonusBar(30,36,36,42);

		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Garden Bed 2\"", font_modeka);
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(0,7.5), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(0,22.5), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(0,37.5), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(0,52.5), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(50,7.5), v2f(10, 10), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(50,22.5), v2f(10, 10), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(50,37.5), v2f(10, 10), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(50,52.5), v2f(10, 10), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-50,7.5), v2f(10, 10), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-50,22.5), v2f(10, 10), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-50,37.5), v2f(10, 10), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-50,52.5), v2f(10, 10), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(-35,7.5), v2f(12,12), "Fire1")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(-15,7.5), v2f(12,12), "Frost1")));
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(35,7.5), v2f(12,12), "Epic1")));
		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(15,7.5), v2f(12,12), "Nature1")));
		vec_Portal.push_back(make_shared<PortalTornadoFrost>(PortalTornadoFrost(v2f(-35,22.5), v2f(12,12), "Frost2")));
		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f(-15,22.5), v2f(12,12), "Epic2")));
		vec_Portal.push_back(make_shared<PortalTornadoNature>(PortalTornadoNature(v2f(35,22.5), v2f(12,12), "Nature2")));
		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(15,22.5), v2f(12,12), "Fire2")));
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(-35,37.5), v2f(12,12), "Epic3")));
		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(-15,37.5), v2f(12,12), "Nature3")));
		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(35,37.5), v2f(12,12), "Fire3")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(15,37.5), v2f(12,12), "Frost3")));
		vec_Portal.push_back(make_shared<PortalTornadoNature>(PortalTornadoNature(v2f(-35,52.5), v2f(12,12), "Nature4")));
		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(-15,52.5), v2f(12,12), "Fire4")));
		vec_Portal.push_back(make_shared<PortalTornadoFrost>(PortalTornadoFrost(v2f(35,52.5), v2f(12,12), "Frost4")));
		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f(15,52.5), v2f(12,12), "Epic4")));
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
		if(!isBoss)
		{
			switch(state)
			{
			case STATE::welcome: Welcome(); break;

			case STATE::play:
				
				if(count_key < count_key_max)
				{
					timer_key_spawn += time;
					if(timer_key_spawn > 1000/modifier_speed)
					{
						if(key_type < 8)
						{
							uint type = rand()%2;
							v2f siz(7,7), spd(0.011,0);
							if(key_type == 0) {
								if(type > 0) CreateFireKey(v2f(-50,7.5), siz, spd);
								else CreateFrosKey(v2f(-50,7.5), siz, spd);
							}
							if(key_type == 1) {
								if(type > 0) CreateEpicKey(v2f(50,7.5), siz, -spd);
								else CreateLifeKey(v2f(50,7.5), siz, -spd);
							}
							if(key_type == 2) {
								if(type > 0) CreateFrosKey(v2f(-50,22.5), siz, spd);
								else CreateEpicKey(v2f(-50,22.5), siz, spd);
							}
							if(key_type == 3) {
								if(type > 0)  CreateLifeKey(v2f(50,22.5), siz, -spd);
								else CreateFireKey(v2f(50,22.5), siz, -spd);
							}
							if(key_type == 4) {
								if(type > 0) CreateEpicKey(v2f(-50,37.5), siz, spd);
								else CreateLifeKey(v2f(-50,37.5), siz, spd);
							}
							if(key_type == 5) {
								if(type > 0) CreateFireKey(v2f(50,37.5), siz, -spd);
								else CreateFrosKey(v2f(50,37.5), siz, -spd);
							}
							if(key_type == 6) {
								if(type > 0) CreateLifeKey(v2f(-50,52.5), siz, spd);
								else CreateFireKey(v2f(-50,52.5), siz, spd);
							}
							if(key_type == 7) {
								if(type > 0) CreateFrosKey(v2f(50,52.5), siz, -spd);
								else CreateEpicKey(v2f(50,52.5), siz, -spd);
							}
							key_type++;
							if(key_type >= 8) key_type = 0;
						}
						timer_key_spawn = 0;
						// Активируем босса, и ждём пока все символы будут поглощены
						if(count_key != 10) KeyGenWhiteBlack(10, 10);
						else isBoss = true;
					}
				}
				break;
			}
		}
		else
		{
			if(state == play && vec_Key.empty() && vec_Boss.empty()) 
				vec_Boss.push_back(make_shared<Boss_3>(Boss_3(1, 6)));
		}
	}

	virtual void Draw()
	{
			oLevel::Draw();
			if(state == welcome) 
				wnd->draw(text_welcome);
	}

	virtual ~Level_30(void)
	{
	}
};