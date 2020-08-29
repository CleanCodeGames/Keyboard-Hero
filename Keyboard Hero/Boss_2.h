#pragma once
#include "oBoss.h"

// Пираты

class Boss_2 : public oBoss
{
private:

	Shape circle;
	Shape shpBoss;
	Shape shpEffect[2];
	vector<shared_ptr<Spider>> vec_Spider;

	float alpha;
	float timer_create_spider, coldown_attack;
	float timer_bang;
	int count_spider;
	
public:

	Boss_2(uint hp, float coldown_attack) : oBoss(hp), 
		timer_create_spider(5500), 
		coldown_attack(coldown_attack),
		alpha(0),
		timer_bang(0)
	{
		count_spider = 0;
		ConstructShape(shpWheel, v2f(-80,10), v2f(10,10), texture->Wheel, true);
		ConstructShape(shpTurret, v2f(-80,10), v2f(10, 4), texture->Turret, true);
		shpTurret.setOrigin(shpTurret.getSize().x/3.5f, shpTurret.getSize().y/2.f);
		
		ConstructShape(circle, v2f(-50, 10), v2f(70,70), texture->RingWhite, sf::Color(122,255,122,0), true);

		ConstructShape(shpBoss, v2f(70,10), v2f(42,30), texture->Boss2, true);
		ConstructShape(shpName, v2f(0, -41), v2f(30, 4), texture->PirateStation, sf::Color::Transparent, true);

		ConstructShape(shpEffect[0], v2f(shpBoss.getPosition().x, shpBoss.getPosition().y)/scr_1, v2f(15,15), texture->EffectInBoss1, true);
		shpEffect[1] = shpEffect[0];
		shpEffect[1].setTextureRect(sf::IntRect(256,0,-256,256));
	}

	virtual void RenameKey()
	{
		for(auto spider: vec_Spider)
			spider->Key()->setKeyNum(getRandKeyNum());
	}

	virtual void RenameKeyWhite()
	{
		for(auto spider: vec_Spider)
			if(spider->Key()->getType() == "White")
				spider->Key()->setKeyNum(getRandKeyNum());
	}

	virtual inline void Transparent()
	{
		if(shpShadow.getFillColor().a > 1)
		{
			float a = shpShadow.getFillColor().a - (0.1*time);
			shpHpBar.setFillColor(sf::Color(255,0,0,a));
			shpName.setFillColor(sf::Color(255,255,255,a));
			shpHpIndicator.setFillColor(sf::Color(255,0,0,a));
			shpShadow.setFillColor(sf::Color(255,255,255,a));
			shpTurret.setFillColor(sf::Color(255,255,255,a));
			shpWheel.setFillColor(sf::Color(255,255,255,a));
			circle.setFillColor(sf::Color(255,255,255,a));
		}
	}

	virtual void Update()
	{
		oBoss::Update();
		circle.rotate(0.1*time);
		switch(state)
		{
		case STATE::create:
			
			if(shpBoss.getPosition().x > scr_1 * 40)
			{
				shpBoss.move(v2f(-0.005 * scr_1, 0) * time);
			}
			else 
			{
				shpBoss.setPosition(v2f(scr_1 * 40, scr_1 * 10));
				state = life;
			}
			
			if(shpWheel.getPosition().x < -scr_1 * 50)
			{
				shpWheel.move(v2f(0.0065 * scr_1, 0) * time);
				shpTurret.setPosition(shpWheel.getPosition());
			}
			else
			{
				shpWheel.setPosition(v2f(-scr_1 * 50, scr_1 * 10));
				shpTurret.setPosition(shpWheel.getPosition());
			}

			break;

		case STATE::win:

			vec_Spider.clear();
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
			shpBoss.setPosition(scr_1 * 35, scr_1 * 10 + (scr_1 * 3 * sin(alpha)));
			circle.setFillColor(sf::Color(122,255,122, 100*(timer_shadow/6000)));
			timer_create_spider > 0 ? timer_create_spider -= time : timer_create_spider = 0;
			alpha+=0.0005*time;

			if(timer_create_spider <= 0)
			{
				if(count_spider < HP_MAX)
				{
					count_spider++;
					vec_Spider.push_back(make_shared<Spider>(Spider(shpBoss.getPosition(), 0.025f*scr_1)));
					timer_create_spider = coldown_attack/modifier_speed;
				}
			}
		}
			break;

		case STATE::dead:

				timer_bang += time;
				shpBoss.rotate(-0.005*time);
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

				shpBoss.move(v2f(-0.0035, 0.006)*scr_1*time);

				if(shpBoss.getPosition().y > (scr_1*50)+shpBoss.getSize().y/2.f)
				{
					cam.setCenter(0,0);
					wnd->setView(cam);
					is_Dead = true;
				}

			break;
		}

