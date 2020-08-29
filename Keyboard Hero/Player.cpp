#include "Player.h"


Player::Player(void) :
	name(""),
	text_Name(Player::name,*font_modeka),
	text_Score("Score: "+to_string(score),*font_modeka),
	text_Level("Level: "+to_string(level),*font_modeka),
	text_Key_Count("", *font_modeka),
	score(0),
	combo(0),
	combo_Max(0),
	text_Combo("Combo: " + to_string(combo),*font_oduda),
	timer_Show_Combo(0),
	timer_Create_Shines(0),
	is_Show_Record_Table(false),
	capture_All(0),
	capture_Fire(0),
	capture_Frost(0),
	capture_Epic(0),
	capture_Nature(0),
	capture_Percent(0),
	capture_Miss(0)
{
	shp_Combo.setTexture(&texture->Combo);
	shp_Combo.setFillColor(sf::Color(200,200,200));
	text_Name.setCharacterSize(uint(scr_1*2.5f));
	text_Name.setStyle(sf::Text::Bold);
	text_Score.setCharacterSize(uint(scr_1*2.5f));
	text_Score.setStyle(sf::Text::Bold);
	text_Level.setCharacterSize(uint(scr_1*2.5f));
	text_Level.setStyle(sf::Text::Bold);
	text_Combo.setCharacterSize(uint(scr_1*4.f));
	text_Combo.setStyle(sf::Text::Bold);
	text_Key_Count.setCharacterSize(uint(scr_1*2.5f));
	text_Key_Count.setStyle(sf::Text::Bold);
	ConstructShape(shp_Top_Bar, v2f(0,-47.5), v2f(scr_W/scr_1, 10), texture->PlayerTopBar, true);
	text_Name.setPosition(v2f(-scr_W/2 + scr_1, -scr_H/2+scr_1/2.f));
	ConstructShape(shp_Record_Table, v2f(0,0), v2f(60, 70), texture->RecordTable, true);
}

void Player::setRecord(const uint max)
{
	capture_Percent = 100 - (float(100)/max)*capture_Miss;
	ConstructText(text_Table_Level, v2f(0, -shp_Record_Table.getSize().y/2+scr_1*6), 4, sf::Color::Black, "Level: " + to_string(level), font_modeka);
	ConstructText(text_Table_Name, v2f(0, -shp_Record_Table.getSize().y/2+scr_1*12), 4, sf::Color::Black, "Player: " + name, font_modeka);
	ConstructText(text_Table_Max_Combo, v2f(0, -shp_Record_Table.getSize().y/2+scr_1*18), 4, sf::Color::Black, "Combo max: " + to_string(combo_Max), font_modeka);
	ConstructText(text_Table_Key_Capture, v2f(0, -shp_Record_Table.getSize().y/2+scr_1*24), 4, sf::Color::Black, "Capture all: " + to_string(capture_All) + "/"+ to_string(max) + "/" + to_string(capture_Percent) +"%", font_modeka);
	ConstructText(text_Table_Key_Fire, v2f(0, -shp_Record_Table.getSize().y/2+scr_1*30), 4, sf::Color::Black, "Capture fire: " + to_string(capture_Fire), font_modeka);
	ConstructText(text_Table_Key_Frost, v2f(0, -shp_Record_Table.getSize().y/2+scr_1*36), 4, sf::Color::Black, "Capture frost: " + to_string(capture_Frost), font_modeka);
	ConstructText(text_Table_Key_Epic, v2f(0, -shp_Record_Table.getSize().y/2+scr_1*42), 4, sf::Color::Black, "Capture darkness: " + to_string(capture_Epic), font_modeka);
	ConstructText(text_Table_Key_Nature, v2f(0, -shp_Record_Table.getSize().y/2+scr_1*48), 4, sf::Color::Black, "Capture life: " + to_string(capture_Nature), font_modeka);
	ConstructText(text_Table_Score, v2f(0, -shp_Record_Table.getSize().y/2+scr_1*54), 4, sf::Color::Black, "Score: " + to_string(score), font_modeka);
	
	is_Show_Record_Table = true;
}

void Player::clearTableRecord()
{
	combo = 0;
	combo_Max = 0;
	capture_All = 0;
	capture_Fire = 0;
	capture_Frost = 0;
	capture_Epic = 0;
	capture_Nature = 0;
	capture_Percent = 0;
	capture_Miss = 0;
	is_Show_Record_Table = false;
}

void Player::addCapture(sf::String type)
{
	if(type == "Fire") capture_Fire++;
	if(type == "Frost") capture_Frost++;
	if(type == "Epic") capture_Epic++;
	if(type == "Nature") capture_Nature++;
	capture_All++;
}

void Player::addCaptureMiss()
{
	clearCombo();
	capture_Miss++;
}

void Player::saveToFile()
{
	nextLevel();
	setScore(score);

	ofstream new_profile("save/"+ name +".prof");
	new_profile << name;							// Name
	new_profile << "\n"+to_string(level);			// Level
	new_profile << "\n"+to_string(score);			// Score
	new_profile.close();
}

