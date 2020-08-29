#pragma once
#include "Training.h"

class Level_1 : public oLevel
{
private:

	Training training;

public:

	Level_1(void)
	{
		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Hello World\"", font_modeka);
		vec_BG.push_back(make_shared<BackGround_L1>(BackGround_L1()));
		music = &sound->Theme[0];
		CreateBonusBar(5,7,7,7);
		percent_need = 90;
		count_key_max = 50;
		count_key = 0; 
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-40, 0), v2f(15,15), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f( 40, 20), v2f(15,15), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-40, 40), v2f(15,15), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f( 40, 60), v2f(15,15), "Crematory")));

		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( 40, 0), v2f(15,15), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-40, 20), v2f(15,15), "Creator", false)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f( 40, 40), v2f(15,15), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-40, 60), v2f(15,15), "Creator", false)));

		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(0, 0), v2f(15,15), "Fire")));
		vec_Portal.push_back(make_shared<PortalTornadoFrost>(PortalTornadoFrost(v2f(0,  20), v2f(15,15), "Frost")));
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(0,  40), v2f(15,15), "Epic")));
		vec_Portal.push_back(make_shared<PortalTornadoNature>(PortalTornadoNature(v2f(0, 60), v2f(15,15), "Nature")));
	}

	virtual void Action()
	{
		if(!training.isEnd()) training.Action();
		else oLevel::Action();
	}

	virtual void Update()
	{
		oLevel::Update();
		switch(state)
		{
		case STATE::welcome:
			if(!training.isEnd()) training.Update();
			else Welcome(); 
		break;

		case STATE::play:
			
			if(count_key < count_key_max)
			{
				timer_key_spawn += time;
				if(timer_key_spawn > 2650/modifier_speed)
				{
					if(key_type < 4)
					{
						v2f siz(7,7), spd(0.0055,0);
						if(key_type == 0) CreateFireKey(v2f(40,  0), siz, -spd);
						if(key_type == 1) CreateFrosKey(v2f(-40,20), siz,  spd);
						if(key_type == 2) CreateEpicKey(v2f(40, 40), siz, -spd);
						if(key_type == 3) CreateLifeKey(v2f(-40,60), siz,  spd);
						
						key_type++;
						if(key_type >= 4) key_type = 0;
					}
					timer_key_spawn = 0;
					KeyGenWhiteBlack(1,5);
				}
			}
			break;
		}
	}

	virtual void Draw()
	{
		if(!training.isEnd()) 
		{
			for(auto bg: vec_BG){ bg->Draw(); }
			training.Draw();
		}
		else
		{
			oLevel::Draw();
			if(state == welcome) 
				wnd->draw(text_welcome);
		}

	}

	virtual ~Level_1(void)
	{
	}
};