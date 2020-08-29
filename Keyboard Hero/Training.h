#pragma once
#include "oLevel.h"

class Training : public System
{
private:

	enum STATE { step_1, step_2, step_3, end } state;
	bool is_End;

	vector<shared_ptr<oPortal>> vec_Portal;
	vector<shared_ptr<oKeyMove>> vec_Key;
	vector<shared_ptr<sf::Text>> vec_Text;
	vector<shared_ptr<oButton>> vec_Button;
	vector<shared_ptr<BonusBar>> vec_BonusBar;
	vector<shared_ptr<PortalMulticolor>> vec_Portal_Multi;
	
	inline void Clear()
	{
		vec_Portal.clear();
		vec_Key.clear();
		vec_Text.clear();
		vec_BonusBar.clear();
		vec_Portal_Multi.clear();
	}

public:

	bool isEnd() const { if(state == end) return true; return false; }

	void Action()
	{
		for(auto button: vec_Button) 
		{
			if(button->isActivate())
			{
				if(button->getNameID() == "Continue")
				{
					switch (state)
					{
					case Training::step_1:

						Clear();

						vec_Key.push_back(make_shared<KeyFire>(KeyFire(0,v2f(-45, 5), v2f(7,7), v2f(0,0), "")));
						vec_Text.push_back(make_shared<sf::Text>(sf::Text(L"Symbol of fire.", *font_modeka)));
						vec_Text.back()->setPosition(v2f(-34*scr_1, -15*scr_1-vec_Text.back()->getGlobalBounds().height/2.f));

						vec_Key.push_back(make_shared<KeyFrost>(KeyFrost(1,v2f(-45, 15), v2f(7,7), v2f(0,0), "")));
						vec_Text.push_back(make_shared<sf::Text>(sf::Text("Symbol of frost.", *font_modeka)));
						vec_Text.back()->setPosition(v2f(-34*scr_1, -5*scr_1-vec_Text.back()->getGlobalBounds().height/2.f));

						vec_Key.push_back(make_shared<KeyEpic>(KeyEpic(2,v2f(-45, 25), v2f(7,7), v2f(0,0), "")));
						vec_Text.push_back(make_shared<sf::Text>(sf::Text("Symbol of darkness.", *font_modeka)));
						vec_Text.back()->setPosition(v2f(-34*scr_1, 5*scr_1-vec_Text.back()->getGlobalBounds().height/2.f));

						vec_Key.push_back(make_shared<KeyNature>(KeyNature(3,v2f(-45, 35), v2f(7,7), v2f(0,0), "")));
						vec_Text.push_back(make_shared<sf::Text>(sf::Text("Symbol of life.", *font_modeka)));
						vec_Text.back()->setPosition(v2f(-34*scr_1, 15*scr_1-vec_Text.back()->getGlobalBounds().height/2.f));

						vec_Key.push_back(make_shared<KeyWhite>(KeyWhite(4,v2f(-45, 45), v2f(7,7), v2f(0,0), "White")));
						vec_Text.push_back(make_shared<sf::Text>(sf::Text("Symbol of instability. Periodically changes letter.", *font_modeka)));
						vec_Text.back()->setPosition(v2f(-34*scr_1, 25*scr_1-vec_Text.back()->getGlobalBounds().height/2.f));

						vec_Key.push_back(make_shared<KeyBlack>(KeyBlack(5,v2f(-45, 55), v2f(7,7), v2f(0,0), "")));
						vec_Text.push_back(make_shared<sf::Text>(sf::Text("Symbol of parasite. Do not catch them, else clear combo and bonuses.", *font_modeka)));
						vec_Text.back()->setPosition(v2f(-34*scr_1, 35*scr_1-vec_Text.back()->getGlobalBounds().height/2.f));

						for(auto text: vec_Text) 
						{
							text->setColor(sf::Color::White);
							text->setCharacterSize(uint(scr_1*2.f));
						}
						state = step_2;

						break;

					case Training::step_2:

						Clear();
						vec_BonusBar.push_back(make_shared<BonusBar>(BonusBar(3,v2f(-50,-7.5f), "Fire")));
						vec_Text.push_back(make_shared<sf::Text>(sf::Text("Fire bonus. Symbols gives x2 points.", *font_modeka)));
						vec_Text.back()->setPosition(v2f((12.5*scr_1)-35*scr_1, -7.5*scr_1));
						vec_BonusBar.push_back(make_shared<BonusBar>(BonusBar(3,v2f(-50,-2.5f), "Frost")));
						vec_Text.push_back(make_shared<sf::Text>(sf::Text("Frost bonus. Slow time and blink symbols.", *font_modeka)));
						vec_Text.back()->setPosition(v2f((12.5*scr_1)-35*scr_1, -2.5*scr_1));
						vec_BonusBar.push_back(make_shared<BonusBar>(BonusBar(3,v2f(-50, 2.5f), "Epic")));
						vec_Text.push_back(make_shared<sf::Text>(sf::Text("Darkness bonus. Allows absorb the symbols out of the portal.", *font_modeka)));
						vec_Text.back()->setPosition(v2f((12.5*scr_1)-35*scr_1, 2.5*scr_1));
						vec_BonusBar.push_back(make_shared<BonusBar>(BonusBar(3,v2f(-50, 7.5f), "Nature")));
						vec_Text.push_back(make_shared<sf::Text>(sf::Text("Life bonus. Instantaneous absorption of all symbols.", *font_modeka)));
						vec_Text.back()->setPosition(v2f((12.5*scr_1)-35*scr_1, 7.5*scr_1));
						for(auto text: vec_Text) 
						{
							text->setColor(sf::Color::White);
							text->setCharacterSize(uint(scr_1*2.f));
						}
						state = step_3;

						break;
					case Training::step_3:
						Clear();
						vec_Button.clear();
						state = end;
						break;
					case Training::end: break;
					}
				}
			}
		}
	}

