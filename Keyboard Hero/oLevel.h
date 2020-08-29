#pragma once
#include "Player.h"
#include "oBackGround.h"
#include "oPortal.h"
#include "Boss_1.h"
#include "Boss_2.h"
#include "Boss_3.h"
#include "Boss_4.h"
#include "Boss_5.h"
#include "KeyKillEffectFire.h"
#include "KeyKillEffectFrost.h"
#include "KeyKillEffectEpic.h"
#include "KeyKillEffectNature.h"
#include "KeyKillEffectBlack.h"
#include "KeyKillEffectWhite.h"
#include "oButton.h"
#include "BonusBar.h"
#include "BonusBarLogo.h"
#include "FloatSphere.h"
#include "FloatCost.h"
#include "LastKey.h"
#include "PauseMenu.h"


class oLevel : public System
{
protected:

	enum STATE { welcome, play, score, pause, end } state;
	sf::Text text_welcome;

	bool isBonusFire;
	bool isBonusFrost;
	bool isBonusEpic;
	bool isFail;
	bool isBoss;

	float timer_Fail_Create_Score;
	float timer_Duration_Bonus_Frost;
	float timer_Duration_Bonus_Fire;
	float timer_Duration_Bonus_Epic;

	uint boss_score;
	uint count_key_capture;
	uint count_key;
	uint count_key_max;
	uint level_Score;
	uint key_type;
	uint percent_need;
	vector<shared_ptr<oPortal>> vec_Portal;
	vector<shared_ptr<oKeyMove>> vec_Key;
	vector<shared_ptr<oKeyKillEffect>> vec_KeyKillEffect;
	vector<shared_ptr<oButton>> vec_Button_Table;
	vector<shared_ptr<BonusBar>> vec_Bonus_Bar;
	vector<shared_ptr<FloatSphere>> vec_Float_Sphere;
	vector<shared_ptr<FloatCost>> vec_Float_Cost;
	vector<shared_ptr<oButton>> vec_Button_Pause_Menu;
	vector<shared_ptr<oBackGround>> vec_BG;
	vector<shared_ptr<PortalMulticolor>> vec_PortalMulti;
	vector<shared_ptr<BonusBarLogo>> vec_Bonus_Bar_Logo;
	vector<shared_ptr<oPortal>> vec_Teleport;
	vector<shared_ptr<oBoss>> vec_Boss;

	LastKey lastKey;

	Shape shpFailed;
	PauseMenu pause_Menu;

	float timer_key_spawn;
	float timer_welcome;

	inline void Welcome()
	{
		if(timer_welcome < 5000)
		{
			timer_welcome += time;
			if(timer_welcome > 5000) timer_welcome = 5000;
			text_welcome.setColor(sf::Color(0,255,0, 255 - 255* (timer_welcome / 5000)));
			static uint i = 0;
		}
		else state = play;
	}

	static Player* m_player;
	sf::Music* music;

public:

	bool isExit() const
	{
		if(pause_Menu.isGoToMainMenu())
			return true; 
		return false;
	}

	static void setPlayer(Player& _player)
	{
		m_player = &_player;
	}

	bool isEnd()
	{
		if(state == end) return true;
		return false;
	}

	virtual void restart()
	{
		timer_Fail_Create_Score = 0;
		isFail = false;
		count_key = 0;
		key_type = 0;
		int lev_sc = level_Score;
		level_Score = 0;
		m_player->addScore(-boss_score);
		boss_score = 0;
		m_player->addScore(-lev_sc);
		count_key_capture = 0;
		m_player->clearCombo();
		m_player->clearTableRecord();
		m_player->setKeyCount(count_key_max);
		timer_key_spawn = 0;
		timer_welcome = 0;
		state = welcome;
		vec_Button_Table.clear();
		vec_Float_Sphere.clear();
		for(auto bonus_bar: vec_Bonus_Bar) 
			bonus_bar->clear();
		for(auto bonus_logo: vec_Bonus_Bar_Logo)
			bonus_logo->Activated(0);
		vec_Key.clear();
		vec_KeyKillEffect.clear();
		isBonusEpic = false;
		isBonusFire = false;
		isBonusFrost = false;
		vec_Boss.clear();
		isBoss = false;
		cam.setCenter(0,0);
		wnd->setView(cam);
		sound->ShowScore.stop();
	}

