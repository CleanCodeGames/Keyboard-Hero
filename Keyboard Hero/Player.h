#pragma once
#include "Shines.h"

class Player : public System
{
private:

	string name;

	uint level;
	uint score;
	uint combo;
	uint combo_Max;
	uint capture_All;
	uint capture_Fire;
	uint capture_Frost;
	uint capture_Epic;
	uint capture_Nature;
	uint capture_Percent;
	uint capture_Miss;

	sf::Text text_Level;
	sf::Text text_Key_Count;
	sf::Text text_Name;
	sf::Text text_Combo;
	sf::Text text_Score;

	sf::Text text_Table_Level;
	sf::Text text_Table_Name;
	sf::Text text_Table_Max_Combo;
	sf::Text text_Table_Score;
	sf::Text text_Table_Key_Capture;
	sf::Text text_Table_Key_Fire;
	sf::Text text_Table_Key_Frost;
	sf::Text text_Table_Key_Epic;
	sf::Text text_Table_Key_Nature;
	
	Shape shp_Top_Bar;
	Shape shp_Combo;
	Shape shp_Record_Table;

	vector<shared_ptr<Shines>> vec_Shines;

	float timer_Create_Shines;
	float timer_Show_Combo;

	bool is_Show_Record_Table;

private:

	static const uint LEVEL_MAX = 45;

public:

	void Draw();

public:

	void clearTableRecord();
	void addCapture(sf::String type);
	void addCaptureMiss();
	void addCombo();
	void clearCombo();
	void nextLevel();
	void backLevel();
	void setLevel(const uint _level);
	void setName(const string _name);
	void setScore(const uint _score);
	void addScore(const int _score);
	void addRank();
	void setKeyCount(const uint max);
	void setRecord(const uint max);
	void saveToFile();
	
public:

	const uint getCapturePercent() const { return capture_Percent; }
	const uint getMiss() const { return capture_Miss; }
	const string& getName() const { return name;}
	const uint& getLevel() const { return level;}
	const uint& getScore() const { return score;}
	const uint getCombo() const { return combo; }

public:

	Player(void);
	~Player(void);
};