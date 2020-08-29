#pragma once
#include "oLevel.h"

class Level_8 : public oLevel
{
public:

	Level_8(void)
	{
		percent_need = 95;
		music = &sound->Theme[2];
		count_key_max = 110;

		vec_BG.push_back(make_shared<BackGround_L8>(BackGround_L8()));

		CreateBonusBar(11,16,16,21);

		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Lotus\"", font_modeka);

		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(0,30), v2f(10,10), "Creator", true)));

		float _a = 0;
		for(int i = 0; i < 8; i++) 
		{
			_a = i * 45 * PI / 180;
			vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(
				v2f(cosf(_a)*30.f, sinf(_a)*30+30),
				v2f(12,12), "Crematory")));
		}

		_a = 0;
		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(cosf(_a)*17.5, sinf(_a)*17.5+30), v2f(12,12), "Fire1"))); _a=45*PI/180;
		vec_Portal.push_back(make_shared<PortalTornadoFrost>(PortalTornadoFrost(v2f(cosf(_a)*17.5, sinf(_a)*17.5+30), v2f(12,12), "Frost1"))); _a=90*PI/180;
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(cosf(_a)*17.5, sinf(_a)*17.5+30), v2f(12,12), "Epic1"))); _a=135*PI/180;
		vec_Portal.push_back(make_shared<PortalTornadoNature>(PortalTornadoNature(v2f(cosf(_a)*17.5, sinf(_a)*17.5+30), v2f(12,12), "Nature1"))); _a=180*PI/180;
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(cosf(_a)*17.5, sinf(_a)*17.5+30), v2f(12,12), "Fire2"))); _a=225*PI/180;
		vec_Portal.push_back(make_shared<PortalTornadoNature>(PortalTornadoNature(v2f(cosf(_a)*17.5, sinf(_a)*17.5+30), v2f(12,12), "Frost2"))); _a=270*PI/180;
		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(cosf(_a)*17.5, sinf(_a)*17.5+30), v2f(12,12), "Epic2"))); _a=315*PI/180;
		vec_Portal.push_back(make_shared<PortalTornadoFrost>(PortalTornadoFrost(v2f(cosf(_a)*17.5, sinf(_a)*17.5+30), v2f(12,12), "Nature2")));
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
					if(timer_key_spawn > 1950/modifier_speed)
					{
						if(key_type < 8)
						{
							const float _a = key_type * 45 * PI / 180;
							v2f siz(7,7), spd = v2f(cosf(_a), sinf(_a))*0.0075f;

							if(key_type == 0) CreateFireKey(v2f(0,30), siz, spd);
							if(key_type == 6) CreateFireKey(v2f(0,30), siz, spd);
							if(key_type == 1) CreateFrosKey(v2f(0,30), siz, spd);
							if(key_type == 7) CreateFrosKey(v2f(0,30), siz, spd);
							if(key_type == 2) CreateEpicKey(v2f(0,30), siz, spd);
							if(key_type == 4) CreateEpicKey(v2f(0,30), siz, spd);
							if(key_type == 3) CreateLifeKey(v2f(0,30), siz, spd);
							if(key_type == 5) CreateLifeKey(v2f(0,30), siz, spd);

							key_type++;
							if(key_type >= 8) key_type = 0;
						}
						timer_key_spawn = 0;
						// Активируем босса, и ждём пока все символы будут поглощены
						KeyGenWhiteBlack(5, 7);
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

	virtual ~Level_8(void)
	{
	}
};