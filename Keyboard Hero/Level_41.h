#pragma once
#include "oLevel.h"

class Level_41 : public oLevel
{
private:

	float alpha;

public:

	Level_41(void) : alpha(0)
	{
		percent_need = 98;
		music = &sound->Theme[0];
		count_key_max = 260;

		vec_BG.push_back(make_shared<BackGround_L1>(BackGround_L1()));

		CreateBonusBar(40,52,52,65);

		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"There - Here 2\"", font_modeka);

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-50,20), v2f(12,12), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-50,40), v2f(12,12), "Crematory")));

		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(50,20), v2f(10,10), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(50,40), v2f(10,10), "Creator", true)));

		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f((((25*scr_1) * cos(alpha/modifier_speed)) - (scr_1*-10))/scr_1,20), v2f(12,12), "Frost")));
		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f((((25*scr_1) * cos(alpha/modifier_speed)) - (scr_1*-10))/scr_1,40), v2f(12,12), "Fire")));
		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f((((25*scr_1) * cos(alpha/modifier_speed)) - (scr_1*10))/scr_1,20), v2f(12,12), "Nature1")));
		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f((((25*scr_1) * cos(alpha/modifier_speed)) - (scr_1*10))/scr_1,40), v2f(12,12), "Epic1")));
	}
	
	virtual void Update()
	{
		oLevel::Update();
		switch(state)
		{
		case STATE::welcome: Welcome(); break;

		case STATE::play:

			vec_Portal[4]->setPosition(v2f(((25*scr_1) * cos(alpha/modifier_speed)) - (scr_1*-10),vec_Portal[4]->getPosition().y));
			vec_Portal[5]->setPosition(v2f(((25*scr_1) * cos(alpha/modifier_speed)) - (scr_1*-10),vec_Portal[5]->getPosition().y));
			vec_Portal[6]->setPosition(v2f(((25*scr_1) * cos(alpha/modifier_speed)) - (scr_1*10),vec_Portal[6]->getPosition().y));
			vec_Portal[7]->setPosition(v2f(((25*scr_1) * cos(alpha/modifier_speed)) - (scr_1*10),vec_Portal[7]->getPosition().y));
			
			if(count_key < count_key_max)
			{
				alpha += 0.0003*time;
				timer_key_spawn += time;
				if(timer_key_spawn > 1000/modifier_speed)
				{
					key_type = rand()%2;
					uint type = rand()%2;
					if(type == 0)
					{
						if(key_type == 0) CreateEpicKey(v2f(50,40), v2f(7,7), v2f(-0.012,0));
						else CreateFireKey(v2f(50,40), v2f(7,7), v2f(-0.012,0));
					}
					if(type == 1)
					{
						if(key_type == 0) CreateFrosKey(v2f(50,20), v2f(7,7), v2f(-0.012,0));
						else CreateLifeKey(v2f(50,20), v2f(7,7), v2f(-0.012,0));
					}

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

	virtual ~Level_41(void)
	{
	}
};