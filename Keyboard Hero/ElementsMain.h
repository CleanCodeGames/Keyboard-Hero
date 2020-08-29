#pragma once
#include "oButton.h"
class ElementsMain : public System
{
private:

	bool is_Need_Del;

	vector<shared_ptr<oButton>> vec_button;
	sf::Text text;

public:

	ElementsMain(void) : is_Need_Del(false)
	{
		IMG& img = texture->Button;
		const v2f& size = v2f(24.f,5.f);
		vec_button.push_back(make_shared<Button_Float>(Button_Float(v2f(0,-9), size, img, "New Player", "NewPlayer")));
		vec_button.push_back(make_shared<Button_Float>(Button_Float(v2f(0,-3), size, img, "Load Player", "LoadProfile")));
		vec_button.push_back(make_shared<Button_Float>(Button_Float(v2f(0, 3), size, img, "Settings", "Settings")));
		vec_button.push_back(make_shared<Button_Float>(Button_Float(v2f(0, 9), size, img, "Exit", "Exit")));
	}

	void Action()
	{
		for(auto button: vec_button) 
			{
				if(button->isActivate())
				{
					if(button->getNameID() == "NewPlayer")
					{
						is_Need_Del = false;

						float count = 0;
						WIN32_FIND_DATA FindFileData;
						HANDLE hf;
						hf = FindFirstFile("Save/*.prof", &FindFileData);

						if(hf != INVALID_HANDLE_VALUE) do count++; while(FindNextFile(hf, &FindFileData) != 0); 
						FindClose(hf);

						if(count > 4)
						{
							is_Need_Del = true;
							sound->ClickError.play();
						}
						else
						{
							state = newProfole;
							isCanEnterText = true;
						}
					}

					if(button->getNameID() == "LoadProfile")
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
				}
			}
	}

	~ElementsMain(void)
	{
	}
};