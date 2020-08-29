#include "oBoss.h"

class Boss_4 : public oBoss
{
private:

	uint counter;
	Shape shpQuad[8][4];
	float timer_Create_Gopher, coldown_gopher;
	float timer_Create_Boss;
	vector<shared_ptr<oKeyMove>> vec_Gopher;

public:

	virtual void RenameKey()
	{
		for(auto key: vec_Gopher)
			key->setKeyNum(getRandKeyNum());
	}

	virtual void RenameKeyWhite()
	{
		for(auto key: vec_Gopher)
			if(key->getType() == "White")
				key->setKeyNum(getRandKeyNum());
	}

	Boss_4(uint hp, float coldown_gopher) : oBoss(hp), timer_Create_Gopher(5000), coldown_gopher(coldown_gopher), timer_Create_Boss(0), counter(hp)
	{
		ConstructShape(shpName, v2f(0, -40), v2f(25, 4), texture->CatchGopher, sf::Color::Transparent, true);

		for(int i = 0; i < 8; i++)
		for(int j = 0; j < 4; j++)
			ConstructShape(shpQuad[i][j], v2f((i*10)-35, (j*10)-15), v2f(10,10),  texture->GopherQuad, sf::Color(255,255,255,0), true);

		int i = rand()%8;
		int j = rand()%4;
		int type = rand()%4;
		v2f pos(shpQuad[i][j].getPosition().x/scr_1, (shpQuad[i][j].getPosition().y/scr_1) + 20);
		if(type == 0) vec_Gopher.push_back(make_shared<KeyFire>(KeyFire(getRandKeyNum(), pos, v2f(8,8), v2f(), "")));
		if (type == 1) vec_Gopher.push_back(make_shared<KeyFrost>(KeyFrost(getRandKeyNum(), pos, v2f(8, 8), v2f(), "")));
		if (type == 2) vec_Gopher.push_back(make_shared<KeyEpic>(KeyEpic(getRandKeyNum(), pos, v2f(8, 8), v2f(), "")));
		if (type == 3) vec_Gopher.push_back(make_shared<KeyNature>(KeyNature(getRandKeyNum(), pos, v2f(8, 8), v2f(), "")));
	}

	virtual void Action()
	{
		if (state == life && ((language == EN && event.key.code >= 0 && event.key.code < 26)
			|| (language == RU && ((event.key.code >= 0 && event.key.code < 26) || (event.key.code >= 46 && event.key.code <= 51)))))
		{
			for(auto it = vec_Gopher.begin(); it != vec_Gopher.end();)
			{
				oKeyMove& gopher = *(*it);
				if(gopher.isAllow() && event.key.code == gopher.getKeyNum())
				{
					vec_Bangs.push_back(make_shared<Bangs>(Bangs(gopher.getPosition(), v2f(10,10))));
					AddDamage();
					m_player->addScore(125*modifier_speed);
					boss_score+=125*modifier_speed;
					vec_FloatCost.push_back(make_shared<FloatCost>(FloatCost(gopher.getPosition(), 125*modifier_speed)));
					sound->SpiderBang.play();
					it = vec_Gopher.erase(it);
					if(hp <= 0)
					{
						state = STATE::dead;
						sound->BossDead1.play();
						for(int i = 0; i < 8; i++)
						{
							for(int j = 0; j < 4; j++)
							{
								vec_Bangs.push_back(make_shared<Bangs>(Bangs(shpQuad[i][j].getPosition(), v2f(20,20))));
							}
						}
					}
				}
				else it++;
			}
		}
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

			for(int i = 0; i < 8; i++)
			{
				for(int j = 0; j < 4; j++)
				{
					shpQuad[i][j].setFillColor(sf::Color(255,255,255,a));
				}
			}
		}
	}

	virtual void Update()
	{
		oBoss::Update();
		switch(state)
		{
			case STATE::create: 

				if(timer_Create_Boss < 5000) timer_Create_Boss += time;
				if(timer_Create_Boss > 5000)
				{
					timer_Create_Boss = 5000;
					state = life;
				}
				break;

			case STATE::dead:

				vec_Gopher.clear();

				for(int i = 0; i < 8; i++)
				{
					for(int j = 0; j < 4; j++)
					{
						float size = shpQuad[i][j].getSize().x;
						shpQuad[i][j].setSize(v2f(size+(0.45*scr_1), size+(0.45*scr_1)));
						shpQuad[i][j].setOrigin(shpQuad[i][j].getSize()/2.f);
						shpQuad[i][j].rotate(0.3*time);
					}
				}

				if(shpShadow.getFillColor().a < 3)
					is_Dead = true;

				break;

			case STATE::life:   
			{
				for(auto cost: vec_FloatCost) cost->Update();
				if(timer_Create_Gopher > 0) timer_Create_Gopher -= (time*modifier_speed);
				if(timer_Create_Gopher <= 0)
				{
					if(counter > 0)
					{
						counter--;
						int i = rand()%8;
						int j = rand()%4;
						int type = rand()%4;
						v2f pos(shpQuad[i][j].getPosition().x/scr_1, (shpQuad[i][j].getPosition().y/scr_1) + 20);
						if (type == 0) vec_Gopher.push_back(make_shared<KeyFire>(KeyFire(getRandKeyNum(), pos, v2f(8, 8), v2f(), "")));
						if (type == 1) vec_Gopher.push_back(make_shared<KeyFrost>(KeyFrost(getRandKeyNum(), pos, v2f(8, 8), v2f(), "")));
						if (type == 2) vec_Gopher.push_back(make_shared<KeyEpic>(KeyEpic(getRandKeyNum(), pos, v2f(8, 8), v2f(), "")));
						if (type == 3) vec_Gopher.push_back(make_shared<KeyNature>(KeyNature(getRandKeyNum(), pos, v2f(8, 8), v2f(), "")));
						timer_Create_Gopher = coldown_gopher;
					}
				}

				for(int i = 0; i < 8; i++)
				{
					for(int j = 0; j < 4; j++)
					{
						shpQuad[i][j].setFillColor(sf::Color(255,255,255, shpShadow.getFillColor().a));
					}
				}

				int count_gopher = 0;

				for(auto gopher: vec_Gopher)
				{
					count_gopher++;
					gopher->Update();

					if(gopher->isMove())
						gopher->setStateAllow();
				}

				if(count_gopher > 5) 
				{
					state = STATE::win;
					vec_Gopher.clear();
				}
			}
				break;

			case STATE::win:

				if(timer_failed >= 5000) 
				{
					is_Win = true;
				}
				else
				{
					for(int i = 0; i < 8; i++)
					{
						for(int j = 0; j < 4; j++)
						{
							float size = shpQuad[i][j].getSize().x;
							shpQuad[i][j].setSize(v2f(size+(0.45*scr_1), size+(0.45*scr_1)));
							shpQuad[i][j].setOrigin(shpQuad[i][j].getSize()/2.f);
							shpQuad[i][j].setFillColor(sf::Color(255,255,255,255-(255*(timer_failed/5000))));
						}
					}
				}
				
				break;
		}
	}

	virtual void Draw()
	{
		oBoss::Draw();

		for(int i = 0; i < 8; i++)
			for(int j = 0; j < 4; j++)
				wnd->draw(shpQuad[i][j]);
		for(auto bang: vec_Bangs)
			bang->Draw();
		for(auto gopher: vec_Gopher) 
			gopher->Draw();
		for(auto cost: vec_FloatCost) cost->Draw();
	}

	virtual ~Boss_4()
	{

	}
};