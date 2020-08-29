#include "oBoss.h"
#include "Meteor.h"

// shape name

class Boss_5 : public oBoss
{
private:

	vector<shared_ptr<Meteor>> vec_Meteor;
	vector<shared_ptr<KeyWhite>> vec_Key;
	vector<shared_ptr<oSpecEffect>> vec_MirrorWheel;
	float timer_wave, coldown_wave;
	uint wave_counter;
	Shape shpLight;
	Shape shpWall[2];
	uint step;

	bool isDirMove, isMove;

	inline void Move()
	{
		static float timer = 0;
		timer += time;
		if(timer > 25)
		{
			timer = 0;
			if(step < 10)
			{
				step++;
				if(isDirMove)
				{
					shpWheel.move(v2f(scr_1,0));
					shpWheel.setRotation(40);
				}
				else 
				{
					shpWheel.move(v2f(-scr_1,0));
					shpWheel.setRotation(320);
				}
				vec_Key[0]->setPostion(v2f(shpWheel.getPosition().x-(6*scr_1), shpWheel.getPosition().y));
				vec_Key[1]->setPostion(v2f(shpWheel.getPosition().x+(6*scr_1), shpWheel.getPosition().y));
			}
			else
			{
				shpWheel.setRotation(0);
				step = 0;
				isMove = false;
			}
		}
	}

public:

	virtual void RenameKey()
	{
		for(auto key: vec_Key)
			key->setKeyNum(getRandKeyNum());
	}

	virtual void RenameKeyWhite(){}

	Boss_5(uint hp, float coldown_wave) : oBoss(hp), timer_wave(0), wave_counter(hp), step(0), isMove(false), isDirMove(false), coldown_wave(coldown_wave)
	{
		ConstructShape(shpWheel, v2f(5, 75), v2f(10,10), texture->UFO2, true);
		ConstructShape(shpWall[0], v2f(-50,0), v2f(50,100), texture->Border, sf::Color(100,100,100,255), true);
		shpWall[0].setOrigin(v2f(shpWall[0].getSize().x, shpWall[0].getSize().y/2));
		ConstructShape(shpWall[1], v2f( 50,0), v2f(50,100), texture->Border, sf::Color(100,100,100,255), true);
		shpWall[1].setOrigin(v2f(0, shpWall[0].getSize().y/2));
		vec_Key.push_back(make_shared<KeyWhite>(KeyWhite(getRandKeyNum(), v2f(-2.5, 75), v2f(5, 5), v2f(0, 0), "")));
		vec_Key.push_back(make_shared<KeyWhite>(KeyWhite(getRandKeyNum(), v2f(12.5, 75), v2f(5, 5), v2f(0, 0), "")));

		while(vec_Key[0]->getKeyNum() == vec_Key[1]->getKeyNum())
			vec_Key[0]->setKeyNum(getRandKeyNum());

		for(auto key: vec_Key) key->setKeyInBoss();

		ConstructShape(shpName, v2f(0, -40), v2f(25, 4), texture->RockFall, sf::Color::Transparent, true);
		ConstructShape(shpLight, v2f(-300,0), v2f(8,100), texture->Light, true);
	}

