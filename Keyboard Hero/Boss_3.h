#pragma once
#include "oBoss.h"

class Boss_3 : public oBoss
{
private:

	float alpha;
	vector<shared_ptr<Locust>> vec_Locust;
	vector<shared_ptr<oKeyMove>> vec_Bullet;

public: 

	Boss_3(uint hp, uint line) : oBoss(hp), alpha(1.0f)
	{
		ConstructShape(shpWheel, v2f(0,65), v2f(10,10), texture->Wheel, true);
		ConstructShape(shpTurret, v2f(0,65), v2f(10, 4), texture->Turret, true);
		shpTurret.setOrigin(shpTurret.getSize().x/3.5f, shpTurret.getSize().y/2.f);
		shpTurret.setRotation(270);
		ConstructShape(shpName, v2f(0, -43), v2f(25, 3.5f), texture->LocustLogo, sf::Color::Transparent, true);
		shpHpIndicator = shpHpBar = Shape();
		
		for(int i = 0; i < 16; i++)
			for(int j = 0; j < line; j++)
			{
				vec_Locust.push_back(make_shared<Locust>(Locust(v2f((i*6)-45,(j*6)-75), v2f(4.15,4.15), v2f(0,0.00002f))));
			}
	}

	virtual void RenameKey(){}
	virtual void RenameKeyWhite(){}

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
		}
	}

	virtual void Update()
	{
		oBoss::Update();

		switch(state)
		{
		case STATE::create:
			
			for(auto locust: vec_Locust) 
			{
				locust->Move(v2f(0,0.01f));
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
				state = life;
			}

			break;

		case STATE::life:
		{
			alpha += 0.0003*time;
			for(auto it = vec_Bullet.begin(); it != vec_Bullet.end();)
			{
				auto& bullet = *(*it);
				if(getVisible().contains(bullet.getPosition()))
				{
					bullet.Update();
					bullet.Move("");
					it++;
				}
				else it = vec_Bullet.erase(it);
			}

			for(auto cost: vec_FloatCost) cost->Update();

			hp = 0;
			for(auto it1 = vec_Locust.begin(); it1 != vec_Locust.end();)
			{
				hp++;
				auto& locust = *(*it1);
				if(!locust.isKill())
				{
					locust.Update(alpha);

					if(getDist(locust.getPosition(), shpWheel.getPosition()) < shpWheel.getSize().x)
					{
						vec_Bangs.push_back(make_shared<Bangs>(Bangs(shpWheel.getPosition(), v2f(15,15))));
						vec_Bangs.push_back(make_shared<Bangs>(Bangs(locust.getPosition(), v2f(8,8))));
						sound->SpiderBang.play();
						state = win;
					}

					for(auto it2 = vec_Bullet.begin(); it2 != vec_Bullet.end();)
					{
						auto& bullet = *(*it2);

						if(getDist(locust.getPosition(), bullet.getPosition()) < bullet.getSize()) // Если пуля врезалась в саранчу
						{
							if(bullet.getKeyNum() == locust.getKeyNum()) // Если символы одинаковые
							{
								vec_FloatCost.push_back(make_shared<FloatCost>(FloatCost(locust.getPosition(), 150*modifier_speed)));
								vec_Bangs.push_back(make_shared<Bangs>(Bangs(bullet.getPosition(), v2f(8,8))));
								vec_Bangs.push_back(make_shared<Bangs>(Bangs(locust.getPosition(), v2f(8,8))));
								sound->SpiderBang.play();
								m_player->addScore(150);
								boss_score+=150;
								it2 = vec_Bullet.erase(it2);
								locust.setStateKill();
							}
							else	// Если символы разные
							{
								it2 = vec_Bullet.erase(it2);
							}
						}
						else it2++;
					}
					it1++;
				}
				else
				{
					it1 = vec_Locust.erase(it1);
				}
			}
			if(hp == 0) state = dead;
		}
			break;

		case STATE::dead:

			is_Dead = true;

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
		}
	}

	virtual void Action()
	{
		if(state == life)
		{
			if ((language == EN && event.key.code >= 0 && event.key.code < 26)
				|| (language == RU && ((event.key.code >= 0 && event.key.code < 26) || (event.key.code >= 46 && event.key.code <= 51))))
			{
				if(vec_Bullet.empty())
				{
					vec_Bullet.push_back(make_shared<KeyWhite>(KeyWhite(event.key.code, v2f(shpWheel.getPosition().x, shpWheel.getPosition().y + (scr_1*20))/scr_1, v2f(4,4), v2f(0,-0.085), "")));
					vec_Bullet.back()->setKeyInBoss();
					sound->LaserSmall.play();
				}
			}
		}
	}

	virtual void Draw()
	{
		oBoss::Draw();
		for(auto bullet: vec_Bullet) bullet->Draw();
		wnd->draw(shpWheel);
		wnd->draw(shpTurret);
		for(auto locust: vec_Locust) locust->Draw();
		for(auto bangs: vec_Bangs) bangs->Draw();
		for(auto cost: vec_FloatCost) cost->Draw();
	}

	~Boss_3(void) { }
};