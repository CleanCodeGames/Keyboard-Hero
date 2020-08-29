#pragma once
#include <SFML\Audio.hpp>
typedef sf::SoundBuffer Buff;
typedef unsigned int uint;
using namespace std;
class Sounds
{
public:

	Buff bClickButton;
	Buff bClickError;
	Buff bKeyCapture;
	Buff bKeyMiss;
	Buff bShowScore;
	Buff bBonusDarkAct;
	Buff bBonusLifeAct;
	Buff bBonusFireAct;
	Buff bKeyCaptureBlack;
	Buff bSpiderAttack;
	Buff bXFiles;
	Buff bSpiderBang;

	Buff bBangSmall;
	Buff bBangBig;
	Buff bLaserSmall;
	Buff bLaserBig;
	Buff bBossDead1;
	Buff bBossDead2;

	sf::Sound ClickButton;
	sf::Sound ClickError;
	sf::Sound KeyCapture;
	sf::Sound KeyMiss;
	sf::Sound ShowScore;
	sf::Sound BonusDarkAct;
	sf::Sound BonusLifeAct;
	sf::Sound BonusFireAct;
	sf::Sound KeyCaptureBlack;
	sf::Sound XFiles;
	sf::Sound SpiderAttack;
	sf::Sound SpiderBang;

	sf::Sound BangSmall;
	sf::Sound BangBig;
	sf::Sound LaserSmall;
	sf::Sound LaserBig;
	sf::Sound BossDead1;
	sf::Sound BossDead2;

	sf::Music MainTheme;
	sf::Music BossTheme;
	sf::Music Creator;
	sf::Music Theme[4];

public:

	void setVolEffects(uint vol)
	{
		ClickButton.setVolume(vol);
		ClickError.setVolume(vol);
		KeyCapture.setVolume(vol);
		KeyCaptureBlack.setVolume(vol);
		KeyMiss.setVolume(vol);
		BonusDarkAct.setVolume(vol);
		BonusLifeAct.setVolume(vol);
		BonusFireAct.setVolume(vol);
		BangSmall.setVolume(vol);
		BangBig.setVolume(vol);
		LaserSmall.setVolume(vol);
		LaserBig.setVolume(vol);
		BossDead1.setVolume(vol);
		SpiderAttack.setVolume(vol);
		SpiderBang.setVolume(vol/1.5f);
		BossDead2.setVolume(vol);
	}

	void setVolMusic(uint vol)
	{
		BossTheme.setVolume(vol);
		MainTheme.setVolume(vol);
		ShowScore.setVolume(vol);
		Creator.setVolume(vol);
		for(int i = 0; i < 3; i++) 
			Theme[i].setVolume(vol);
	}

	Sounds(void)
	{
		LoadSound("ClickButton.wav", ClickButton, bClickButton);
		LoadSound("ClickError.wav", ClickError, bClickError);
		LoadSound("KeyCapture.wav", KeyCapture, bKeyCapture);
		LoadSound("KeyCaptureBlack.wav", KeyCaptureBlack, bKeyCaptureBlack);
		LoadSound("KeyMiss.wav", KeyMiss, bKeyMiss);
		LoadSound("ShowScore.wav", ShowScore, bShowScore);
		LoadSound("BonusDarkAct.wav", BonusDarkAct, bBonusDarkAct);
		LoadSound("BonusFireAct.wav", BonusFireAct, bBonusFireAct);
		LoadSound("BonusLifeAct.wav", BonusLifeAct, bBonusLifeAct);

		LoadSound("BangSmall.wav", BangSmall, bBangSmall);
		LoadSound("BangBig.wav", BangBig, bBangBig);
		LoadSound("LaserSmall.wav", LaserSmall, bLaserSmall);
		LoadSound("LaserBig.wav", LaserBig, bLaserBig);
		LoadSound("BossDead1.wav", BossDead1, bBossDead1);
		LoadSound("BossDead2.wav", BossDead2, bBossDead2);
		LoadSound("SpiderAttack.wav", SpiderAttack, bSpiderAttack);
		LoadSound("SpiderBang.wav", SpiderBang, bSpiderBang);
		SpiderBang.setPitch(1.65);

		LoadMusic("Molo Dimolo_Wait.ogg", MainTheme);
		LoadMusic("Molo Dimolo_Listen.ogg", Theme[0]);
		LoadMusic("Molo Dimolo_Dance.ogg", Theme[1]);
		LoadMusic("Molo Dimolo_Type.ogg", Theme[2]);
		LoadMusic("BonusTheme.ogg", Theme[3]);
		LoadMusic("BossTheme.ogg", BossTheme);
		LoadMusic("Creator.ogg", Creator);
	}

	void stopMusic()
	{
		MainTheme.stop();
		BossTheme.stop();
		Creator.stop();
		for(int i = 0; i < 4; i++) 
			Theme[i].stop();
	}

	~Sounds(void){}

private:

	inline void LoadSound(string file, sf::Sound& s, sf::SoundBuffer& b)
	{
		b.loadFromFile("Resources/Sounds/"+file);
		s.setBuffer(b);
	}

	inline void LoadMusic(string file, sf::Music& m)
	{
		m.openFromFile("Resources/Music/"+file);
		m.setLoop(true);
	}
};

