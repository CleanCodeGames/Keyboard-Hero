#pragma once
#include"oLevel.h"

class Level_20 : public oLevel
{

public:

	Level_20(void)
	{
		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Rockfall\"", font_modeka);
		vec_BG.push_back(make_shared<BackGround_L4>(BackGround_L4()));
		music = &sound->BossTheme;
		CreateBonusBar(24,28,28,28);
		percent_need = 96;
		count_key_max = 120;
		count_key = 0; 
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f( -45, 60),  v2f(10,10),"Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-32.5, 60), v2f(10,10),"Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f( -20, 60), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-7.5, 60), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(7.5, 60),  v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(20, 60), v2f(10,10),	"Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(32.5, 60), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(45, 60), v2f(10,10),	"Crematory")));

		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( -45, 0),  v2f(10,10),	"Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-32.5, 0), v2f(10,10),	"Creator", false)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( -20, 0), v2f(10,10),		"Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-7.5, 0), v2f(10,10),		"Creator", false)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(7.5, 0),  v2f(10,10),		"Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(20, 0), v2f(10,10),		"Creator", false)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(32.5, 0), v2f(10,10),		"Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(45, 0), v2f(10,10),		"Creator", false)));

		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(-45, 30), v2f(10,10), "Fire")));
		vec_Portal.push_back(make_shared<PortalTornadoFrost>(PortalTornadoFrost(v2f(-32.5,  30), v2f(10,10), "Frost")));
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(-20,  30), v2f(10,10), "Epic")));
		vec_Portal.push_back(make_shared<PortalTornadoNature>(PortalTornadoNature(v2f(-7.5, 30), v2f(10,10), "Nature")));
		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(7.5, 30), v2f(10,10), "Fire2")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(20,  30), v2f(10,10), "Frost2")));
		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f(32.5,  30), v2f(10,10), "Epic2")));
		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(45, 30), v2f(10,10), "Nature2")));
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
					if(timer_key_spawn > 1300/modifier_speed)
					{
						key_type = rand()%8;
						
						v2f siz(7,7), spd(0.0,0.0115);
						if(key_type == 0) CreateFireKey(v2f(-45,  0), siz, spd);
						if(key_type == 1) CreateFrosKey(v2f(-32.5,0), siz, spd);
						if(key_type == 2) CreateEpicKey(v2f(-20, 0), siz, spd);
						if(key_type == 3) CreateLifeKey(v2f(-7.5,0), siz, spd);
						if(key_type == 4) CreateFireKey(v2f(7.5,  0), siz, spd);
						if(key_type == 5) CreateFrosKey(v2f(20.,0), siz, spd);
						if(key_type == 6) CreateEpicKey(v2f(32.5, 0), siz, spd);
						if(key_type == 7) CreateLifeKey(v2f(45,0), siz, spd);
						
						timer_key_spawn = 0;
						// Активируем босса, и ждём пока все символы будут поглощены
						if(count_key != 10) KeyGenWhiteBlack(9, 9);
						else isBoss = true;
					}
				}
				break;
			}
		}
		else
		{
			if(state == play && vec_Key.empty() && vec_Boss.empty()) 
				vec_Boss.push_back(make_shared<Boss_5>(Boss_5(25, 7250)));
		}
	}

	virtual void Draw()
	{ 
		oLevel::Draw();
		if(state == welcome) 
			wnd->draw(text_welcome);
	}

	virtual ~Level_20(void)
	{
	}
};