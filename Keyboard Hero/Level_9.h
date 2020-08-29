#pragma once
#include "oLevel.h"
class Level_9 : public oLevel
{
public:

	Level_9(void)
	{
		percent_need = 95;
		music = &sound->Theme[3];
		count_key_max = 115;
		vec_BG.push_back(make_shared<BackGround_L1>(BackGround_L1()));
		CreateBonusBar(7,9,9,80);
		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);
		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Locomotive\"", font_modeka);
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(50,20), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( -50, 20), v2f(12, 12), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalTornadoNature>(PortalTornadoNature(v2f(0,20), v2f(12,12), "Nature1")));
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
				if(timer_key_spawn > 1900/modifier_speed)
				{
					CreateLifeKey(v2f(-50,20), v2f(7,7), v2f(0.009,0));
					timer_key_spawn = 0;
					KeyGenWhiteBlack(6,8);
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

	virtual ~Level_9(void)
	{
	}
};