		for(auto it = vec_Spider.begin(); it != vec_Spider.end();)
		{
			auto& spider = *(*it);
			if(!spider.isEnd())
			{
				spider.Update();
				if(!spider.isKill())
				{
					if(getDist(spider.Key()->getPosition(), shpWheel.getPosition()) < scr_1*35)
					{
						spider.Key()->setStateAllow();
						if(getDist(spider.Key()->getPosition(), shpWheel.getPosition()) < scr_1*10) 
						{
							state = win;
							sound->SpiderBang.play();
							vec_Bangs.push_back(make_shared<Bangs>(Bangs(spider.Key()->getPosition(), v2f(20,20))));
							vec_Bangs.push_back(make_shared<Bangs>(Bangs(shpWheel.getPosition(), v2f(20,20))));
						}
					}
				}
				else 
				{
					if(spider.isKill())
					{
						if(getDist(spider.Key()->getPosition(), shpBoss.getPosition()) < scr_1*15)
						{
							sound->SpiderBang.play();
							spider.End();
						}
					}
				}
				it++;
			}
			else
			{
				AddDamage();
				if(hp <= 0)
				{
					sound->BossDead2.play();
					state = dead; 
				}
				vec_FloatCost.push_back(make_shared<FloatCost>(FloatCost(spider.Key()->getPosition(), 100*modifier_speed)));
				m_player->addScore(100*modifier_speed);
				boss_score+=100*modifier_speed;
				vec_Bangs.push_back(make_shared<Bangs>(Bangs(spider.Key()->getPosition(), v2f(15,15))));
				it = vec_Spider.erase(it);
			}
		}
				

		if(state != dead) 
		{
			shpBoss.setRotation(atan2f(
				shpWheel.getPosition().y - shpBoss.getPosition().y,
				shpWheel.getPosition().x - shpBoss.getPosition().x) * 180.f / PI);
		}

		for(int i = 0; i < 2; i++)
			shpEffect[i].setPosition(NormalizePosition(shpBoss.getPosition(), -12.5, shpBoss.getRotation()));

		shpEffect[0].rotate( 0.15*time); 
		shpEffect[1].rotate(-0.15*time);

		for(auto it = vec_Laser_Player.begin(); it != vec_Laser_Player.end();) 
		{
			auto& laser = *(*it);
			if(!laser.isEnd())
			{
				laser.Update();
				it++;
			}
			else it = vec_Laser_Player.erase(it);
		}
	}

	virtual void Action()
	{
		if(state == life)
		{
			if ((language == EN && event.key.code >= 0 && event.key.code < 26)
				|| (language == RU && ((event.key.code >= 0 && event.key.code < 26) || (event.key.code >= 46 && event.key.code <= 51))))
			{
				for(auto spider: vec_Spider)
				{
					if(spider->Key()->getKeyNum() == event.key.code)
					{
						if(spider->Key()->isAllow() && !spider->isKill())
						{
							shpTurret.setRotation(atan2f(spider->Key()->getPosition().y - shpWheel.getPosition().y,spider->Key()->getPosition().x - shpWheel.getPosition().x) * 180.f / PI);
							spider->Kill(atan2f(shpBoss.getPosition().y - spider->Key()->getPosition().y, shpBoss.getPosition().x - spider->Key()->getPosition().x));
							sound->LaserSmall.play();
							vec_Laser_Player.push_back(make_shared<Laser>(Laser(shpWheel.getPosition(), spider->Key()->getPosition(), 2.5, 12, 750, sf::Color::Green)));
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
		wnd->draw(circle);
		if(state != win)
			for(auto spider: vec_Spider) spider->Draw();
		wnd->draw(shpBoss);
		for(int i = 0; i < 2; i++) wnd->draw(shpEffect[i]);
		for(auto bang: vec_Bangs) bang->Draw();
		for(auto cost: vec_FloatCost) cost->Draw();
		for(auto laser: vec_Laser_Player) laser->Draw();
		wnd->draw(shpWheel);
		for(auto bang: vec_Bangs) bang->Draw();		
		wnd->draw(shpTurret);
		for(auto laser: vec_Laser_Boss) laser->Draw();
	}

	virtual ~Boss_2(void){}
};