	void Update()
	{
		for(auto portal: vec_Portal) portal->Update();
		for(auto portal: vec_Portal_Multi) portal->Update();
		for(auto key: vec_Key) key->Update();
		for(auto button: vec_Button) button->Update();

		if(state == step_1)
		{
			static float timer = 0;
			timer += time;
			if(timer >= 1000)
			{
				timer = 0;
				for(auto portal: vec_Portal_Multi) 
					portal->SetNextColor();
			}
		}

		if(state == step_2)
		{
			static float timer = 0;
			timer += time;
			if(timer >= 2000)
			{
				timer = 0;
				for(auto key: vec_Key) 
					if(key->getName() == "White")
						key->setKeyNum(getRandKeyNum());
			}
		}

		if(state == step_3)
		{
			static float timer = 0;
			timer += time;
			if(timer >= 1000)
			{
				timer = 0;
				for(auto bar: vec_BonusBar)
				{
					if(bar->getActive()) bar->clear();
					else bar->addCount();
				}
			}
		}
	}

	void Draw()
	{
		for(auto portal: vec_Portal) portal->Draw();
		for(auto portal: vec_Portal_Multi) portal->Draw();
		for(auto key: vec_Key) key->Draw();
		for(auto button: vec_Button) button->Draw();
		for(auto text: vec_Text) wnd->draw(*text);
		for(auto bar: vec_BonusBar) bar->Draw();
	}

	Training(void) : is_End(false), state(step_1)
	{
		vec_Portal.push_back(make_shared<PortalCreator>(PortalCreator(v2f(-45,0), v2f(10,10), "", true)));
		vec_Text.push_back(make_shared<sf::Text>(sf::Text("Create new symbols.", *font_modeka)));
		vec_Text.back()->setPosition(v2f(-33*scr_1, -20*scr_1-vec_Text.back()->getGlobalBounds().height/2.f));

		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(-50, 10), v2f(10,10), "")));
		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(-40,10), v2f(10,10), "")));
		vec_Text.push_back(make_shared<sf::Text>(sf::Text("Absorbs symbols of fire.", *font_modeka)));
		vec_Text.back()->setPosition(v2f(-33*scr_1, -10*scr_1-vec_Text.back()->getGlobalBounds().height/2.f));

		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(-50,20), v2f(10,10), "")));
		vec_Portal.push_back(make_shared<PortalTornadoFrost>(PortalTornadoFrost(v2f(-40,20), v2f(10,10), "")));
		vec_Text.push_back(make_shared<sf::Text>(sf::Text("Absorbs symbols of frost.", *font_modeka)));
		vec_Text.back()->setPosition(v2f(-33*scr_1, scr_1-vec_Text.back()->getGlobalBounds().height/2.f));

		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(-50,30), v2f(10,10), "")));
		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f(-40,30), v2f(10,10), "")));
		vec_Text.push_back(make_shared<sf::Text>(sf::Text("Absorbs symbols of darkness.", *font_modeka)));
		vec_Text.back()->setPosition(v2f(-33*scr_1, 10*scr_1-vec_Text.back()->getGlobalBounds().height/2.f));

		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(-50, 40), v2f(10,10), "")));
		vec_Portal.push_back(make_shared<PortalTornadoNature>(PortalTornadoNature(v2f(-40,40), v2f(10,10), "")));
		vec_Text.push_back(make_shared<sf::Text>(sf::Text("Absorbs symbols of life.", *font_modeka)));
		vec_Text.back()->setPosition(v2f(-33*scr_1, 20*scr_1-vec_Text.back()->getGlobalBounds().height/2.f));

		vec_Portal_Multi.push_back(make_shared<PortalMulticolor>(PortalMulticolor(v2f(-45, 50), v2f(10,10), "", "Fire")));
		vec_Text.push_back(make_shared<sf::Text>(sf::Text("Press spacebar, or enter to change the correct type.", *font_modeka)));
		vec_Text.back()->setPosition(v2f(-33*scr_1, 30*scr_1-vec_Text.back()->getGlobalBounds().height/2.f));

		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(-45,60), v2f(10,10), "")));
		vec_Text.push_back(make_shared<sf::Text>(sf::Text("Destroy all symbols and clear combo stack.", *font_modeka)));
		vec_Text.back()->setPosition(v2f(-33*scr_1, 40*scr_1-vec_Text.back()->getGlobalBounds().height/2.f));
		
		for(auto text: vec_Text) 
		{
			text->setColor(sf::Color::White);
			text->setCharacterSize(uint(scr_1*2.f));
		}

		vec_Button.push_back(make_shared<Button_YN>(Button_YN(v2f(45,45), v2f(15,5), texture->Button, "Continue", "Continue")));

	}

	~Training(void)
	{

	}
};