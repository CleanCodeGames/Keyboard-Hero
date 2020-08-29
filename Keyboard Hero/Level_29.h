#pragma once
#include "oLevel.h"
class Level_29 : public oLevel
{
public:

	Level_29(void)
	{
		percent_need = 97;
		music = &sound->Theme[3];
		count_key_max = 250;
		vec_BG.push_back(make_shared<BackGround_L5>(BackGround_L5()));
		CreateBonusBar(10,15,150,25);
		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);
		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Locomotive 2\"", font_modeka);
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(50,20), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( -50, 20), v2f(10, 10), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f(0,20), v2f(10,10), "Epic")));
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
				if(timer_key_spawn > 800/modifier_speed)
				{
					CreateEpicKey(v2f(-50,20), v2f(7,7), v2f(0.013,0));
					timer_key_spawn = 0;
					KeyGenWhiteBlack(12,12);
				}
			}
			break;
		}
	}

	virtual void Draw()
	{
			oLevel::Draw();
			if(state == welcome) 
				wnd->draw(text_welcome);
	}

	virtual ~Level_29(void)
	{
	}
};