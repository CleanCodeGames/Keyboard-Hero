#pragma once
#include "Player.h"
#include "oPortal.h"
#include "oButton.h"
#include "MenuInterface_Flour.h"
#include "oBackGround.h"
#include "CheckBox.h"
#include "Scroller.h"

class MainMenu :
	public System
{
private:

	Player* player;

private:

	enum STATE { main, newProfole, loadProfile, confirm_delete, settings, exit_yes_no} state;

	vector<shared_ptr<oBackGround>> vBackGround;

	Shape EnterText;
	Shape EnterLine;
	Shape SFML;
	Logo_Main logo_Main;

	sf::Text text_New_Profile;
	sf::Text text_Confirm_Delete_Profile;
	sf::Text text_Need_Delete_Profile;
	sf::Text text_Not_Load_Profiles;
	sf::Text text_Need_Picked_Profile;
	sf::Text text_Enter_Your_Name;
	sf::Text text_Need_Rename;
	sf::Text text_Quit_Game;
	sf::Text text_Keyboard_Layout;

	bool is_Need_Delete;
	bool is_Not_Saves;
	bool is_Need_Picked;
	bool is_Need_Enter_Name;
	bool is_Need_Rename;

	string str_New_Profile;
	string str_picked_profile;
	vector<shared_ptr<oMenuInterface>> vec_MainMenu_Ince;

	vector<shared_ptr<oButton>> vec_Button_Main;
	vector<shared_ptr<oButton>> vec_Button_New_Profile;
	vector<shared_ptr<oButton>> vec_Button_Load_Profile;
	vector<shared_ptr<oButton>> vec_Button_Settings;
	vector<shared_ptr<oButton>> vec_Button_Exit_Yes_No;
	vector<shared_ptr<oButton>> vec_Button_Load_Prof_List_Elem;
	vector<shared_ptr<oButton>> vec_Button_Yes_No_Delete_Profile;

	vector<shared_ptr<CheckBox>> vec_Check_Box;
	vector<shared_ptr<Scroller>> vec_Settings_Scroller;
	vector<shared_ptr<oPortal>> vec_Portal;

	bool isCanEnterText;

private:

	inline void ClearErrorText();
	inline void TransperentLine();
	inline void CreateLoadProfMenu();
	inline void CreateNewProf();
	inline void EnterTextInEnterLine();

public:

	void setStateMain();
	void Update();
	void Draw();
	void Action();

	MainMenu(Player& player);
	~MainMenu(void){}
};

