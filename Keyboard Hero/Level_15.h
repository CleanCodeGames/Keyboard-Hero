#pragma once
#include "oLevel.h"

class Level_15 : public oLevel
{
private:

	bool is_create_boss;

public:

	Level_15(void) : is_create_boss(false)
	{
		percent_need = 95;
		music = &sound->BossTheme;
		count_key_max = 160;

		vec_BG.push_back(make_shared<BackGround_L7>(BackGround_L7()));

		CreateBonusBar(30,25,25,20);

		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Go Go!\"", font_modeka);

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(50, 0), v2f(15,15), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(50,20), v2f(15,15), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(50,40), v2f(15,15), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(50,60), v2f(15,15), "Crematory")));

		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-50, 0), v2f(15,15), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-50,20), v2f(15,15), "Creator", false)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-50,40), v2f(15,15), "Creator", false)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-50,60), v2f(15,15), "Creator", false)));

		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(30,0), v2f(20,20), "Fire1")));
		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(10,20), v2f(20,20), "Fire2")));
		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(-10,40), v2f(20,20), "Fire3")));
		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(-30,60), v2f(20,20), "Fire4")));

		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f(30, 20), v2f(20,20), "Epic1")));
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(10, 40), v2f(20,20), "Epic2")));
		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f(-10, 60), v2f(20,20), "Epic3")));

		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(30,  40), v2f(20,20), "Frost1")));
		vec_Portal.push_back(make_shared<PortalTornadoFrost>(PortalTornadoFrost(v2f(10,  60), v2f(20,20), "Frost2")));

		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(30,60), v2f(20,20), "Nature1")));
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
					if(timer_key_spawn > 5500/modifier_speed)
					{
						v2f siz(7,7), spd(0.009,0);
						
						if(count_key < count_key_max)
						{
							CreateFireKey(v2f(-50,0), siz, spd);
							KeyGenWhiteBlack(5, 9);
						}

						uint type = rand()%2;
						if(count_key < count_key_max)
						{
							if(type == 0) CreateEpicKey(v2f(-50,20), siz, spd);
							if(type == 1) CreateFireKey(v2f(-50,20), siz, spd);
							KeyGenWhiteBlack(5, 9);
						}

						type = rand()%3;
						if(count_key < count_key_max) 
						{
							if(type == 0) CreateFrosKey(v2f(-50,40), siz, spd);
							if(type == 1) CreateEpicKey(v2f(-50,40), siz, spd);
							if(type == 2) CreateFireKey(v2f(-50,40), siz, spd);
							KeyGenWhiteBlack(5, 9);
						}
						
						type = rand()%4;
						if(count_key < count_key_max) 
						{	
							if(type == 0) CreateLifeKey(v2f(-50,60), siz, spd);
							if(type == 1) CreateEpicKey(v2f(-50,60), siz, spd);
							if(type == 2) CreateFireKey(v2f(-50,60), siz, spd);
							if(type == 3) CreateLifeKey(v2f(-50,60), siz, spd);
							KeyGenWhiteBlack(5, 9);
						}
						timer_key_spawn = 0;
						// Активируем босса, и ждём пока все символы будут поглощены
						if(!is_create_boss && count_key > 9)
						{
							isBoss = true;
							is_create_boss = true;
						}
						
					}
				}
				break;
			}
		}
		else
		{
			if(state == play && vec_Key.empty() && vec_Boss.empty()) 
				vec_Boss.push_back(make_shared<Boss_2>(Boss_2(75, 1500)));
		}
	}

	virtual void Draw()
	{
			oLevel::Draw();
			if(state == welcome) 
				wnd->draw(text_welcome);
	}

	virtual ~Level_15(void)
	{
	}
};