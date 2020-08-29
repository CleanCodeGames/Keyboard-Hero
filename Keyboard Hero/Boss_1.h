#pragma once
#include "oBoss.h"

// Кругрый босс

class Boss_1 : public oBoss
{
private:

	Shape shpBoss;
	Shape shpEffect[2];
	vector<shared_ptr<oKeyMove>> vec_Key;

	float alpha;
	float timer_allow, coldown_attack;
	bool check;
	float timer_bang;
	
public:

	Boss_1(uint hp, float coldown_attack) : oBoss(hp), 
		timer_allow(5000), 
		coldown_attack(coldown_attack),
		alpha(0), check(true), 
		timer_bang(0)
	{
		ConstructShape(shpWheel, v2f(0, 75), v2f(10,10), texture->Wheel, true);
		ConstructShape(shpTurret, v2f(0,75), v2f(10, 4), texture->Turret, true);
		shpTurret.setOrigin(shpTurret.getSize().x/3.5f, shpTurret.getSize().y/2.f);

		ConstructShape(shpBoss, v2f(15,-70), v2f(35,35), texture->Boss1, true);
		ConstructShape(shpName, v2f(0, -40), v2f(25, 4), texture->Destroyer, sf::Color::Transparent, true);
		ConstructShape(shpEffect[0], v2f(shpBoss.getPosition().x, shpBoss.getPosition().y)/scr_1, v2f(15,15), texture->EffectInBoss1, true);
		shpEffect[1] = shpEffect[0];
		shpEffect[1].setTextureRect(sf::IntRect(256,0,-256,256));
		vec_Key.push_back(make_shared<KeyFrost>(KeyFrost(getRandKeyNum(), shpBoss.getPosition(), v2f(5, 5), v2f(0, 0), "Frost")));
		vec_Key.push_back(make_shared<KeyFire>(KeyFire(getRandKeyNum(), shpBoss.getPosition(), v2f(5, 5), v2f(0, 0), "Fire")));
		vec_Key.push_back(make_shared<KeyFire>(KeyFire(getRandKeyNum(), shpBoss.getPosition(), v2f(5, 5), v2f(0, 0), "Fire1")));
		vec_Key.push_back(make_shared<KeyEpic>(KeyEpic(getRandKeyNum(), shpBoss.getPosition(), v2f(5, 5), v2f(0, 0), "Epic")));
		vec_Key.push_back(make_shared<KeyNature>(KeyNature(getRandKeyNum(), shpBoss.getPosition(), v2f(5, 5), v2f(0, 0), "Nature")));

		for(auto key: vec_Key) 
			key->setKeyInBoss();

		vec_Key[rand()%5]->setStateAllow();
	}

	virtual void RenameKey()
	{
		for(auto key: vec_Key)
			key->setKeyNum(getRandKeyNum());
	}

	virtual void RenameKeyWhite()
	{
		for(auto key: vec_Key)
			if(key->getType() == "White")
				key->setKeyNum(getRandKeyNum());
	}

	virtual inline void Transparent()
	{
		if(shpShadow.getFillColor().a > 1)
		{
			float a = shpShadow.getFillColor().a - (0.1*time);
			shpHpBar.setFillColor(sf::Color(255,255,255,a));
			shpName.setFillColor(sf::Color(255,255,255,a));
			shpHpIndicator.setFillColor(sf::Color(255,0,0,a));
			shpShadow.setFillColor(sf::Color(255,255,255,a));
			shpTurret.setFillColor(sf::Color(255,255,255,a));
			shpWheel.setFillColor(sf::Color(255,255,255,a));
		}
	}