void Player::addCombo()
{
	combo++;
	if(combo_Max < combo) 
	{
		combo_Max = combo;
	}
	if(combo >= 3) timer_Show_Combo = 5000.f;

	if(combo >= 3 && combo < 10) {
		text_Combo.setCharacterSize(scr_1*4);
		text_Combo.setString("Combo " + to_string(combo) + "!");
		text_Combo.setColor(sf::Color::Blue);
	}
	if(combo >= 10 && combo < 20) {
		text_Combo.setCharacterSize(scr_1*5);
		text_Combo.setString("Normal Combo " + to_string(combo) + "!");
		text_Combo.setColor(sf::Color::Green);
	}
	if(combo >= 20 && combo < 30) {
		text_Combo.setCharacterSize(scr_1*5.5);
		text_Combo.setString("Good Combo " + to_string(combo) + "!");
		text_Combo.setColor(sf::Color::Red);
	}
	if(combo >= 30 && combo < 40) {
		text_Combo.setCharacterSize(scr_1*6);
		text_Combo.setString("Super Combo " + to_string(combo) + "!");
		text_Combo.setColor(sf::Color::Magenta);
	}
	if(combo >= 40 && combo < 50) {
		text_Combo.setCharacterSize(scr_1*6.5);
		text_Combo.setString("Excellent Combo " + to_string(combo) + "!");
		text_Combo.setColor(sf::Color(200,255,200));
	}
	if(combo >= 50 && combo < 75) {
		text_Combo.setCharacterSize(scr_1*7);
		text_Combo.setString("Incredible Combo " + to_string(combo) + "!");
		text_Combo.setColor(sf::Color(255,170,200));
	}
	if(combo > 74) {
		text_Combo.setCharacterSize(scr_1*7.5);
		text_Combo.setString("GodLike Combo " + to_string(combo) + "!");
		text_Combo.setColor(sf::Color::Yellow);
	}
	text_Combo.setPosition(v2f(-text_Combo.getGlobalBounds().width/2.f, -scr_1*36));
	shp_Combo.setSize(v2f(text_Combo.getGlobalBounds().width*1.15f, text_Combo.getGlobalBounds().height*1.15f));
	shp_Combo.setOrigin(shp_Combo.getSize()/2.f);
	shp_Combo.setPosition(v2f(0,-scr_1*36+text_Combo.getGlobalBounds().height/1.25f));
}

void Player::clearCombo()
{
	vec_Shines.clear();
	timer_Show_Combo = 0;
	combo = 0;
}

void Player::setScore(const uint _score)
{
	score = _score;
	text_Score.setString("Score: "+to_string(score));
	text_Score.setPosition(v2f(-text_Score.getGlobalBounds().width/2, text_Name.getPosition().y));
}

void Player::addScore(const int _score)
{
	score += _score;
	text_Score.setString("Score: "+to_string(score));
	text_Score.setPosition(v2f(-text_Score.getGlobalBounds().width/2, text_Name.getPosition().y));
}

void Player::setName(const string _name)
{
	name = _name;
	text_Name.setString("Player: " + name);
}

void Player::nextLevel()
{
	if(level < LEVEL_MAX) level++;
	text_Level.setString("Level: "+to_string(level));
}

void Player::backLevel()
{
	if(level > 1) level--;
	text_Level.setString("Level: "+to_string(level));
}

void Player::setKeyCount(const uint max)
{
	capture_Percent = 100 - (float(100)/max)*capture_Miss;
	text_Key_Count.setString("Keys: " + to_string(capture_All) + "/"+ to_string(max) + "/" + to_string(capture_Percent) +"%");
	text_Key_Count.setPosition(text_Score.getPosition().x + text_Score.getGlobalBounds().width + scr_1*15, text_Score.getPosition().y);
}

void Player::Draw()
{
	timer_Show_Combo -= time;
	if(!is_Show_Record_Table)
	{
		if(timer_Show_Combo > 0) 
		{
			timer_Create_Shines += time;
			if(timer_Create_Shines > 50)
			{
				int x = rand()%static_cast<int>(shp_Combo.getSize().x)-shp_Combo.getSize().x/2.f;
				int y = rand()%static_cast<int>(shp_Combo.getSize().y)-(shp_Combo.getSize().y/2)-shp_Combo.getPosition().y;
				vec_Shines.push_back(make_shared<Shines>(Shines(v2f(x,-y))));
				timer_Create_Shines = 0;
			}
			wnd->draw(shp_Combo);
		}
	
		wnd->draw(shp_Top_Bar);
		wnd->draw(text_Name);
		wnd->draw(text_Score);
		wnd->draw(text_Level);
		wnd->draw(text_Key_Count);

		if(timer_Show_Combo > 0)
		{
			for(auto it = vec_Shines.begin(); it != vec_Shines.end();)
			{
				auto& shine = *(*it);
				if(shine.getKill()) 
				{
					it = vec_Shines.erase(it);
				}
				else
				{
					shine.Update();
					shine.Draw();
					it++;
				}
			}
			text_Combo.setColor(sf::Color(text_Combo.getColor().r, text_Combo.getColor().g, text_Combo.getColor().b, 255*(timer_Show_Combo/5000.f)));
			wnd->draw(text_Combo);
		}
	}
	else
	{
		wnd->draw(shp_Record_Table);
		wnd->draw(text_Table_Name);
		wnd->draw(text_Table_Level);
		wnd->draw(text_Table_Max_Combo);
		wnd->draw(text_Table_Score);
		wnd->draw(text_Table_Key_Capture);
		wnd->draw(text_Table_Key_Fire);
		wnd->draw(text_Table_Key_Frost);
		wnd->draw(text_Table_Key_Epic);
		wnd->draw(text_Table_Key_Nature);

	}
}

void Player::setLevel(const uint _level)
{
	if(level < LEVEL_MAX) level++;
	level = _level;
	text_Level.setString("Level: "+to_string(level));
	text_Level.setPosition(v2f(scr_W/2 - text_Level.getGlobalBounds().width - scr_1*2, text_Name.getPosition().y));
}

Player::~Player(void)
{
}