	oLevel(void) :
		state(welcome),
		level_Score(0),
		boss_score(0),
		timer_welcome(0),
		timer_key_spawn(0),
		key_type(0),
		isBonusEpic(false),
		isBonusFire(false),
		isBonusFrost(false),
		isFail(false),
		isBoss(false),
		timer_Duration_Bonus_Frost(0),
		timer_Duration_Bonus_Fire(0),
		timer_Duration_Bonus_Epic(0),
		timer_Fail_Create_Score(0)
	{
		ConstructShape(shpFailed, v2f(0,-39.5), v2f(25,6), texture->LevelFailed, true);

		vec_Bonus_Bar_Logo.push_back(make_shared<BonusBarLogo>(BonusBarLogo(v2f(-57.5f, -46.f), "Fire")));
		vec_Bonus_Bar_Logo.push_back(make_shared<BonusBarLogo>(BonusBarLogo(v2f(-27.5f, -46.f), "Frost")));
		vec_Bonus_Bar_Logo.push_back(make_shared<BonusBarLogo>(BonusBarLogo(v2f(2.5f, -46.f), "Epic")));
		vec_Bonus_Bar_Logo.push_back(make_shared<BonusBarLogo>(BonusBarLogo(v2f(32.5f, -46.f), "Nature")));
	}

	virtual void CreateBonusBar(uint fire, uint frost, uint dark, uint life)
	{
		vec_Bonus_Bar.push_back(make_shared<BonusBar>(BonusBar(fire, v2f(-57.5f, -46.f), "Fire")));
		vec_Bonus_Bar.push_back(make_shared<BonusBar>(BonusBar(frost, v2f(-27.5f, -46.f), "Frost"))); 
		vec_Bonus_Bar.push_back(make_shared<BonusBar>(BonusBar(dark, v2f(2.5f, -46.f), "Epic")));
		vec_Bonus_Bar.push_back(make_shared<BonusBar>(BonusBar(life, v2f(32.5f, -46.f), "Nature")));
	}

	virtual inline void CreateBlackKey()
	{
		const uint num = vec_Key.back()->getKeyNum();
		const v2f pos = vec_Key.back()->getPosition()/scr_1;
		const float siz = vec_Key.back()->getSize()/scr_1;
		const v2f spd = vec_Key.back()->getSpeed()/scr_1;
		vec_Key.pop_back();
		vec_Key.push_back(make_shared<KeyBlack>(KeyBlack(num, v2f(pos.x, pos.y+20), v2f(siz, siz), spd, "Black")));
		count_key--;
	}

	virtual inline void CreateWhiteKey()
	{
		const uint num = vec_Key.back()->getKeyNum();
		const v2f pos = vec_Key.back()->getPosition()/scr_1;
		const float siz = vec_Key.back()->getSize()/scr_1;
		const v2f spd = vec_Key.back()->getSpeed()/scr_1;
		vec_Key.pop_back();
		vec_Key.push_back(make_shared<KeyWhite>(KeyWhite(num, v2f(pos.x, pos.y+20), v2f(siz, siz), spd, "White")));
	}

	virtual inline void Teleport(string T_S, string T_E, v2f spd)
	{
		for(auto teleport: vec_Teleport)
		{
			if(teleport->getType() == T_S)
				for(auto key: vec_Key)
					if(getDist(key->getPosition(), teleport->getPosition()) < (key->getSize()/2.f+teleport->getSize())/12.f)
						for(auto T2E: vec_Teleport)
							if(T2E->getType() == T_E) 
							{
								key->setPostion(T2E->getPosition());
								key->setSpeed(spd);
							}
		}
	}

	virtual inline void CreateFrosKey(v2f pos, v2f siz, v2f spd)
	{
		vec_Key.push_back(make_shared<KeyFrost>(KeyFrost(getRandKeyNum(), pos, siz, spd, "Frost"))); count_key++;
	}

