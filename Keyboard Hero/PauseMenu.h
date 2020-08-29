#pragma once
#include"oButton.h"
#include "CheckBox.h"
#include "Scroller.h"

class PauseMenu : public System
{
private:

	Shape shpPause;

	bool is_GoToMainMenu;
	bool is_Restart;

	vector<shared_ptr<oButton>> vec_Pause_Main;
	vector<shared_ptr<oButton>> vec_Exit_Confirm;
	vector<shared_ptr<oButton>> vec_Settings;
	vector<shared_ptr<CheckBox>> vec_Check_Box;
	vector<shared_ptr<Scroller>> vec_Settings_Scroller;

	enum STATE { main, settings, exit, exit_confirm, resume } state;

public:

	bool isGoToMainMenu() const
	{
		return is_GoToMainMenu;
	}
	
	bool isRestart() const
	{
		return is_Restart;
	}

	void clearRestart()
	{
		is_Restart = false;
	}

	bool isResume() const
	{
		if(state == resume) return true; return false;
	}

	void setMain()
	{
		state = main;
	}

	PauseMenu(void) : is_GoToMainMenu(false), is_Restart(false), state(main)
	{
		ConstructShape(shpPause, v2f(0, -16), v2f(25, 7), texture->Pause, true);

		vec_Pause_Main.push_back(make_shared<Button_Float>(Button_Float(v2f(0,-9), v2f(24,5), texture->Button, "Resume", "Resume")));
		vec_Pause_Main.push_back(make_shared<Button_Float>(Button_Float(v2f(0,-3), v2f(24,5), texture->Button, "Restart", "Restart")));
		vec_Pause_Main.push_back(make_shared<Button_Float>(Button_Float(v2f(0, 3), v2f(24,5), texture->Button, "Settings", "Settings")));
		vec_Pause_Main.push_back(make_shared<Button_Float>(Button_Float(v2f(0, 9), v2f(24,5), texture->Button, "Exit", "Exit")));

		vec_Exit_Confirm.push_back(make_shared<Button_YN>(Button_YN(v2f(-8,-3), v2f(15,5), texture->Button, "Main Menu", "MainMenu")));
		vec_Exit_Confirm.push_back(make_shared<Button_YN>(Button_YN(v2f( 8,-3), v2f(15,5), texture->Button, "Windows", "Windows")));
		vec_Exit_Confirm.push_back(make_shared<Button_YN>(Button_YN(v2f( 0, 3), v2f(15,5), texture->Button, "Cancel", "Cancel")));
	
		vec_Check_Box.push_back(make_shared<CheckBox>(CheckBox(v2f(-25, -8), isEffectStar, "EffectStar", "Effect Star.")));
		vec_Check_Box.push_back(make_shared<CheckBox>(CheckBox(v2f(-25, -4), isVideo_Smoth_On, "VideoSmothOn", "Set smoth.")));
		vec_Check_Box.push_back(make_shared<CheckBox>(CheckBox(v2f(-25, 0), isVideo_VertSync_On, "VideoVertSyncOn", "Set vertical sync.")));
		vec_Check_Box.push_back(make_shared<CheckBox>(CheckBox(v2f(-25, 4), isSound_Music_On, "MusicOn", "Play music.")));
		vec_Check_Box.push_back(make_shared<CheckBox>(CheckBox(v2f(-25, 8), isSound_Effects_On, "EffectOn", "Play sound effects.")));

		vec_Settings_Scroller.push_back(make_shared<Scroller>(Scroller(v2f(12.5, -6), sound_Vol_Music, "MusicVol", "Music Volume.")));
		vec_Settings_Scroller.push_back(make_shared<Scroller>(Scroller(v2f(12.5,  0), sound_Vol_Effects, "EffectsVol", "Effects Volume.")));
		vec_Settings_Scroller.push_back(make_shared<Scroller>(Scroller(v2f(12.5, 6), float(modifier_speed*100)-50, "GameSpeed", "Game Speed.")));
		vec_Settings.push_back(make_shared<Button_YN>(Button_YN(v2f(0,15), v2f(15,5), texture->Button, "OK", "Back")));

	}
	
