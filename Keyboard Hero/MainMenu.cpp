#include "MainMenu.h"

MainMenu::MainMenu(Player& player) :
	player(&player),
	state(main),
	isCanEnterText(false),
	str_New_Profile(""),
	is_Need_Delete(false),
	is_Not_Saves(false),
	is_Need_Picked(false),
	is_Need_Enter_Name(false)
{	
	ConstructShape(EnterText, v2f(0,-9), v2f(25, 4), texture->EnterText, true);
	ConstructShape(EnterLine, v2f(-12,-9), v2f(0.3,3), sf::Color::Black, true);
	ConstructText(text_New_Profile, EnterText.getPosition() - (EnterText.getSize()/2.f), 3.0, sf::Color::Black, "", font_modeka);
	ConstructText(text_Need_Delete_Profile, v2f(0, -13.f*scr_1), 3.0, sf::Color::Red, "Delete, or load player.", font_modeka);
	ConstructText(text_Not_Load_Profiles, v2f(0, -13.f*scr_1), 3.0, sf::Color::Red, "Saves absent.", font_modeka);
	ConstructText(text_Need_Picked_Profile, v2f(0, -13.f*scr_1), 3.0, sf::Color::Red, "Profile is not selected.", font_modeka);
	ConstructText(text_Need_Rename, v2f(0, -13.f*scr_1), 3.0, sf::Color::Red, "Profile with this name already exists.", font_modeka);
	ConstructText(text_Confirm_Delete_Profile, v2f(0,-13.f*scr_1), 3.0, sf::Color::Red, "", font_modeka);
	ConstructText(text_Enter_Your_Name, v2f(0, -13.f*scr_1), 3.0, sf::Color::Red, "Enter your name.", font_modeka);
	ConstructText(text_Quit_Game, v2f(0, -10.f*scr_1), 3.0, sf::Color::Red, "Quit game?", font_modeka);
	if (language == EN) ConstructText(text_Keyboard_Layout, v2f(0, 21 * scr_1), 3, sf::Color::Green, "Layout - EN.", font_modeka);
	if (language == RU) ConstructText(text_Keyboard_Layout, v2f(0, 21 * scr_1), 3, sf::Color::Green, "Layout - RU.", font_modeka);
	vec_MainMenu_Ince.push_back(make_shared<MenuInterface_Flour>(MenuInterface_Flour()));
	ConstructShape(SFML, v2f(-45,45), v2f(25,7.5), texture->SFML, true);
	
	vec_Button_Main.push_back(make_shared<Button_Float>(Button_Float(v2f(0,-9), v2f(24.f,5.f), texture->Button, "New Player", "NewPlayer")));
	vec_Button_Main.push_back(make_shared<Button_Float>(Button_Float(v2f(0,-3), v2f(24.f,5.f), texture->Button, "Load Player", "LoadPlayer")));
	vec_Button_Main.push_back(make_shared<Button_Float>(Button_Float(v2f(0, 3), v2f(24.f,5.f), texture->Button, "Settings", "Settings")));
	vec_Button_Main.push_back(make_shared<Button_Float>(Button_Float(v2f(0, 9), v2f(24.f,5.f), texture->Button, "Exit", "Exit")));

	vec_Button_Main.push_back(make_shared<Button_Picked>(Button_Picked(v2f(7, 16), v2f(6, 6), texture->Button, "RU", "RU")));
	vec_Button_Main.push_back(make_shared<Button_Picked>(Button_Picked(v2f(-7, 16), v2f(6, 6), texture->Button, "EN", "EN")));

	vec_Button_New_Profile.push_back(make_shared<Button_YN>(Button_YN(v2f(-8,-3), v2f(15,5), texture->Button, "Create","Yes")));
	vec_Button_New_Profile.push_back(make_shared<Button_YN>(Button_YN(v2f(8,-3), v2f(15,5), texture->Button, "Cancel","No")));
	vec_Button_Exit_Yes_No.push_back(make_shared<Button_YN>(Button_YN(v2f(-8,0), v2f(15,5), texture->Button, "Exit", "Exit")));
	vec_Button_Exit_Yes_No.push_back(make_shared<Button_YN>(Button_YN(v2f(8,0), v2f(15,5), texture->Button, "Cancel", "Cancel")));
	vec_Button_Yes_No_Delete_Profile.push_back(make_shared<Button_YN>(Button_YN(v2f(-8,0), v2f(15,5), texture->Button, "Delete", "Delete")));
	vec_Button_Yes_No_Delete_Profile.push_back(make_shared<Button_YN>(Button_YN(v2f(8,0), v2f(15,5), texture->Button, "Cancel", "Cancel")));
	vec_Button_Settings.push_back(make_shared<Button_YN>(Button_YN(v2f(0,15), v2f(15,5), texture->Button, "OK", "Back")));

	vec_Portal.push_back(make_shared<PortalFire>(PortalFire(v2f(-35,-10), v2f(15,15),"")));
	vec_Portal.push_back(make_shared<PortalNature>(PortalNature(v2f(-40,10), v2f(15,15),"")));
	vec_Portal.push_back(make_shared<PortalFrost>(PortalFrost(v2f(-45,30), v2f(15,15),"")));
	vec_Portal.push_back(make_shared<PortalEpic>(PortalEpic(v2f(-35,50), v2f(15,15),"")));
	vec_Portal.push_back(make_shared<PortalTornadoFire>(PortalTornadoFire(v2f(35,-10), v2f(15,15),"")));
	vec_Portal.push_back(make_shared<PortalTornadoNature>(PortalTornadoNature(v2f(40,10), v2f(15,15),"")));
	vec_Portal.push_back(make_shared<PortalTornadoFrost>(PortalTornadoFrost(v2f(45,30), v2f(15,15),"")));
	vec_Portal.push_back(make_shared<PortalTornadoEpic>(PortalTornadoEpic(v2f(35,50), v2f(15,15),"")));
	vec_Portal.push_back(make_shared<PortalCrematory>(PortalCrematory(v2f(0,-20), v2f(15,15),"")));

	vec_Check_Box.push_back(make_shared<CheckBox>(CheckBox(v2f(-25,-8), isEffectStar, "EffectStar", "Effect Star."))),
	vec_Check_Box.push_back(make_shared<CheckBox>(CheckBox(v2f(-25, -4), isVideo_Smoth_On, "VideoSmothOn", "Set smoth.")));
	vec_Check_Box.push_back(make_shared<CheckBox>(CheckBox(v2f(-25, 0), isVideo_VertSync_On, "VideoVertSyncOn", "Set vertical sync.")));
	vec_Check_Box.push_back(make_shared<CheckBox>(CheckBox(v2f(-25, 4), isSound_Music_On, "MusicOn", "Play music.")));
	vec_Check_Box.push_back(make_shared<CheckBox>(CheckBox(v2f(-25, 8), isSound_Effects_On, "EffectOn", "Play sound effects.")));

	vec_Settings_Scroller.push_back(make_shared<Scroller>(Scroller(v2f(12.5, -6), sound_Vol_Music, "MusicVol", "Music Volume.")));
	vec_Settings_Scroller.push_back(make_shared<Scroller>(Scroller(v2f(12.5,  0), sound_Vol_Effects, "EffectsVol", "Effects Volume.")));
	vec_Settings_Scroller.push_back(make_shared<Scroller>(Scroller(v2f(12.5, 6), float(modifier_speed*100)-50, "GameSpeed", "Game Speed.")));
	vBackGround.push_back(make_shared<BackGround_L7>(BackGround_L7()));
}