	virtual inline void CreateEpicKey(v2f pos, v2f siz, v2f spd)
	{
		vec_Key.push_back(make_shared<KeyEpic>(KeyEpic(getRandKeyNum(), pos, siz, spd, "Epic"))); count_key++;
	}

	virtual inline void CreateLifeKey(v2f pos, v2f siz, v2f spd)
	{
		vec_Key.push_back(make_shared<KeyNature>(KeyNature(getRandKeyNum(), pos, siz, spd, "Nature"))); count_key++;
	}

	virtual inline void CreateFireKey(v2f pos, v2f siz, v2f spd)
	{
		vec_Key.push_back(make_shared<KeyFire>(KeyFire(getRandKeyNum(), pos, siz, spd, "Fire"))); count_key++;
	}

	virtual inline void KeyGenWhiteBlack(uint chanceWhite, uint chanceBlack)
	{
		uint chance = rand()%100;
		if(chance < chanceBlack) CreateBlackKey();
		if(chance > 99-chanceWhite) CreateWhiteKey();
	}


	virtual void Action()
	{
		if(state == pause)
		{
			pause_Menu.Action();
			if(pause_Menu.isGoToMainMenu()) 
			{ 
				restart(); 
				state = end; 
			}
			if(pause_Menu.isResume())  state = play;
			if(pause_Menu.isRestart())
			{
				restart();
				pause_Menu.clearRestart();
			}
		}

		if(event.type == sf::Event::KeyPressed)
		{
			if(state != pause)
			{
				if(event.key.code == Key::Space)
				{
					for(auto portal: vec_PortalMulti)
					{
						portal->SetNextColor();
						for(auto key: vec_Key)
						{
							if(getDist(key->getPosition(), portal->getPosition()) < (portal->getSize()/2.f)-(key->getSize()/2.f))
							{
								if(key->isAllow()) 
									key->setStateMove();
							}
						}
					}
				}

				if(event.key.code == Key::Return)
				{
					for(auto portal: vec_PortalMulti)
					{
						portal->SetBackColor();
						for(auto key: vec_Key)
						{
							if(getDist(key->getPosition(), portal->getPosition()) < (portal->getSize()/2.f)-(key->getSize()/2.f))
							{
								if(key->isAllow())  
									key->setStateMove();
							}
						}
					}
				}
			}
			if(event.key.code == Key::F1) for(auto bonus_bar: vec_Bonus_Bar) if(bonus_bar->getActive())
				if(bonus_bar->getType() == "Fire") 
				{
					bonus_bar->use();
					sound->BonusFireAct.play();
					timer_Duration_Bonus_Fire = 30000;
					isBonusFire = true;
					for(auto bonus_logo: vec_Bonus_Bar_Logo)
						if(bonus_logo->getType() == "Fire") 
							bonus_logo->Activated(30000);
				}

			if(event.key.code == Key::F2) for(auto bonus_bar: vec_Bonus_Bar) if(bonus_bar->getActive())
				if(bonus_bar->getType() == "Frost") 
				{
					bonus_bar->use();
					timer_Duration_Bonus_Frost = 20000;
					for(auto bonus_logo: vec_Bonus_Bar_Logo)
						if(bonus_logo->getType() == "Frost") 
							bonus_logo->Activated(20000);
					isBonusFrost = true;
				}

			if(event.key.code == Key::F3) for(auto bonus_bar: vec_Bonus_Bar) if(bonus_bar->getActive())
				if(bonus_bar->getType() == "Epic") 
				{
					bonus_bar->use();
					sound->BonusDarkAct.play();
					timer_Duration_Bonus_Epic = 10000;
					for(auto bonus_logo: vec_Bonus_Bar_Logo)
						if(bonus_logo->getType() == "Epic") 
							bonus_logo->Activated(10000);
					if(!isBonusEpic)
					{
						isBonusEpic = true;
						for(auto portal: vec_Portal)
							if(portal->getType() != "Crematory" && portal->getType() != "Creator")
								portal->setFillColor(sf::Color::Black);
						for(auto portmulti: vec_PortalMulti) 
							portmulti->setFillColor(sf::Color::Black);
					}
				}

			if(event.key.code == Key::F4) for(auto bonus_bar: vec_Bonus_Bar) if(bonus_bar->getActive())
			{
				if(bonus_bar->getType() == "Nature") 
				{
					for(auto bonus_logo: vec_Bonus_Bar_Logo)
						if(bonus_logo->getType() == "Nature") 
							bonus_logo->Activated(3000);
					bonus_bar->use();
					sound->BonusLifeAct.play();
					for(auto key: vec_Key) 
					{
						if(!key->isKill() && key->getType() != "Black")
						{
							m_player->addCapture(key->getType());
							m_player->addCombo();
							m_player->addScore(m_player->getCombo()*(10*modifier_speed));
							level_Score += m_player->getCombo()*(10*modifier_speed);
							vec_Float_Cost.push_back(make_shared<FloatCost>(
								FloatCost(key->getPosition(), m_player->getCombo()*(10*modifier_speed))));
							m_player->setKeyCount(count_key_max);

							for(auto bonus_bar: vec_Bonus_Bar)
							{
								if(bonus_bar->getType() == key->getType())
									vec_Float_Sphere.push_back(make_shared<FloatSphere>(
									FloatSphere(key->getPosition(), bonus_bar->getSpherePosition(), key->getType())));
								if(key->getType() == "White")
									vec_Float_Sphere.push_back(make_shared<FloatSphere>(
									FloatSphere(key->getPosition(), bonus_bar->getSpherePosition(), bonus_bar->getType())));
							}
							key->setStateKill();
						}
					}
				}
			}
			//L47-R48 ХЪ
			//49-52 ЖЭ
			//50-51 БЮ
			if(state != pause)
			if ((language == EN && event.key.code >= 0 && event.key.code < 26) 
				|| (language == RU && ((event.key.code >= 0 && event.key.code < 26) || (event.key.code >= 46 && event.key.code <= 51))))
			{
				lastKey.setKeyNum(event.key.code);

				for(auto key: vec_Key)
				{
					if(key->getKeyNum() == event.key.code)
					{
						if(key->isAllow())
						{
							if(isBonusEpic)
							{
								if(key->getType() != "Black")
								{
									sound->KeyCapture.play();
									count_key_capture++;
									m_player->addCombo();
									
									if(isBonusFire) // Score x2
									{
										m_player->addScore(m_player->getCombo()*(20*modifier_speed));
										level_Score += m_player->getCombo()*(20*modifier_speed);
										vec_Float_Cost.push_back(make_shared<FloatCost>(
											FloatCost(key->getPosition(), m_player->getCombo()*(20*modifier_speed))));
									}
									else
									{
										m_player->addScore(m_player->getCombo()*(20*modifier_speed));
										level_Score += m_player->getCombo()*(20*modifier_speed);
										vec_Float_Cost.push_back(make_shared<FloatCost>(
											FloatCost(key->getPosition(), m_player->getCombo()*(20*modifier_speed))));
									}

									m_player->addCapture(key->getType());
									m_player->setKeyCount(count_key_max);
									key->setStateHook(key->getPosition());
									for(auto bonus_bar: vec_Bonus_Bar)
									{
										if(key->getType() == bonus_bar->getType())
											vec_Float_Sphere.push_back(make_shared<FloatSphere>(
											FloatSphere(key->getPosition(), bonus_bar->getSpherePosition(), key->getType())));
										if(key->getType() == "White")
										{
											vec_Float_Sphere.push_back(make_shared<FloatSphere>(
											FloatSphere(key->getPosition(), bonus_bar->getSpherePosition(), bonus_bar->getType())));
										}
									}
								}
							}
							else
							{
								for(auto portal: vec_Portal)
								{
									if(getDist(key->getPosition(), portal->getPosition()) < (portal->getSize()/2.f)-(key->getSize()/2.f))
									{
										if(key->getName() == portal->getName())
										{
											if(key->getType() != "Black")
											{
												sound->KeyCapture.play();
												count_key_capture++;
												m_player->addCombo();
												
												if(isBonusFire) // Score x2
												{
													m_player->addScore(m_player->getCombo()*(20*modifier_speed));
													level_Score += m_player->getCombo()*(20*modifier_speed);
													vec_Float_Cost.push_back(make_shared<FloatCost>(
														FloatCost(key->getPosition(), m_player->getCombo()*(20*modifier_speed))));
												}
												else
												{
													m_player->addScore(m_player->getCombo()*(10*modifier_speed));
													level_Score += m_player->getCombo()*(10*modifier_speed);
													vec_Float_Cost.push_back(make_shared<FloatCost>(
														FloatCost(key->getPosition(), m_player->getCombo()*(10*modifier_speed))));
												}

												m_player->addCapture(key->getType());
												m_player->setKeyCount(count_key_max);
												key->setStateHook(portal->getPosition());
												for(auto bonus_bar: vec_Bonus_Bar)
												{
													if(key->getType() == bonus_bar->getType())
														vec_Float_Sphere.push_back(make_shared<FloatSphere>(
														FloatSphere(key->getPosition(), bonus_bar->getSpherePosition(), key->getType())));
													if(key->getType() == "White")
													{
														vec_Float_Sphere.push_back(make_shared<FloatSphere>(
														FloatSphere(key->getPosition(), bonus_bar->getSpherePosition(), bonus_bar->getType())));
													}
												}
											}
											else
											{
												key->setStateHook(portal->getPosition());
												sound->KeyCaptureBlack.play();
												m_player->clearCombo();
												for(auto bonus_bar: vec_Bonus_Bar) 
													bonus_bar->clear();
											}
										}
									}
								}
								for(auto portal: vec_PortalMulti)
								{
									if(getDist(key->getPosition(), portal->getPosition()) < (portal->getSize()/2.f)-(key->getSize()/2.f))
									{
										if(key->getName() == portal->getName())
										{
											if(key->getType() != "Black")
											{
												sound->KeyCapture.play();
												count_key_capture++;
												m_player->addCombo();
											
												if(isBonusFire) // Score x2
												{
													m_player->addScore(m_player->getCombo()*(20*modifier_speed));
													level_Score += m_player->getCombo()*(20*modifier_speed);
													vec_Float_Cost.push_back(make_shared<FloatCost>(
														FloatCost(key->getPosition(), m_player->getCombo()*(20*modifier_speed))));
												}
												else
												{
													m_player->addScore(m_player->getCombo()*(10*modifier_speed));
													level_Score += m_player->getCombo()*(10*modifier_speed);
													vec_Float_Cost.push_back(make_shared<FloatCost>(
														FloatCost(key->getPosition(), m_player->getCombo()*(10*modifier_speed))));
												}

												m_player->addCapture(key->getType());
												m_player->setKeyCount(count_key_max);
												key->setStateHook(portal->getPosition());
												for(auto bonus_bar: vec_Bonus_Bar)
												{
													if(key->getType() == bonus_bar->getType())
														vec_Float_Sphere.push_back(make_shared<FloatSphere>(
														FloatSphere(key->getPosition(), bonus_bar->getSpherePosition(), key->getType())));
													if(key->getType() == "White")
													{
														vec_Float_Sphere.push_back(make_shared<FloatSphere>(
														FloatSphere(key->getPosition(), bonus_bar->getSpherePosition(), bonus_bar->getType())));
													}
												}
											}
											else
											{
												key->setStateHook(portal->getPosition());
												sound->KeyCaptureBlack.play();
												m_player->clearCombo();
												for(auto bonus_bar: vec_Bonus_Bar) 
													bonus_bar->clear();
											}
										}
									}
								}
							}
						}
					}
				}
			}

			if(event.key.code == sf::Keyboard::Escape) 
			{
				if(state != score)
				{
					if(state != pause)
					{ 
						pause_Menu.setMain(); 
						state = pause;
						isPauseGame = true;

						for(auto key: vec_Key) 
							key->setKeyNum(getRandKeyNum());

						for(auto boss: vec_Boss) 
							boss->RenameKey();
					}
					else 
					{
						isPauseGame = false;
						state = play;
					}
				}
			}
		}
		if(state == score)
		{
			for(auto button: vec_Button_Table)
			{
				if(button->isActivate())
				{
					if(button->getNameID() == "Restart")
					{
						restart();
						break;
					}

					if(button->getNameID() == "Continue")
					{
						m_player->saveToFile();
						m_player->clearTableRecord();
						vec_Button_Table.clear();
						sound->ShowScore.stop();
						vec_Bonus_Bar.clear();
						vec_Bonus_Bar_Logo.clear();
						m_player->setKeyCount(count_key_max);
						state = end;
						break;
					}
					if(button->getNameID() == "95%")
					{
						sound->ClickError.play();
					}
				}
			}
		}
	}
	