	void Update()
	{
		switch (state)
		{
		case PauseMenu::main:
			for(auto button: vec_Pause_Main) 
				button->Update();
			break;

		case PauseMenu::settings:
			for(auto button: vec_Settings) 
				button->Update();
			break;

		case PauseMenu::exit_confirm:
			for(auto button: vec_Exit_Confirm) 
				button->Update();
			break;
		}
	}

	void Action()
	{
		switch (state)
		{
		case PauseMenu::main:

			for(auto button: vec_Pause_Main) 
			{
				if(button->isActivate())
				{
					if(button->getNameID() == "Resume")
					{
						isPauseGame = false;
						state = resume;
					}
					if(button->getNameID() == "Restart")
					{
						state = main;
						is_Restart = true;
						isPauseGame = false;
					}
					if(button->getNameID() == "Settings")
					{
						state = settings;
					}
					if(button->getNameID() == "Exit")
					{
						state = exit_confirm;
					}
				}
			}

			break;

		case PauseMenu::settings:

			for(auto button: vec_Settings)
			{
				if(button->isActivate())
				{
					if(button->getNameID() == "Back")
					{
						state = main;
					}
				}
			}

			for(auto checkBox: vec_Check_Box)
			{
				if(checkBox->isActive())
				{
					if(checkBox->getNameID() == "EffectStar")
					{
						if(checkBox->isCheck()) isEffectStar = true;
						else isEffectStar = false;
					}

					if(checkBox->getNameID() == "VideoSmothOn")
					{
						if(checkBox->isCheck())
						{
							isVideo_Smoth_On = true;
							texture->setSmoth(isVideo_Smoth_On);
						}
						else
						{
							isVideo_Smoth_On = false;
							texture->setSmoth(isVideo_Smoth_On);
						}
					}

					if(checkBox->getNameID() == "MusicOn")
					{
						if(checkBox->isCheck())
						{
							isSound_Music_On = true;
							sound->setVolMusic(sound_Vol_Music);
						}
						else
						{
							isSound_Music_On = false;
							sound->setVolMusic(0);
						}
					}

					if(checkBox->getNameID() == "EffectOn")
					{
						if(checkBox->isCheck())
						{
							isSound_Effects_On = true;
							sound->setVolEffects(sound_Vol_Effects);
						}
						else
						{
							isSound_Effects_On = false;
							sound->setVolEffects(0);
						}
					}

					if(checkBox->getNameID() == "VideoVertSyncOn")
					{
						if(checkBox->isCheck())
						{
							isVideo_VertSync_On = true;
							wnd->setVerticalSyncEnabled(true);
						}
						else
						{
							isVideo_VertSync_On = false;
							wnd->setVerticalSyncEnabled(false);
						}
					}
				}
			}
			
			for(auto scroller: vec_Settings_Scroller)
			{
				if(scroller->isActive())
				{
					if(scroller->getNameID() == "MusicVol")
					{
						sound_Vol_Music = scroller->getResult();
						sound->setVolMusic(sound_Vol_Music);
					}

					if(scroller->getNameID() == "EffectsVol")
					{
						sound_Vol_Effects = scroller->getResult();
						sound->setVolEffects(sound_Vol_Effects);
					}
					if(scroller->getNameID() == "GameSpeed")
					{
						modifier_speed = float(50+scroller->getResult())/100.f;
					}
				}
			}

			break;

		case PauseMenu::exit_confirm:

			for(auto button: vec_Exit_Confirm) 
			{
				if(button->isActivate())
				{
					if(button->getNameID() == "Windows")
					{
						wnd->close();
					}
					if(button->getNameID() == "Cancel")
					{
						state = main;
					}
					if(button->getNameID() == "MainMenu")
					{
						isPauseGame = false;
						is_GoToMainMenu = true;
					}
				}
			}

			break;
		}
	}

	void Draw()
	{
		switch (state)
		{
		case PauseMenu::main:

			for(auto button: vec_Pause_Main) 
				button->Draw();

			break;

		case PauseMenu::settings:

			for(auto button: vec_Settings) 
				button->Draw();
			for(auto checkBox: vec_Check_Box)
				checkBox->Draw();
			for(auto scroller: vec_Settings_Scroller)
				scroller->Draw();

			break;

		case PauseMenu::exit_confirm:

			for(auto button: vec_Exit_Confirm) 
				button->Draw();

			break;
		}
		wnd->draw(shpPause);
	}
	
	
	
	virtual ~PauseMenu(void){}

};