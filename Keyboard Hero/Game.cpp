#include "Game.h"


Game::Game(void) : System("init")
{
	vec_mainMenu.push_back(make_shared<MainMenu>(MainMenu(player)));
	oLevel::setPlayer(player);
	oBoss::setPlayer(player);
	while (wnd->isOpen())
	{
		SystemTime();

		while(wnd->pollEvent(event))
		{
			SystemCursor();
			if(event.type == sf::Event::Closed) 
				wnd->close();
			switch (gState)
			{
			case System::main_menu:

				for(auto menu: vec_mainMenu) 
					menu->Action();

				break;
			case System::game:

				for(auto level: vec_Level) 
					level->Action();

				////////////////////////////////////////// ×èò
				//if(event.type == sf::Event::KeyPressed)
				//{
				//	if(event.key.code == Key::Right)
				//	{
				//		vec_Level.clear();
				//		sound->stopMusic();
				//		player.nextLevel();
				//	}
				//	if(event.key.code == Key::Left)
				//	{
				//		vec_Level.clear();
				//		sound->stopMusic();
				//		player.backLevel();
				//	}
				//}

				break;
			}
		}

		switch (gState)
		{
		case System::main_menu:

			if(vec_mainMenu.empty()) 
				vec_mainMenu.push_back(make_shared<MainMenu>(MainMenu(player)));
			for(auto menu: vec_mainMenu) 
				menu->Update();
			if(!vec_Level.empty()) vec_Level.clear();
			
			break;
		case System::game:
			if(!vec_mainMenu.empty()) 
				vec_mainMenu.clear();

			if(vec_Level.empty())
			{
				//if(player.getLevel() == 1) vec_Level.push_back(make_shared<Level_Test>(Level_Test()));
				if(player.getLevel() == 1) vec_Level.push_back(make_shared<Level_1>(Level_1()));
				if(player.getLevel() == 2) vec_Level.push_back(make_shared<Level_2>(Level_2()));
				if(player.getLevel() == 3) vec_Level.push_back(make_shared<Level_3>(Level_3()));
				if(player.getLevel() == 4) vec_Level.push_back(make_shared<Level_4>(Level_4()));
				if(player.getLevel() == 5) vec_Level.push_back(make_shared<Level_5>(Level_5()));
			
				if(player.getLevel() == 6) vec_Level.push_back(make_shared<Level_6>(Level_6()));
				if(player.getLevel() == 7) vec_Level.push_back(make_shared<Level_7>(Level_7()));
				if(player.getLevel() == 8) vec_Level.push_back(make_shared<Level_8>(Level_8()));
				if(player.getLevel() == 9) vec_Level.push_back(make_shared<Level_9>(Level_9()));
				if(player.getLevel() == 10) vec_Level.push_back(make_shared<Level_10>(Level_10()));
				
				if(player.getLevel() == 11) vec_Level.push_back(make_shared<Level_11>(Level_11()));
				if(player.getLevel() == 12) vec_Level.push_back(make_shared<Level_12>(Level_12()));
				if(player.getLevel() == 13) vec_Level.push_back(make_shared<Level_13>(Level_13()));
				if(player.getLevel() == 14) vec_Level.push_back(make_shared<Level_14>(Level_14()));
				if(player.getLevel() == 15) vec_Level.push_back(make_shared<Level_15>(Level_15()));

				if(player.getLevel() == 16) vec_Level.push_back(make_shared<Level_16>(Level_16()));
				if(player.getLevel() == 17) vec_Level.push_back(make_shared<Level_17>(Level_17()));
				if(player.getLevel() == 18) vec_Level.push_back(make_shared<Level_18>(Level_18()));
				if(player.getLevel() == 19) vec_Level.push_back(make_shared<Level_19>(Level_19()));
				if(player.getLevel() == 20) vec_Level.push_back(make_shared<Level_20>(Level_20()));

				if(player.getLevel() == 21) vec_Level.push_back(make_shared<Level_21>(Level_21()));
				if(player.getLevel() == 22) vec_Level.push_back(make_shared<Level_22>(Level_22()));
				if(player.getLevel() == 23) vec_Level.push_back(make_shared<Level_23>(Level_23()));
				if(player.getLevel() == 24) vec_Level.push_back(make_shared<Level_24>(Level_24()));
				if(player.getLevel() == 25) vec_Level.push_back(make_shared<Level_25>(Level_25()));

				if(player.getLevel() == 26) vec_Level.push_back(make_shared<Level_26>(Level_26()));
				if(player.getLevel() == 27) vec_Level.push_back(make_shared<Level_27>(Level_27()));
				if(player.getLevel() == 28) vec_Level.push_back(make_shared<Level_28>(Level_28()));
				if(player.getLevel() == 29) vec_Level.push_back(make_shared<Level_29>(Level_29()));
				if(player.getLevel() == 30) vec_Level.push_back(make_shared<Level_30>(Level_30()));

				if(player.getLevel() == 31) vec_Level.push_back(make_shared<Level_31>(Level_31()));
				if(player.getLevel() == 32) vec_Level.push_back(make_shared<Level_32>(Level_32()));
				if(player.getLevel() == 33) vec_Level.push_back(make_shared<Level_33>(Level_33()));
				if(player.getLevel() == 34) vec_Level.push_back(make_shared<Level_34>(Level_34()));
				if(player.getLevel() == 35) vec_Level.push_back(make_shared<Level_35>(Level_35()));

				if(player.getLevel() == 36) vec_Level.push_back(make_shared<Level_36>(Level_36()));
				if(player.getLevel() == 37) vec_Level.push_back(make_shared<Level_37>(Level_37()));
				if(player.getLevel() == 38) vec_Level.push_back(make_shared<Level_38>(Level_38()));
				if(player.getLevel() == 39) vec_Level.push_back(make_shared<Level_39>(Level_39()));
				if(player.getLevel() == 40) vec_Level.push_back(make_shared<Level_40>(Level_40()));

				if(player.getLevel() == 41) vec_Level.push_back(make_shared<Level_41>(Level_41()));
				if(player.getLevel() == 42) vec_Level.push_back(make_shared<Level_42>(Level_42()));
				if(player.getLevel() == 43) vec_Level.push_back(make_shared<Level_43>(Level_43()));
				if(player.getLevel() == 44) vec_Level.push_back(make_shared<Level_44>(Level_44()));
				if(player.getLevel() == 45) vec_Level.push_back(make_shared<Level_45>(Level_45()));

				if(player.getLevel() == 46) vec_Level.push_back(make_shared<Level_End>(Level_End()));
			}

			for(auto level: vec_Level) 
			{
				level->Update();
				if(level->isEnd()) 
				{
					sound->stopMusic();
					if(level->isExit())
					{
						gState = main_menu;
						for(auto menu: vec_mainMenu) 
							menu->setStateMain();
					}
					vec_Level.clear();
					break;
				}
			}

			break;
		}
		
		wnd->clear();
			switch (gState)
			{
			case System::main_menu:
				for(auto menu: vec_mainMenu) menu->Draw();
				break;
			case System::game:
				for(auto level: vec_Level) level->Draw();
				break;
			}
		wnd->display();
	}

	ofstream settings("Settings/Settings.prm");
	settings << to_string(sound_Vol_Effects);
	settings << "\n"+to_string(isSound_Effects_On);
	settings << "\n"+to_string(sound_Vol_Music);
	settings << "\n"+to_string(isSound_Music_On);
	settings << "\n"+to_string(isVideo_Smoth_On);
	settings << "\n"+to_string(isVideo_VertSync_On);
	settings << "\n"+to_string(modifier_speed);
	settings << "\n"+to_string(isEffectStar);
	settings << "\n"+to_string(language);
	settings.close();
}

int main()
{
	Game play;
	return EXIT_SUCCESS;
}