	virtual void Update()
	{
		// Меняем буквы на белых символах
		if(!isPauseGame)
		{
			static float timer_white = 0;
			timer_white += time;
			if(timer_white >= 2000)
			{
				for(auto key: vec_Key) 
					if(key->getType() == "White")
						key->setKeyNum(getRandKeyNum());

				for(auto boss: vec_Boss) 
					boss->RenameKeyWhite();

				timer_white = 0;
			}

			// Если активирован FROST бонус, то замедляем время и музыку
			if(isBonusFrost)
			{
				time/=1.5f;
				if(music->getPitch() > 0.75f)
					music->setPitch(music->getPitch()-(0.0004*time));
			}
			else // Иначе возвращаем номральную скорость музыки
			{
				if(music->getPitch() < 1.0f)
					music->setPitch(music->getPitch() + (0.0004*time));
			}

			// Апдейтим всё
			for(auto teleport: vec_Teleport) teleport->Update();
			for(auto portal: vec_Portal) portal->Update();
			for(auto portal: vec_PortalMulti) portal->Update();
			for(auto key: vec_Key) key->Update();
			for(auto bg: vec_BG) bg->Update();

			// Проигрываем музыку
			if(state != score && music->getStatus() != sf::Music::Status::Playing) music->play();

			// Апдейтим текст награды
			for(auto it = vec_Float_Cost.begin(); it != vec_Float_Cost.end();)
			{
				auto& obj = *(*it);
				if(obj.isKill()) it = vec_Float_Cost.erase(it);
				else
				{
					obj.Update();
					it++;
				}
			}

			// Апдейтим значки активированных бонусов
			for(auto bonus_logo: vec_Bonus_Bar_Logo) 
				bonus_logo->Update();

			//Апдейтим спецэффекты символов
			for(auto it = vec_Float_Sphere.begin(); it != vec_Float_Sphere.end();)
			{
				auto& obj = *(*it);

				if(obj.isKill()){ it = vec_Float_Sphere.erase(it); break;}

				for(auto bonus_bar: vec_Bonus_Bar)
				{
					if(bonus_bar->getType() == obj.getType())
					{
						if(obj.getPosition().y >= bonus_bar->getSpherePosition().y)
						{
							obj.Update();
						}
						else if(!obj.isKill())
						{
							bonus_bar->addCount();
							obj.Kill();
						}
					}
				}
				it++;
			}

			for(auto it = vec_KeyKillEffect.begin(); it != vec_KeyKillEffect.end();)
			{
				auto &obj = *(*it);
				if(obj.isEnd()) it = vec_KeyKillEffect.erase(it);
				else
				{
					obj.Update();
					it++;
				}
			}
		}

		switch(state)
		{
		case STATE::play: 
		{
			// Засекаем время активированных бонусов
			timer_Duration_Bonus_Frost -= time;
			timer_Duration_Bonus_Fire  -= time;
			timer_Duration_Bonus_Epic  -= time;
			lastKey.Update();
			
			// Если пропустили много символов или босс победил, то отсчитываем 5 секунд до появления таблицы статистики
			if(isFail) timer_Fail_Create_Score += time;

			// Если время бонусов истекло, то отключаем их
			if(timer_Duration_Bonus_Epic  <= 0) { 
				if(isBonusEpic) 
					for(auto key: vec_Key) 
						if(key->isAllow()) 
							key->setStateMove(); 
				isBonusEpic = false;
			}
			if(timer_Duration_Bonus_Fire  <= 0) isBonusFire  = false;
			if(timer_Duration_Bonus_Frost <= 0) isBonusFrost = false;

			for(auto key: vec_Key)
			{
				// Двигаем символы, если активирован FROST то добавляем спецэффект
				if(key->isMove() || key->isAllow())
					if(isBonusFrost) key->Move("Frost");
					else key->Move("");

				for(auto portal: vec_PortalMulti)
				{
					if(!isBonusEpic) portal->setFillColor(sf::Color::White);
					if(key->isMove() || key->isAllow())
					{
						if(getDist(key->getPosition(), portal->getPosition()) < (portal->getSize()/2.f)-(key->getSize()/2.f))
						{
							if(portal->getType() != "Crematory" && portal->getType() != "Creator")
							{
								if((key->getType() == "Black" && key->getName() != portal->getName()) 
									|| (key->getType() == "White" && key->getName() != portal->getName()))
								{
									key->setName(portal->getName());
									key->setStateAllow();
								}
							}

							if(key->getType() == portal->getType())
							{
								key->setName(portal->getName());
								key->setStateAllow();
							}
						}
						else 
						{
							if(key->getName() == portal->getName())
							{
								if(key->isAllow())
								{
									key->setName("");
									key->setStateMove();
								}
							}
						}
					}
				}
				for(auto portal: vec_Portal)
				{
					if(!isBonusEpic) portal->setFillColor(sf::Color::White);
					if(key->isMove() || key->isAllow())
					{
						if(getDist(key->getPosition(), portal->getPosition()) < (portal->getSize()/2.f)-(key->getSize()/2.f))
						{
							if(portal->getType() != "Crematory" && portal->getType() != "Creator")
								if((key->getType() == "Black" && key->getName() != portal->getName())
									|| (key->getType() == "White" && key->getName() != portal->getName()))
								{
									key->setName(portal->getName());
									key->setStateAllow();
								}

							if(key->getType() == portal->getType())
							{
								key->setName(portal->getName());
								key->setStateAllow();
							}
						}
						else 
						{
							if(key->getName() == portal->getName())
							{
								if(key->isAllow())
								{
									key->setName("");
									key->setStateMove();
								}
							}
						}
					}

					if(key->isMove() || key->isAllow())
					{
						if(portal->getType() == "Crematory")
						{
							if(getDist(key->getPosition(), portal->getPosition()) < (portal->getSize()/2.f)-(key->getSize()/2.f))
							{
								if(key->getType() != "Black")
								{
									m_player->addCaptureMiss();
									m_player->setKeyCount(count_key_max);
									m_player->clearCombo();
									if(100 - (float(100)/count_key_max)*m_player->getMiss() < percent_need)
									{
										isFail = true;
									}
									sound->KeyMiss.play();
								}

								key->setStateKill();
								key->setPostion(portal->getPosition());
							}
						}
						if(isBonusEpic) 
							if(key->isMove()) 
								key->setStateAllow();
					}
				}
			}

			for(auto it = vec_Key.begin(); it != vec_Key.end();)
			{
				auto& obj = *(*it);
				if(!getVisible().contains(obj.getPosition()))
				{
					if(obj.getType() != "Black")
					{
						m_player->addCaptureMiss();
						m_player->setKeyCount(count_key_max);
						m_player->clearCombo();
						if(100 - (float(100)/count_key_max)*m_player->getMiss() < percent_need)
						{
							isFail = true;
						}
						sound->KeyMiss.play();
					}
				}

				if((obj.isDestroy() || !getVisible().contains(obj.getPosition())))
				{
					if(obj.getType() == "Fire") 
						vec_KeyKillEffect.push_back(make_shared<KeyKillEffectFire>(KeyKillEffectFire(obj.getPosition(), obj.getSize())));
					if(obj.getType() == "Frost") 
						vec_KeyKillEffect.push_back(make_shared<KeyKillEffectFrost>(KeyKillEffectFrost(obj.getPosition(), obj.getSize())));
					if(obj.getType() == "Epic") 
						vec_KeyKillEffect.push_back(make_shared<KeyKillEffectEpic>(KeyKillEffectEpic(obj.getPosition(), obj.getSize())));
					if(obj.getType() == "Nature") 
						vec_KeyKillEffect.push_back(make_shared<KeyKillEffectNature>(KeyKillEffectNature(obj.getPosition(), obj.getSize())));
					if(obj.getType() == "Black") 
						vec_KeyKillEffect.push_back(make_shared<KeyKillEffectBlack>(KeyKillEffectBlack(obj.getPosition(), obj.getSize())));
					if(obj.getType() == "White") 
						vec_KeyKillEffect.push_back(make_shared<KeyKillEffectWhite>(KeyKillEffectWhite(obj.getPosition(), obj.getSize())));
					
					it = vec_Key.erase(it);
				}
				else it++;
			}

			// Если символы закончились, то заканчиваем уровень появлением таблицы статистики
			// Или уровень провален, то через 0.5 секунд предлагаем рестарт
			if((count_key >= count_key_max && vec_Key.empty() && vec_KeyKillEffect.empty()) 
				|| (isFail && timer_Fail_Create_Score > 500))
			{
				m_player->setRecord(count_key_max);
				state = score;
				sound->stopMusic();
				sound->ShowScore.play();
				if(m_player->getCapturePercent() >= percent_need)
				{
					vec_Button_Table.push_back(make_shared<Button_YN>(Button_YN(v2f(-8, 27), v2f(15,5), texture->Button, "Restart", "Restart")));
					vec_Button_Table.push_back(make_shared<Button_YN>(Button_YN(v2f(8, 27), v2f(15,5), texture->Button, "Continue", "Continue")));
				}
				else
				{
					vec_Button_Table.push_back(make_shared<Button_YN>(Button_YN(v2f(-8, 27), v2f(15,5), texture->Button, "Restart", "Restart")));
					vec_Button_Table.push_back(make_shared<Button_YN>(Button_YN(v2f(8, 27), v2f(15,5), texture->Button, "Need "+to_string(percent_need)+"%", "95%")));
				}
			}

			for(auto boss: vec_Boss) 
			{
				boss->Update();
				boss_score = boss->getScore();
				if(boss->isDead())
				{
					vec_Boss.clear();
					isBoss = false;
				}
				if(boss->isWin())
				{
					vec_Boss.clear();
					m_player->setRecord(count_key_max);
					state = score;
					sound->stopMusic();
					sound->ShowScore.play();
					isBoss = false;
					vec_Button_Table.push_back(make_shared<Button_YN>(Button_YN(v2f(-8, 27), v2f(15,5), texture->Button, "Restart", "Restart")));
					vec_Button_Table.push_back(make_shared<Button_YN>(Button_YN(v2f(8, 27), v2f(15,5), texture->Button, "Boss Win", "95%")));
				}
			}
		}
		break;

		case STATE::score:
			for(auto button: vec_Button_Table) 
				button->Update();
			break;

		case STATE::pause:
			pause_Menu.Update();
			break;
		}
	}

	virtual void Draw()
	{
		for(auto bg: vec_BG) bg->Draw();
		lastKey.Draw();
		for(auto portal: vec_PortalMulti) portal->Draw();
		for(auto teleport: vec_Teleport) teleport->Draw();
		for(auto portal: vec_Portal) portal->Draw();
		for(auto effect: vec_KeyKillEffect) effect->Draw();
		for(auto key: vec_Key) key->Draw();
		for(auto boss: vec_Boss) boss->Draw();
		if(isFail) wnd->draw(shpFailed);

		m_player->Draw();

		if(state != score)
		{
			for(auto bonus_bar: vec_Bonus_Bar) bonus_bar->Draw();
			for(auto bonus_logo: vec_Bonus_Bar_Logo) bonus_logo->Draw();
			for(auto sphere: vec_Float_Sphere) sphere->Draw();
			for(auto cost: vec_Float_Cost) cost->Draw();
		}

		if(state == score) 
		{
			for(auto button: vec_Button_Table) 
				button->Draw();
		}
		if(state == pause) pause_Menu.Draw();
	}

	virtual ~oLevel(void)
	{
	}
};