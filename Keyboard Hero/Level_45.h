#pragma once
#include "oLevel.h"

class Level_45 : public oLevel
{
public:

	Level_45(void)
	{
		percent_need = 99;
		music = &sound->Theme[1];
		count_key_max = 400;

		vec_BG.push_back(make_shared<BackGround_L5>(BackGround_L5()));

		CreateBonusBar(10,60,75,90);

		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Large pendulum 2\"", font_modeka);

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-50,0), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-50,20), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-50,40), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-50,60), v2f(10,10), "Crematory")));

		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(50,0), v2f(10,10), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(50,20), v2f(10,10), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(50,40), v2f(10,10), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(50,60), v2f(10,10), "Creator", true)));

		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f(-10, 0), v2f(12,12), "Epic")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(-10, 20), v2f(12,12), "Frost")));
		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(-10, 40), v2f(12,12), "Fire")));
		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(-10,60), v2f(12,12), "Nature")));

		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(10, 0), v2f(12,12), "Nature1")));
		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(10, 20), v2f(12,12), "Fire1")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(10, 40), v2f(12,12), "Frost1")));
		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f(10,60), v2f(12,12), "Epic1")));
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
			static float alpha = 0.5;
			switch(state)
			{
			case STATE::welcome: Welcome(); break;

			case STATE::play:

				vec_Portal[8]->setPosition(v2f(((25*scr_1) * cos(alpha/modifier_speed)) - (scr_1*10),vec_Portal[8]->getPosition().y));
				vec_Portal[9]->setPosition(v2f(((25*scr_1) * cos(alpha/modifier_speed)) - (scr_1*10),vec_Portal[9]->getPosition().y));
				vec_Portal[10]->setPosition(v2f(((25*scr_1) * cos(alpha/modifier_speed)) - (scr_1*10),vec_Portal[10]->getPosition().y));
				vec_Portal[11]->setPosition(v2f(((25*scr_1) * cos(alpha/modifier_speed)) - (scr_1*10),vec_Portal[11]->getPosition().y));

				vec_Portal[12]->setPosition(v2f(((25*scr_1) * cos(alpha/modifier_speed)) + (scr_1*10),vec_Portal[12]->getPosition().y));
				vec_Portal[13]->setPosition(v2f(((25*scr_1) * cos(alpha/modifier_speed)) + (scr_1*10),vec_Portal[13]->getPosition().y));
				vec_Portal[14]->setPosition(v2f(((25*scr_1) * cos(alpha/modifier_speed)) + (scr_1*10),vec_Portal[14]->getPosition().y));
				vec_Portal[15]->setPosition(v2f(((25*scr_1) * cos(alpha/modifier_speed)) + (scr_1*10),vec_Portal[15]->getPosition().y));
				alpha += 0.0003*time;
				
				if(count_key < count_key_max)
				{
					timer_key_spawn += time;
					if(timer_key_spawn > 1000/modifier_speed)
					{
						key_type = rand()%2;
						uint type = rand()%4;
						if(type == 0)
						{
							if(key_type == 0) CreateEpicKey(v2f(50,0), v2f(7,7), v2f(-0.013,0));
							else CreateLifeKey(v2f(50,0), v2f(7,7), v2f(-0.013,0));
						}
						if(type == 1)
						{
							if(key_type == 0) CreateFrosKey(v2f(50,20), v2f(7,7), v2f(-0.013,0));
							else CreateFireKey(v2f(50,20), v2f(7,7), v2f(-0.013,0));
						}
						if(type == 2)
						{
							if(key_type == 0) CreateFrosKey(v2f(50,40), v2f(7,7), v2f(-0.013,0));
							else CreateFireKey(v2f(50,40), v2f(7,7), v2f(-0.013,0));
						}
						if(type == 3)
						{
							if(key_type == 0) CreateEpicKey(v2f(50,60), v2f(7,7), v2f(-0.013,0));
							else CreateLifeKey(v2f(50,60), v2f(7,7), v2f(-0.013,0));
						}

						timer_key_spawn = 0;
						// Активируем босса, и ждём пока все символы будут поглощены
						if(count_key != 10) KeyGenWhiteBlack(15, 12);
						else isBoss = true;
					}
				}
				break;
			}
		}
		else
		{
			if(state == play && vec_Key.empty() && vec_Boss.empty()) 
				vec_Boss.push_back(make_shared<Boss_4>(Boss_4(150, 500)));
		}
	}
	virtual void Draw()
	{
			oLevel::Draw();
			if(state == welcome) 
				wnd->draw(text_welcome);
	}

	virtual ~Level_45(void)
	{
	}
};