	virtual void Update()
	{
		oBoss::Update();
		switch(state)
		{
		case STATE::create:
			
			if(shpBoss.getPosition().y < -scr_1 * 15)
			{
				shpBoss.move(v2f(0, 0.004 * scr_1) * time);
			}
			else 
			{
				shpBoss.setPosition(v2f(shpBoss.getPosition().x, -scr_1 * 15));
				state = life;
			}
			
			if(shpWheel.getPosition().y > scr_1 * 40)
			{
				shpWheel.move(v2f(0,-0.004 * scr_1) * time);
				shpTurret.setPosition(shpWheel.getPosition());
				
			}
			else
			{
				shpWheel.setPosition(v2f(0, scr_1 * 40));
				shpTurret.setPosition(shpWheel.getPosition());
			}

			break;

		case STATE::win:

			if(timer_failed >= 5000) 
			{
				is_Win = true;
			}
			else
			{
				// 5 секунд на поражение
			}

			break;

		case STATE::life:
		{
			shpBoss.setPosition(scr_1 * 15 * cos(alpha), scr_1 * 15 * sin(alpha));

			float rate = 255; 

			if(timer_allow < coldown_attack/modifier_speed && check) 
				rate = 255 * (timer_allow / (coldown_attack/modifier_speed));

			for(int i = 0; i < 2; i++) 
				shpEffect[i].setFillColor(sf::Color(255, rate, rate));

			timer_allow > 0 ? timer_allow-=time : timer_allow = 0;
			alpha+=0.001*time;

			if(timer_allow < 0)
			{
				check = true;
				for(auto key: vec_Key) 
				{
					if(key->isAllow())
					{
						sound->LaserBig.play();
						vec_Laser_Boss.push_back(make_shared<Laser>(Laser(shpEffect[0].getPosition(), shpWheel.getPosition(), 25, 16, 3000, sf::Color::Red)));
						key->setStateMove();
						check = false;
					}
				}

				if(check)
				{
					timer_allow = coldown_attack/modifier_speed;
					vec_Key[rand()%5]->setStateAllow();
				}
				else
				{
					state = win;
					timer_allow = 5000;
				}
			}
		}
			break;

		case STATE::dead:

				timer_bang += time;

				if(timer_bang >= 100)
				{
					v2f pos = shpBoss.getPosition() + v2f(rand()%int(shpBoss.getSize().x), rand()%int(shpBoss.getSize().y)) - shpBoss.getSize()/2.f;
					vec_Bangs.push_back(make_shared<Bangs>(Bangs(pos, v2f(16,16))));
					sound->BangSmall.play();
					if(gold_count < 20) 
					{
						vec_FloatCost.push_back(make_shared<FloatCost>(FloatCost(pos, 500*modifier_speed)));
						m_player->addScore(500*modifier_speed);
						boss_score+=500*modifier_speed;
					}

					gold_count++;
					timer_bang = 0;
				}

				shpBoss.move(v2f(0,0.006*time)*scr_1);

				if(shpBoss.getPosition().y > (scr_1*50)+shpBoss.getSize().y/2.f)
				{
					cam.setCenter(0,0);
					wnd->setView(cam);
					is_Dead = true;
				}

			break;
		}

		vec_Key[0]->setPostion(NormalizePosition(shpBoss.getPosition(),  8, shpBoss.getRotation()+180));
		vec_Key[1]->setPostion(NormalizePosition(shpBoss.getPosition(), 15, shpBoss.getRotation()-45));
		vec_Key[2]->setPostion(NormalizePosition(shpBoss.getPosition(), 15, shpBoss.getRotation()+45));
		vec_Key[3]->setPostion(NormalizePosition(shpBoss.getPosition(), 15, shpBoss.getRotation()-90));
		vec_Key[4]->setPostion(NormalizePosition(shpBoss.getPosition(), 15, shpBoss.getRotation()+90));

		if(state != dead) 
		{
			shpBoss.setRotation(atan2f(shpWheel.getPosition().y - shpBoss.getPosition().y,shpWheel.getPosition().x - shpBoss.getPosition().x) * 180.f / PI);
			shpTurret.setRotation(shpBoss.getRotation()+180);
		}

		for(int i = 0; i < 2; i++)
			shpEffect[i].setPosition(NormalizePosition(shpBoss.getPosition(), 5, shpBoss.getRotation()));

		shpEffect[0].rotate( 0.15*time); 
		shpEffect[1].rotate(-0.15*time);

		for(auto key: vec_Key) key->Update();

		for(auto it = vec_Laser_Player.begin(); it != vec_Laser_Player.end();) 
		{
			auto& laser = *(*it);
			if(!laser.isEnd())
			{
				laser.Update(shpWheel.getPosition(), shpEffect[0].getPosition());
				it++;
			}
			else it = vec_Laser_Player.erase(it);
		}

		for(auto it = vec_Laser_Boss.begin(); it != vec_Laser_Boss.end();) 
		{
			auto& laser = *(*it);
			if(!laser.isEnd())
			{
				laser.Update(shpEffect[0].getPosition(), shpWheel.getPosition());
				it++;
			}
			else it = vec_Laser_Boss.erase(it);
		}
	}

	virtual void Action()
	{
		if(state == life)
		{
			if ((language == EN && event.key.code >= 0 && event.key.code < 26)
				|| (language == RU && ((event.key.code >= 0 && event.key.code < 26) || (event.key.code >= 46 && event.key.code <= 51))))
			{
				for(auto key: vec_Key)
				{
					if(key->getKeyNum() == event.key.code)
					{
						if(key->isAllow())
						{
							AddDamage();
							if(hp <= 0)
							{
								sound->BossDead1.play();
								state = dead; 
							}
							m_player->addScore(100*modifier_speed);
							boss_score+=100*modifier_speed;
							vec_FloatCost.push_back(make_shared<FloatCost>(FloatCost(key->getPosition(), 100*modifier_speed)));
							sound->LaserSmall.play();
							vec_Laser_Player.push_back(make_shared<Laser>(Laser(shpWheel.getPosition(), shpEffect[0].getPosition(), 2.5, 12, 750, sf::Color::Green)));
							for (auto key : vec_Key) key->setKeyNum(getRandKeyNum());
							key->setStateMove();
							vec_Key[rand()%5]->setStateAllow();
							timer_allow = coldown_attack/modifier_speed;
							break;
						}
					}
				}
			}
		}
	}

	virtual void Draw()
	{
		oBoss::Draw();
		wnd->draw(shpBoss);
		for(int i = 0; i < 2; i++) wnd->draw(shpEffect[i]);
		for(auto key: vec_Key) key->Draw();
		for(auto bang: vec_Bangs) bang->Draw();
		for(auto cost: vec_FloatCost) cost->Draw();
		for(auto laser: vec_Laser_Player) laser->Draw();
		wnd->draw(shpWheel);
		wnd->draw(shpTurret);
		for(auto laser: vec_Laser_Boss) laser->Draw();
	}

	virtual ~Boss_1(void){}
};