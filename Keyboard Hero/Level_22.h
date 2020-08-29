#pragma once
#include "oLevel.h"

class Level_22 : public oLevel
{
public:

	Level_22(void)
	{
		percent_need = 96;
		music = &sound->Theme[1];
		count_key_max = 140;

		vec_BG.push_back(make_shared<BackGround_L6>(BackGround_L6()));

		CreateBonusBar(20,25,28,32);

		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);

		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"Black Hole\"", font_modeka);

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(0,30), v2f(10,10), "Crematory")));

		float _a = 0;
		bool isLeft = false;
		for(int i = 0; i < 8; i++) 
		{
			isLeft = !isLeft;
			_a = i * 45 * PI / 180;
			vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(
				v2f(cosf(_a)*30.f, sinf(_a)*30+30),
				v2f(10,10), "Creator", isLeft)));
		}

		vec_PortalMulti.push_back(make_shared<PortalMulticolor>(PortalMulticolor(v2f(0, 30), v2f(30,30), "Fire", "Fire")));
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
					if(timer_key_spawn > 1300/modifier_speed)
					{
						if(key_type < 8)
						{
							const float _a = rand()%8 * 45 * PI / 180;
							v2f siz(7,7), spd = v2f(cosf(_a), sinf(_a))*0.0095f;
							int x = rand()%4;
							if(x == 0) CreateFireKey(v2f(cosf(_a)*30.f, sinf(_a)*30+30), siz, -spd);
							if(x == 1) CreateFrosKey(v2f(cosf(_a)*30.f, sinf(_a)*30+30), siz, -spd);
							if(x == 2) CreateEpicKey(v2f(cosf(_a)*30.f, sinf(_a)*30+30), siz, -spd);
							if(x == 3) CreateLifeKey(v2f(cosf(_a)*30.f, sinf(_a)*30+30), siz, -spd);

							key_type++;
							if(key_type >= 8) key_type = 0;
						}
						timer_key_spawn = 0;
						KeyGenWhiteBlack(9, 9);
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

	virtual ~Level_22(void)
	{
	}
};