	virtual void Action()
	{
		if(event.type == sf::Event::KeyPressed)
		{
			if (state == life && ((language == EN && event.key.code >= 0 && event.key.code < 26)
				|| (language == RU && ((event.key.code >= 0 && event.key.code < 26) || (event.key.code >= 46 && event.key.code <= 51)))))
			{
				if(!isMove && vec_Key[0]->getKeyNum() == event.key.code && shpWheel.getPosition().x > -scr_1*36)
				{
					vec_Key[0]->setKeyNum(getRandKeyNum());
					vec_Key[1]->setKeyNum(getRandKeyNum());
					isMove = true;
					isDirMove = false;
					while(vec_Key[0]->getKeyNum() == vec_Key[1]->getKeyNum() || event.key.code == vec_Key[0]->getKeyNum())
						vec_Key[0]->setKeyNum(getRandKeyNum());
				}

				if(!isMove && vec_Key[1]->getKeyNum() == event.key.code && shpWheel.getPosition().x < scr_1*36)
				{
					vec_Key[0]->setKeyNum(getRandKeyNum());
					vec_Key[1]->setKeyNum(getRandKeyNum());
					isMove = true;
					isDirMove = true;
					while(vec_Key[0]->getKeyNum() == vec_Key[1]->getKeyNum() || event.key.code == vec_Key[1]->getKeyNum())
						vec_Key[1]->setKeyNum(getRandKeyNum());
				}
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
			shpWheel.setFillColor(sf::Color(255,255,255,a));
			for(int i = 0; i < 2; i++) 
				vec_Key[i]->setFillColor(sf::Color(255,255,255,a));
		}
	}

	virtual void Update()
	{
		oBoss::Update();
		switch(state)
		{
			case STATE::create: 

				if(shpWheel.getPosition().y > scr_1 * 45)
				{
					shpWheel.move(v2f(0,-0.006 * scr_1) * time);
					vec_Key[0]->setPostion(v2f(shpWheel.getPosition().x-(6*scr_1), shpWheel.getPosition().y));
					vec_Key[1]->setPostion(v2f(shpWheel.getPosition().x+(6*scr_1), shpWheel.getPosition().y));
				}
				else
				{
					shpWheel.setPosition(v2f(5 * scr_1, scr_1 * 45));
					state = life;
					vec_Key[0]->setPostion(v2f(shpWheel.getPosition().x-(6*scr_1), shpWheel.getPosition().y));
					vec_Key[1]->setPostion(v2f(shpWheel.getPosition().x+(6*scr_1), shpWheel.getPosition().y));
				}

				break;

			case STATE::dead:

				if(shpShadow.getFillColor().a < 3) is_Dead = true;

				break;

			case STATE::life:   
			{
				timer_wave += time;

				if(isMove) Move();

				if(timer_wave >= coldown_wave)
				{
					if(wave_counter != 0 && vec_Meteor.empty())
					{
						wave_counter--;
						int tunnel = rand()%10;
						for(int i = 0; i < 10; i++)
						{
							if(i != tunnel) 
							{
								vec_Meteor.push_back(make_shared<Meteor>(Meteor(v2f(9, 9), v2f( ( i * 10 ) - 45, -350), 0.065f)));
							}
							else shpLight.setPosition(v2f( ( i * 10 ) - 45, 0 )*scr_1);
						}
						timer_wave = 0;
					}
				}

				bool isDamage = false;

				for(auto it = vec_Meteor.begin(); it != vec_Meteor.end();)
				{
					Meteor&meteor = *(*it);
					if(!meteor.isDead())
					{
						meteor.Update();
						if(getDist(shpWheel.getPosition(), meteor.getPosition()) < shpWheel.getSize().x*0.7f)
						{
							state = win;
							vec_Bangs.push_back(make_shared<Bangs>(Bangs(shpWheel.getPosition(), v2f(25,25))));
						}
						it++;
					}
					else
					{
						isDamage = true;
						it = vec_Meteor.erase(it);
					}
				}

				if(hp <= 0) state = dead;
				if(isDamage) 
				{
					m_player->addScore(1000);
					boss_score+=1000;
					vec_FloatCost.push_back(make_shared<FloatCost>(FloatCost(shpWheel.getPosition(), 1000)));
					AddDamage();
				}

				break;
			}
			case STATE::win:

				if(timer_failed >= 5000) 
				{
					is_Win = true;
				}
				else
				{
					
				}
				
				break;
		}
	}

	virtual void Draw()
	{
		wnd->draw(shpShadow);
		wnd->draw(shpLight);
		for(int i = 0; i < 2; i++) wnd->draw(shpWall[i]);
		wnd->draw(shpName);
		wnd->draw(shpHpIndicator);
		wnd->draw(shpHpBar);
		for(auto bang: vec_Bangs) 
			bang->Draw();
		for(auto meteor: vec_Meteor) 
			meteor->Draw();
		wnd->draw(shpWheel);
		for(auto key: vec_Key) 
			key->Draw();
		for(auto cost: vec_FloatCost) cost->Draw();
	}

	virtual ~Boss_5()
	{
		cam.setCenter(v2f(0,0));
		wnd->setView(cam);
	}
};