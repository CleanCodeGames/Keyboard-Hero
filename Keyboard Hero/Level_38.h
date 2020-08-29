#pragma once
#include "oLevel.h"

class Level_38 : public oLevel
{
private:

	Shape shpUFO;
	float alpha;

public:

	Level_38(void) : alpha(0)
	{
		ConstructShape(shpUFO, v2f(42,0), v2f(8,8), texture->UFO, true);
		shpUFO.setTextureRect(sf::IntRect(0,0,64,64));
		percent_need = 98;
		music = &sound->Theme[2];
		count_key_max = 250;
		vec_BG.push_back(make_shared<BackGround_L6>(BackGround_L6()));
		CreateBonusBar(30,40,45,50);
		count_key = 0;
		count_key_capture = 0;
		m_player->setKeyCount(count_key_max);
		ConstructText(text_welcome, v2f(0,-35*scr_1), 10, sf::Color::Green, L"\"X-Files 2\"", font_modeka);
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(0,30), v2f(10,10), "Crematory")));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-30,0), v2f(10,10), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(30,0), v2f(10,10), "Creator", true)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-30,60), v2f(10,10), "Creator", false)));
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(30,60), v2f(10,10), "Creator", false)));
		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(10,20), v2f(12,12), "Fire1")));
		vec_Portal.push_back(make_shared<PortalTornadoFrost>(PortalTornadoFrost(v2f(20,10), v2f(12,12), "Frost1")));
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(10,40), v2f(12,12), "Epic1")));
		vec_Portal.push_back(make_shared<PortalTornadoNature>(PortalTornadoNature(v2f(20,50), v2f(12,12), "Nature1")));
		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(-10,20), v2f(12,12), "Nature2")));
		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f(-20,10), v2f(12,12), "Epic2")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(-10,40), v2f(12,12), "Frost2")));
		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(-20,50), v2f(12,12), "Fire2")));
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
		
		// Анимация НЛО
		static float timer;
		timer+=time;
		static uint frame = 0;

		if(timer > 50)
		{
			timer = 0;

			if(frame < 5) shpUFO.setTextureRect(sf::IntRect(frame*64,0,64,64));
			if(frame < 10 && frame >= 5) shpUFO.setTextureRect(sf::IntRect((frame-5)*64,64,64,64));
			if(frame < 15 && frame >= 10) shpUFO.setTextureRect(sf::IntRect((frame-10)*64,128,64,64));
			frame++;
			if(frame >= 15) 
				frame = 0;
		}
		// Конец анимации НЛО

			switch(state)
			{
			case STATE::welcome: Welcome(); break;

			case STATE::play:

				shpUFO.setPosition( scr_1*42 * cos(alpha), scr_1*42 * sin(alpha));
				alpha += 0.00025*time;

				if(count_key < count_key_max)
				{
					timer_key_spawn += time;
					if(timer_key_spawn > 1000/modifier_speed)
					{
						if(key_type < 4)
						{
							v2f siz(7,7);
							uint type = rand()%2;
							if(key_type == 0) {
								if(type > 0) CreateFireKey(v2f(30,0), siz, v2f(-0.0135, 0.0135));
									else CreateFrosKey(v2f(30,0), siz, v2f(-0.0135, 0.0135));
							}
							if(key_type == 1) {
								if(type > 0) CreateLifeKey(v2f(-30,0), siz, v2f(0.0135, 0.0135));
									else CreateEpicKey(v2f(-30,0), siz, v2f(0.0135, 0.0135));
							}
							if(key_type == 2) {
								if(type > 0) CreateLifeKey(v2f(30,60), siz, v2f(-0.0135, -0.0135));
									else CreateEpicKey(v2f(30,60), siz, v2f(-0.0135, -0.0135));
							}
							if(key_type == 3) {
								if(type > 0) CreateFireKey(v2f(-30,60), siz, v2f(0.0135, -0.0135));
									else CreateFrosKey(v2f(-30,60), siz, v2f(0.0135, -0.0135));
							}
							
							key_type++;
							if(key_type >= 4) key_type = 0;
						}
						timer_key_spawn = 0;
						KeyGenWhiteBlack(11,11);
					}
				}
				break;
			}
	}

	virtual void Draw()
	{
			oLevel::Draw();
			wnd->draw(shpUFO);
			if(state == welcome) 
				wnd->draw(text_welcome);
	}

	virtual ~Level_38(void)
	{
	}
};