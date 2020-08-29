#pragma once
#include "oLevel.h"

class Level_33 : public oLevel
{
private:

	v2f pos;

public:

	Level_33(void)
	{
		percent_need = 97;
		music = &sound->Theme[2];
		count_key_max = 216;

		vec_BG.push_back(make_shared<BackGround_L1>(BackGround_L1()));

		CreateBonusBar(32,42,38,35);

		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Miracle Paw 2\"", font_modeka);

		float _a = 0;
		for(int i = 0; i < 4; i++) 
		{
			_a = 135+(i * 30 * PI / 180);
			vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(
				v2f(cosf(_a)*30.f, sinf(_a)*30+30),
				v2f(10,10), "Crematory")));
		}
		vec_PortalMulti.push_back(make_shared<PortalMulticolor>(PortalMulticolor(v2f(0,30), v2f(40,40), "Fire", "Fire"))); 
		_a = 45 * PI / 180; pos = v2f(cosf(_a)*40.f, sinf(_a)*40+30);
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(pos, v2f(10,10), "Creator", false)));
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
		switch(state)
		{
		case STATE::welcome: Welcome(); break;

		case STATE::play:
			
			if(count_key < count_key_max)
			{
				timer_key_spawn += time;
				if(timer_key_spawn > 2900/modifier_speed)
				{
					v2f siz(7,7);
					float _a = atan2f(vec_Portal[key_type]->getPosition().y - vec_Portal[4]->getPosition().y, vec_Portal[key_type]->getPosition().x - vec_Portal[4]->getPosition().x);
					v2f spd(cosf(_a)*0.012f, sinf(_a)*0.012f);
					if(count_key < count_key_max) { CreateFireKey(pos, siz, spd); KeyGenWhiteBlack(12, 10); key_type++;} 
					_a = atan2f(vec_Portal[key_type]->getPosition().y - vec_Portal[4]->getPosition().y, vec_Portal[key_type]->getPosition().x - vec_Portal[4]->getPosition().x);
					spd = v2f(cosf(_a)*0.012f, sinf(_a)*0.012f);
					if(count_key < count_key_max) { CreateFrosKey(pos, siz, spd); KeyGenWhiteBlack(12, 10); key_type++;}
					_a = atan2f(vec_Portal[key_type]->getPosition().y - vec_Portal[4]->getPosition().y, vec_Portal[key_type]->getPosition().x - vec_Portal[4]->getPosition().x);
					spd = v2f(cosf(_a)*0.012f, sinf(_a)*0.012f);
					if(count_key < count_key_max) { CreateEpicKey(pos, siz, spd); KeyGenWhiteBlack(12, 10); key_type++;}
					_a = atan2f(vec_Portal[key_type]->getPosition().y - vec_Portal[4]->getPosition().y, vec_Portal[key_type]->getPosition().x - vec_Portal[4]->getPosition().x);
					spd = v2f(cosf(_a)*0.012f, sinf(_a)*0.012f);
					if(count_key < count_key_max) { CreateLifeKey(pos, siz, spd); KeyGenWhiteBlack(7, 8); key_type++;}
					key_type = 0;
					timer_key_spawn = 0;
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

	virtual ~Level_33(void)
	{
	}
};