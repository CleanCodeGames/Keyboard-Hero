#pragma once
#include "oKeyMove.h"
#include "Laser.h"
#include "Bangs.h"
#include "FloatCost.h"
#include "Player.h"
#include "Locust.h"
#include "Spider.h"

class oBoss : public System
{
protected:

	int hp;
	uint HP_MAX;
	uint boss_score;
	enum STATE { create, life, win, dead } state;
	vector<shared_ptr<Laser>> vec_Laser_Player, vec_Laser_Boss;
	vector<shared_ptr<Bangs>> vec_Bangs;
	vector<shared_ptr<FloatCost>> vec_FloatCost;

	uint gold_count;
	bool is_Dead;
	bool is_Win;
	float timer_shadow;
	float timer_failed;
	float timer_cam_shake;
	Shape shpShadow;
	Shape shpHpBar, shpHpIndicator, shpName;
	Shape shpWheel, shpTurret;
	static Player* m_player;

	virtual inline void AddDamage()
	{
		hp--;
		shpHpIndicator.setSize(v2f(float(hp)/float(HP_MAX)*(scr_1*30), 3*scr_1));
		shpHpIndicator.setTextureRect(sf::IntRect(0,0,int(float(hp)/float(HP_MAX)*256.f),36));
	}

	virtual inline void Heal()
	{
		hp++;
		if(hp > HP_MAX) 
			HP_MAX = hp;
	}

	virtual inline void Transparent() = 0;

public:

	static void setPlayer(Player &player)
	{
		m_player = &player;
	}

	oBoss(uint hp) : 
		hp(hp), HP_MAX(hp), 
		state(create), 
		is_Dead(false), 
		is_Win(false), 
		timer_shadow(0),
		boss_score(0),
		timer_failed(0),
		timer_cam_shake(0), 
		gold_count(0)
	{
		ConstructShape(shpHpBar, v2f(0,-37), v2f(30,3), texture->BonusIndBar, sf::Color::Transparent, true);
		ConstructShape(shpHpIndicator, v2f(0,-37), v2f(30,3), texture->BonusIndFire, sf::Color(255,0,0,0), true);
		ConstructShape(shpShadow, v2f(0,0), v2f(100/scr_1*scr_1w, 100), texture->Shadow, sf::Color(255,255,255,0), true);
	}

	virtual uint getScore() const
	{
		return boss_score;
	}

	virtual bool isWin() const { return is_Win; }
	virtual bool isDead() const { return is_Dead; }
	virtual void RenameKey() = 0;
	virtual void RenameKeyWhite() = 0;

	virtual void Update()
	{
		for(auto it = vec_Bangs.begin(); it != vec_Bangs.end();)
		{
			auto& bang = *(*it);
			if(bang.isEnd()) it = vec_Bangs.erase(it);
			else
			{
				bang.Update();
				it++;
			}
			
		}

		for(auto it = vec_FloatCost.begin(); it != vec_FloatCost.end();)
		{
			auto& cost = *(*it);
			if(cost.isKill()) it = vec_FloatCost.erase(it);
			else
			{
				cost.Update();
				it++;
			}
		}

		switch(state)
		{
		case STATE::life:
			{
				if(timer_shadow < 6000) timer_shadow += time;
				if(timer_shadow > 6000) timer_shadow = 6000;
				const float rate = 255*(timer_shadow/6000);
				shpShadow.setFillColor(sf::Color(255,255,255, rate));
				shpHpBar.setFillColor(sf::Color(255,255,255, rate));
				shpHpIndicator.setFillColor(sf::Color(255,0,0, rate));
				shpName.setFillColor(sf::Color(255,255,255, rate));
			}
			break;

		case STATE::dead:

			CamShake();
			Transparent();

			break;
		case STATE::win:

			CamShake();
			timer_failed += time;
			Transparent();

			break;
		}
	}

	virtual inline void CamShake()
	{
		timer_cam_shake += time;
		if(timer_cam_shake > 50)
		{
			cam.setCenter(rand()%int(scr_1)-rand()%int(scr_1/2), rand()%int(scr_1)-rand()%int(scr_1/2));
			wnd->setView(cam);
			timer_cam_shake = 0;
		}
	}

	virtual void Action() = 0;

	virtual void Draw()
	{
		wnd->draw(shpShadow);
		wnd->draw(shpName);
		wnd->draw(shpHpIndicator);
		wnd->draw(shpHpBar);
	}

	virtual ~oBoss(void)
	{
	}
};