void MainMenu::setStateMain()
{
	state = main;
}

void MainMenu::Action()
{
	switch(state)
	{
		case MainMenu::main:
			for(auto button: vec_Button_Main) 
			{
				if(button->isActivate())
				{
					if(button->getNameID() == "NewPlayer")
					{
						ClearErrorText();
						float count = 0;
						WIN32_FIND_DATA FindFileData;
						HANDLE hf;
						hf = FindFirstFile("Save/*.prof", &FindFileData);
						if(hf != INVALID_HANDLE_VALUE) 
							do count++; 
						while(FindNextFile(hf, &FindFileData) != 0); 
						FindClose(hf);

						if(count > 4)
						{
							is_Need_Delete = true;
							sound->ClickError.play();
						}
						else
						{
							state = newProfole;
							isCanEnterText = true;
						}
					}

					if(button->getNameID() == "LoadPlayer")
					{
						ClearErrorText();
						CreateLoadProfMenu();
						state = loadProfile;
					}

					if(button->getNameID() == "Settings")
					{
						ClearErrorText();
						state = settings;
					}

					if(button->getNameID() == "Exit")
					{
						ClearErrorText();
						state = exit_yes_no;
					}
					if (button->getNameID() == "EN")
					{
						language = EN;
						text_Keyboard_Layout.setString("Layout - EN.");
					}
					if (button->getNameID() == "RU")
					{
						language = RU;
						text_Keyboard_Layout.setString("Layout - RU.");
					}
				}
			}
			break;

		case MainMenu::newProfole:
			{
				EnterTextInEnterLine();	// Ввод текста имени нового профиля

				// Создаём новый профиль
				for(auto button: vec_Button_New_Profile)
				{
					oButton& b = *button;
					if(b.isActivate())
					{
						if(b.getNameID() == "Yes")
						{
							ClearErrorText();
							if(!str_New_Profile.empty())
							{
								WIN32_FIND_DATA FindFileData;
								HANDLE hf;
								hf = FindFirstFile("Save/*.prof", &FindFileData);
								if(hf != INVALID_HANDLE_VALUE)
								{
								    do
									{
										ifstream file ("Save/"+string(FindFileData.cFileName));			// Обращаемся к файлу
										string str_fname = FindFileData.cFileName;						// Заносим в строку название файла
										for(int i = 0; i < 5; i++) 
											str_fname.erase(str_fname.end()-1);	// Удаляем разрешение .prof из названия
										
										if(strcmpi(str_fname.c_str(), str_New_Profile.c_str()) == 0)
										{
											is_Need_Rename = true;
										}
										if(file.is_open()) 
											file.close();
									}
									while(FindNextFile(hf, &FindFileData) != 0); FindClose(hf);
								}
								if(!is_Need_Rename)
								{
									CreateNewProf();
									sound->MainTheme.stop();
									gState = game;
								}
								else
								{
									sound->ClickError.play();
								}
							}
							else
							{
								is_Need_Enter_Name = true;
								sound->ClickError.play();
							}
						}
							

						// Возвращаемся в меню и обнуляем строку с текстом
						if(b.getNameID() == "No")
						{
							ClearErrorText();
							str_New_Profile.clear();
							text_New_Profile.setString(str_New_Profile);
							EnterLine.setPosition(text_New_Profile.getPosition().x + text_New_Profile.getGlobalBounds().width + (0.3f*scr_1), -9*scr_1);
							state = main;
						}
					}
				}
			}
			break;

		case MainMenu::loadProfile:
			{
				// Считываем данные файла.prof при нажатии по спрайту
				for(auto load_elem: vec_Button_Load_Prof_List_Elem)
				{
					if(load_elem->isActivate())
					{
						is_Need_Picked = false;
						str_picked_profile = load_elem->getNameID();
						ifstream file("Save/"+str_picked_profile+".prof");

						if(str_picked_profile == load_elem->getNameID()) 
							load_elem->setFillColor(sf::Color::Yellow);
						else load_elem->setFillColor(sf::Color::White);

						uint countLine = 0;
						if (file.is_open())
						{
							while (file.good())
							{
								countLine++;
								string str_file_line;
								getline(file,str_file_line);
								if(countLine == 1) player->setName(str_file_line);			// Name
								if(countLine == 2) player->setLevel(stoi(str_file_line));	// Level
								if(countLine == 3) player->setScore(stoi(str_file_line));	// Score
							}
						}
						file.close();
					}
				}

				for(auto button: vec_Button_Load_Profile)
				{
					if(button->isActivate())
					{
						if(button->getNameID() == "Load")
						{
							ClearErrorText();
							if(str_picked_profile != "")
							{
								gState = game;
								sound->MainTheme.stop();
							}
							else
							{
								sound->ClickError.play();
								is_Need_Picked = true;
							}
						}

						if(button->getNameID() == "Cancel")
						{
							ClearErrorText();
							state = main;
						}

						if(button->getNameID() == "DeleteProfile")
						{
							ClearErrorText();
							if(str_picked_profile == "")
							{
								sound->ClickError.play();
								is_Need_Picked = true;
							}
							else
							{
								text_Confirm_Delete_Profile.setString(L"Delete player " + sf::String(str_picked_profile) + " ?");
								text_Confirm_Delete_Profile.setPosition(v2f(-text_Confirm_Delete_Profile.getGlobalBounds().width/2, -(text_Confirm_Delete_Profile.getGlobalBounds().height/2+scr_1*6)));
								state = confirm_delete;
							}
						}
					}
				}
			}
			break;

		case MainMenu::confirm_delete:
			{
				for(auto button: vec_Button_Yes_No_Delete_Profile)
				{
					if(button->isActivate())
					{
						if(button->getNameID() == "Delete")
						{
							ClearErrorText();
							for(auto load_elem: vec_Button_Load_Prof_List_Elem)
							{
								if(str_picked_profile == load_elem->getNameID()) 
								{
									string str = "Save/" + str_picked_profile +".prof";
									const char* file = str.c_str();
									remove(file);
									str_picked_profile.clear();
								}
							}
							CreateLoadProfMenu();
							state = loadProfile;
							is_Need_Delete = false;
							break;
						}

						if(button->getNameID() == "Cancel")
						{
							ClearErrorText();
							state = loadProfile;
						}
					}
				}
			}
			break;

		case MainMenu::settings:
			for(auto button: vec_Button_Settings)
			{
				if(button->isActivate())
				{
					if(button->getNameID() == "Back")
					{
						ClearErrorText();
						state = main;
					}
				}
			}
			for(auto checkBox: vec_Check_Box)
			{
				if(checkBox->isActive())
				{
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

					if(checkBox->getNameID() == "EffectStar")
					{
						if(checkBox->isCheck()) isEffectStar = true;
						else isEffectStar = false;
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

		case MainMenu::exit_yes_no:
			{
				for(auto button: vec_Button_Exit_Yes_No)
				{
					
					if(button->isActivate())
					{
						if(button->getNameID() == "Exit")
						{
							ClearErrorText();
							wnd->close();
						}
						if(button->getNameID() == "Cancel")
						{
							ClearErrorText();
							state = main;
						}
					}
				}
			}
			break;
	}
}

void MainMenu::Update()
{
	if(sound->MainTheme.getStatus() != sf::Music::Status::Playing) sound->MainTheme.play();
	for(auto bg: vBackGround) bg->Update();
	for(auto inface: vec_MainMenu_Ince) inface->Update();

	switch (state)
	{
		case MainMenu::main:
			{
				for(auto button: vec_Button_Main)
				{
					if(is_Need_Delete && button->getNameID() == "NewPlayer") button->setFillColor(sf::Color::Red);
					else button->setFillColor(sf::Color::White);
					button->Update();
				}
				logo_Main.Update();
			}
			break;
			
		case MainMenu::newProfole:
			{
				TransperentLine();
				for(auto button: vec_Button_New_Profile)
				{
					button->Update();
				}
			}
			break;

		case MainMenu::loadProfile:
			for(auto load_elem: vec_Button_Load_Prof_List_Elem)
			{
				load_elem->Update();
				if(str_picked_profile == load_elem->getNameID()) 
					load_elem->setFillColor(sf::Color::Yellow);
				else load_elem->setFillColor(sf::Color::White);
			}
			for(auto button: vec_Button_Load_Profile)
				button->Update();
			break;

		case MainMenu::confirm_delete:
			{
				for(auto button: vec_Button_Yes_No_Delete_Profile)
				{
					button->Update();
				}
			}
			break;

		case MainMenu::settings:
			for(auto button: vec_Button_Settings)
				button->Update();
			break;

		case MainMenu::exit_yes_no:
			{
				for(auto button: vec_Button_Exit_Yes_No)
				{
					button->Update();
				}
			}
			break;
	}

	for(auto portal: vec_Portal)
	{
		portal->Update();
	}
}

void MainMenu::ClearErrorText()
{
	is_Need_Delete = false;
	is_Not_Saves = false;
	is_Need_Picked = false;
	is_Need_Enter_Name = false;
	is_Need_Rename = false;
}

void MainMenu::EnterTextInEnterLine()
{
	if(event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == Key::LShift || event.key.code == Key::RShift) 
			isShift = true;

		if(EnterText.getSize().x >= text_New_Profile.getGlobalBounds().width/0.9)
		{
			if(event.key.code >= 0 && event.key.code < 26)	// A-Z
			{
				if(!isShift) str_New_Profile += string(1, 'a' + uint(event.key.code));
				else str_New_Profile += string(1, 'A' + uint(event.key.code));
			    text_New_Profile.setString(str_New_Profile);
			}
			if(event.key.code > 25 && event.key.code < 36)	// 0-9
			{
				str_New_Profile += to_string(event.key.code - 26);
				text_New_Profile.setString(str_New_Profile);
			}
		}
		if(event.key.code == Key::BackSpace)
		{
			if(!str_New_Profile.empty()) str_New_Profile.erase(str_New_Profile.end()-1);
			text_New_Profile.setString(str_New_Profile);
		}
		EnterLine.setPosition(text_New_Profile.getPosition().x + text_New_Profile.getGlobalBounds().width + (0.3f*scr_1), -9*scr_1); 
	}

	if(event.type == sf::Event::KeyReleased)
	{
		if(event.key.code == Key::LShift || event.key.code == Key::RShift) 
			isShift = false;
	}
}

void MainMenu::CreateNewProf()
{
	if(!str_New_Profile.empty())
	{
		ofstream new_profile("save/"+ str_New_Profile +".prof");
		new_profile << str_New_Profile;	// Name
		new_profile << "\n1";			// Level
		new_profile << "\n0";			// Score
		new_profile.close();
	}
	player->setLevel(1);
	player->setScore(0);
	player->setName(str_New_Profile);
}

void MainMenu::CreateLoadProfMenu()
{
	vec_Button_Load_Prof_List_Elem.clear();
	vec_Button_Load_Profile.clear();

	float count = 0.f;
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	hf = FindFirstFile("Save/*.prof", &FindFileData);
	if(hf != INVALID_HANDLE_VALUE)
	{
	    do
		{
			count++;
			if(count > 5) { count--; break; }								// Если файлов загрузки больше 5, то прекращаем считывание
			ifstream file ("Save/"+string(FindFileData.cFileName));			// Обращаемся к файлу
			string str_fname = FindFileData.cFileName;						// Заносим в строку название файла
			for(int i = 0; i < 5; i++) str_fname.erase(str_fname.end()-1);	// Удаляем разрешение .prof из названия
			vec_Button_Load_Prof_List_Elem.push_back(make_shared<Button_Picked>(Button_Picked(v2f(0,(logo_Main.shape.getPosition().y/scr_1) + 7 + (6 * count)), v2f(30,5), texture->Button, str_fname,str_fname)));
			if(file.is_open()) file.close();
		}
		while(FindNextFile(hf, &FindFileData) != 0); FindClose(hf);

		count /= 2;
		for(auto load_elem: vec_Button_Load_Prof_List_Elem)
		{
			count--;
			if(load_elem == vec_Button_Load_Prof_List_Elem.back())
			{
				vec_Button_Load_Profile.push_back(make_shared<Button_YN>(Button_YN(v2f(-8, -6*count+8), v2f(15,5), texture->Button, "Load", L"Load")));
				vec_Button_Load_Profile.push_back(make_shared<Button_YN>(Button_YN(v2f(8, -6*count+8), v2f(15,5), texture->Button, "Cancel", L"Cancel")));
				vec_Button_Load_Profile.push_back(make_shared<Button_YN>(Button_YN(v2f(0, -6*count+14), v2f(15,5), texture->Button, "Delete", L"DeleteProfile")));
			}
		}
		is_Not_Saves = false;
	}
	else
	{
		is_Not_Saves = true;
		vec_Button_Load_Profile.push_back(make_shared<Button_YN>(Button_YN(v2f(0,(logo_Main.shape.getPosition().y/scr_1) + 16),  v2f(15,5), texture->Button, "Back", L"Cancel")));
	}
}

void MainMenu::TransperentLine()
{
	static float timer = 0;
	static bool isTransparent = false;
	timer += time;
	if(timer >= 500)
	{
		isTransparent ? EnterLine.setFillColor(sf::Color::Transparent) : EnterLine.setFillColor(sf::Color::Black);
		timer = 0;
		isTransparent = !isTransparent;
	}
}

void MainMenu::Draw()
{
	for(auto bg: vBackGround) bg->Draw();
	for(auto inface: vec_MainMenu_Ince) inface->Draw();
	switch (state)
	{
		case MainMenu::main:
			{
				logo_Main.Draw();
				for(auto button: vec_Button_Main)
				{
					button->Draw();
				}
				if(is_Need_Delete) wnd->draw(text_Need_Delete_Profile);
				wnd->draw(text_Keyboard_Layout);
			}
			break;

		case MainMenu::newProfole:
			{
				wnd->draw(EnterText);
				wnd->draw(EnterLine);
				wnd->draw(text_New_Profile);
				for(auto button: vec_Button_New_Profile)
				{
					button->Draw();
				}
				if(is_Need_Enter_Name) wnd->draw(text_Enter_Your_Name);
				if(is_Need_Rename) wnd->draw(text_Need_Rename);
			}
			break;

		case MainMenu::loadProfile:
			{
				for(auto load_elem: vec_Button_Load_Prof_List_Elem)
				{
					load_elem->Draw();
				}
				for(auto button: vec_Button_Load_Profile)
				{
					button->Draw();
				}
				if(is_Not_Saves) wnd->draw(text_Not_Load_Profiles);
				if(is_Need_Picked) wnd->draw(text_Need_Picked_Profile);
			}
			break;

		case MainMenu::confirm_delete:
			{
				for(auto button: vec_Button_Yes_No_Delete_Profile)
				{
					wnd->draw(text_Confirm_Delete_Profile);
					button->Draw();
				}
			}
			break;

		case MainMenu::settings:
			{
				for(auto button: vec_Button_Settings)
					button->Draw();
				for(auto checkBox: vec_Check_Box)
					checkBox->Draw();
				for(auto scroller: vec_Settings_Scroller)
					scroller->Draw();
			}
			break;

		case MainMenu::exit_yes_no:
			{
				for(auto button: vec_Button_Exit_Yes_No)
				{
					button->Draw();
				}
				wnd->draw(text_Quit_Game);
			}
			break;
	}
	
	for(auto portal: vec_Portal)
	{
		portal->Draw();
	}

	wnd->draw(SFML);
}
