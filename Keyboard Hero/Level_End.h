#pragma once
#include "oLevel.h"

class Level_End : public oLevel
{
private:

	sf::Text text_Congratulations, text_Score;
	Button_YN but_Continue;

public:

	Level_End(void) : but_Continue(v2f(50,45), v2f(12,4), texture->Button, "Exit", "Exit")
	{
		music = &sound->MainTheme;
		vec_BG.push_back(make_shared<BackGround_L7>(BackGround_L7()));
		ConstructText(text_Congratulations, v2f(0,-5)*scr_1, 6.5, sf::Color(255,255,60,128), "Congratulations! It end game.", font_lines);
		ConstructText(text_Score, v2f(0,5)*scr_1, 6.5, sf::Color(180,255,75,128), "Your score " + to_string(m_player->getScore()) + "!", font_oduda);
		vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(-35,-10), v2f(15,15),"")));
		vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(-40,10), v2f(15,15),"")));
		vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(-45,30), v2f(15,15),"")));
		vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(-35,50), v2f(15,15),"")));
		vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(35,-10), v2f(15,15),"")));
		vec_Portal.push_back(make_shared<PortalTornadoNature>(PortalTornadoNature(v2f(40,10), v2f(15,15),"")));
		vec_Portal.push_back(make_shared<PortalTornadoFrost>(PortalTornadoFrost(v2f(45,30), v2f(15,15),"")));
		vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f(35,50), v2f(15,15),"")));
		vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(0,-20), v2f(15,15),"")));
	}

	virtual void Action()
	{
		if(but_Continue.isActivate())
		{
			m_player->saveToFile();
			m_player->clearTableRecord();
			vec_Button_Table.clear();
			vec_Bonus_Bar.clear();
			vec_Bonus_Bar_Logo.clear();
			m_player->setKeyCount(count_key_max);
			state = end;
			gState = main_menu;
		}
	}

	virtual void Update()
	{
		for(auto portal: vec_Portal) portal->Update();
		for(auto bg: vec_BG) bg->Update();
		but_Continue.Update();
	}

	virtual void Draw()
	{
		for(auto bg: vec_BG) bg->Draw();
		for(auto portal: vec_Portal) portal->Draw();
		but_Continue.Draw();
		wnd->draw(text_Congratulations);
		wnd->draw(text_Score);
	}

	virtual ~Level_End(void)
	{
	}
};