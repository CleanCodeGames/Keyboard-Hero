#pragma once
#include "Texture.h"
#include "Sounds.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <memory>
#define PI 3.1415

typedef unsigned int uint;
typedef sf::Vector2f v2f;
typedef sf::Vector2i v2i;
typedef sf::Keyboard Key;
typedef sf::RectangleShape Shape;

class System
{
public:

	System(void* init);
	System(void);
	static void SystemTime();
	static void SystemCursor();

	static void ConstructShape(Shape& shp, v2f pos, v2f siz, IMG& png, const bool perc_pos);
	static void ConstructShape(Shape& shp, v2f pos, v2f siz, const bool perc_pos);
	static void ConstructShape(Shape& shp, v2f pos, v2f siz, IMG& png, sf::Color col, const bool perc_pos);
	static void ConstructShape(Shape& shp, v2f pos, v2f siz, sf::Color col, const bool perc_pos);

	static void ConstructText(sf::Text& text, v2f pos, float siz, sf::Color col, sf::String str, sf::Font* font);

public:

	static sf::RenderWindow* wnd;
	static sf::Clock clock;
	static sf::Event event;
	static sf::View cam;
	static sf::Font* font_oduda, *font_lines, *font_modeka;

	static float time;
	static float modifier_speed;
	static float time_in_pause;
	static int scr_W;
	static int scr_H;
	static float scr_1;
	static float scr_1w;
	static v2f cam_p;
	static v2f cur_p;
	static Texture* texture;
	static Sounds* sound;
	static enum GSTATE {main_menu, game} gState;
	static enum LANGUAGE { EN, RU } language;
	static bool isPauseGame;
	static bool isShift;
	static float timer_Star2_sEff;
	static bool isEffectStar;

	static bool isSound_Music_On;
	static bool isSound_Effects_On;
	static bool isVideo_Smoth_On;
	static bool isVideo_VertSync_On;
	static uint sound_Vol_Music;
	static uint sound_Vol_Effects;

public:

	uint getRandKeyNum();
	static float getDist(v2f p1, v2f p2);
	static sf::FloatRect getVisible();
	static v2f NormalizePosition(v2f pos, float dist, float angle);

};