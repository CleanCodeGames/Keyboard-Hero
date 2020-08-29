#pragma once
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "System.h"
#include "MainMenu.h"

#include "Level_1.h"
#include "Level_2.h"
#include "Level_3.h"
#include "Level_4.h"
#include "Level_5.h"
#include "Level_6.h"
#include "Level_7.h"
#include "Level_8.h"
#include "Level_9.h"
#include "Level_10.h"
#include "Level_11.h"
#include "Level_12.h"
#include "Level_13.h"
#include "Level_14.h"
#include "Level_15.h"
#include "Level_16.h"
#include "Level_17.h"
#include "Level_18.h"
#include "Level_19.h"
#include "Level_20.h"
#include "Level_21.h"
#include "Level_22.h"
#include "Level_23.h"
#include "Level_24.h"
#include "Level_25.h"

#include "Level_26.h"
#include "Level_27.h"
#include "Level_28.h"
#include "Level_29.h"
#include "Level_30.h"
#include "Level_31.h"
#include "Level_32.h"
#include "Level_33.h"
#include "Level_34.h"
#include "Level_35.h"
#include "Level_36.h"
#include "Level_37.h"
#include "Level_38.h"
#include "Level_39.h"
#include "Level_40.h"
#include "Level_41.h"
#include "Level_42.h"
#include "Level_43.h"
#include "Level_44.h"
#include "Level_45.h"

#include "Level_End.h"

#include "Level_Test.h"

// bug set vert sync in game settinga

Player* oLevel::m_player;
Player* oBoss::m_player;

class Game :
	public System
{
private:

	Player player;
	vector<shared_ptr<MainMenu>> vec_mainMenu;
	vector<shared_ptr<oLevel>> vec_Level;

public:

	Game(void);
	~Game(void){}
};

