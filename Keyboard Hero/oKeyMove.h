#pragma once
#include"System.h"
#include"oSpecEffect.h"

class oKeyMove :
	public System
{
protected:

	vector<shared_ptr<oSpecEffect>> vec_Effect;
	float timer_Effect;

	Shape shp_Char;
	Shape shape[2];
	Shape shp_Key;
	v2f speed;
	uint keyNum;

	const short dir;

	string name;
	string type;

	enum State { 
		create, move, allow, hook, kill, destroy
	} state;

public:

	const string& getType() const
	{
		return type;
	}

	void setSpeed(v2f _speed)
	{
		speed = _speed*scr_1;
	}

	void setName(const string& _name) { name = _name; }

	uint getKeyNum() { return keyNum; }
	void setKeyNum(uint num) 
	{ 
			keyNum = num;
			if (keyNum <= 7) shp_Char.setTextureRect(sf::IntRect(keyNum * 64, 0, 64, 64));
			else if (keyNum >= 8 && keyNum <= 15) shp_Char.setTextureRect(sf::IntRect((keyNum - 8) * 64, 64, 64, 64));
			else if (keyNum >= 16 && keyNum <= 23) shp_Char.setTextureRect(sf::IntRect((keyNum - 16) * 64, 128, 64, 64));
			else if (keyNum >= 24 && keyNum <= 32) shp_Char.setTextureRect(sf::IntRect((keyNum - 24) * 64, 192, 64, 64));
			else if (language == RU && (keyNum >= 46 && keyNum <= 51)) shp_Char.setTextureRect(sf::IntRect((keyNum - 44) * 64, 192, 64, 64));
	}

	v2f getSpeed() const { return speed; }

	const v2f getPosition() const { return shape[0].getPosition(); }

	bool isMove() const { if(state == move) return true; return false; }

	bool isAllow() const { if(state == allow) return true; return false; }

	bool isDestroy() const { if(state == destroy) return true; return false; }

	bool isKill() const { if(state == kill) return true; return false; }

	bool isHook() const { if(state == hook) return true; return false; }

	bool isCreate() const { if(state == create) return true; return false; }

	void setStateAllow() { state = allow; }
	
	void setStateHook(const v2f& pos) { setPostion(pos); state = hook; }
	
	void setStateKill() { state = kill; }

	void setStateMove() { state = move; shp_Key.setFillColor(sf::Color::White);}

	void setFillColor(sf::Color color)
	{
		shp_Key.setFillColor(color);
		shp_Char.setFillColor(color);
		for(int i = 0; i < 2; i++) shape[i].setFillColor(color);
	}

	virtual void Move(string bonus)
	{
		const v2f _speed = (speed*modifier_speed)*time;
		for(int i = 0; i < 2; i++) shape[i].move(_speed);

		shp_Key.move(_speed);
		shp_Char.move(_speed);
		
		if(bonus == "Frost")
		{
			timer_Effect += time;

			if(timer_Effect >= 150)
			{
				if(type == "Frost")vec_Effect.push_back(make_shared<SpecEffect_TwoCircleRotation>(SpecEffect_TwoCircleRotation(getPosition(), getSize(), texture->RingFrost)));
				if(type == "Fire")vec_Effect.push_back(make_shared<SpecEffect_TwoCircleRotation>(SpecEffect_TwoCircleRotation(getPosition(), getSize(), texture->RingFire)));
				if(type == "Epic")vec_Effect.push_back(make_shared<SpecEffect_TwoCircleRotation>(SpecEffect_TwoCircleRotation(getPosition(), getSize(), texture->RingEpic)));
				if(type == "Nature")vec_Effect.push_back(make_shared<SpecEffect_TwoCircleRotation>(SpecEffect_TwoCircleRotation(getPosition(), getSize(), texture->RingNature)));
				if(type == "Black")vec_Effect.push_back(make_shared<SpecEffect_TwoCircleRotation>(SpecEffect_TwoCircleRotation(getPosition(), getSize(), texture->RingBlack)));
				if(type == "White")vec_Effect.push_back(make_shared<SpecEffect_TwoCircleRotation>(SpecEffect_TwoCircleRotation(getPosition(), getSize(), texture->RingWhite)));
				timer_Effect = 0;
			}
		}
	}

	void setPostion(v2f pos)
	{
		for(int i = 0; i < 2; i++) 
			shape[i].setPosition(pos);
		shp_Key.setPosition(pos);
		shp_Char.setPosition(pos);
	}

	const string& getName() const { return name; }

	const float getSize() const { return shape[0].getSize().x; }

public:

	oKeyMove(uint keyNum, v2f pos, v2f siz, v2f speed, string name) : 
		keyNum(keyNum),
		state(create),
		speed(speed*scr_1),
		name(name),
		dir(rand()%2),
		timer_Effect(0)
	{
		ConstructShape(shp_Key, v2f(pos.x, pos.y-20), siz*0.6f, texture->Key, true);
		if(language == EN) ConstructShape(shp_Char, v2f(pos.x, pos.y-20), siz*0.7f, texture->Symbols_EN, sf::Color::Black, true);
		else if (language == RU) ConstructShape(shp_Char, v2f(pos.x, pos.y - 20), siz*0.7f, texture->Symbols_RU, sf::Color::Black, true);
		setKeyNum(keyNum);
		for(int i = 0; i < 2; i++) shape[i].setScale(v2f(0.1,0.1));
		shp_Key.setScale(v2f(0.1,0.1));
		shp_Char.setScale(v2f(0.1,0.1));
	}

	virtual void setScale(v2f scale)
	{
		shp_Key.setScale(scale);
		shp_Char.setScale(scale);
		for(int i = 0; i < 2; i++) 
			shape[i].setScale(scale);
	}
	
	virtual void setKeyInBoss()
	{
		state = State::move;
		for(int i = 0; i < 2; i++) 
			shape[i].setScale(v2f(1,1));
		shp_Key.setScale(v2f(1,1));
		shp_Char.setScale(v2f(1,1));
	}

	virtual void Update()
	{
		shape[0].rotate(-0.03f*time);
		shape[1].rotate( 0.03f*time);

		switch(state)
		{
		case create:
			{
				float scale = shape[0].getScale().x+(0.001f*time_in_pause);
				if(scale >= 1.0f) 
				{
					for(int i = 0; i < 2; i++) shape[i].setScale(v2f(1,1));
					shp_Key.setScale(v2f(1,1));
					shp_Char.setScale(v2f(1,1));
					state = move;
					break;
				}
				for(int i = 0; i < 2; i++) shape[i].setScale(v2f(scale,scale));
				shp_Key.setScale(v2f(scale,scale));
				shp_Char.setScale(v2f(scale,scale));
			}
			break;

		case allow:
			if(timer_Effect > 190) shp_Key.setFillColor(sf::Color::Green);
			else shp_Key.setFillColor(sf::Color::Yellow);
			break;

		case hook:
			shp_Key.setFillColor(sf::Color::Cyan);
			state = kill;
			break;

		case kill:
			{
				float scale = shape[0].getScale().x - (0.001f * time_in_pause);
				if(scale <= 0.1f) 
				{
					for(int i = 0; i < 2; i++)
					{
						shape[i].setScale(v2f(0.1,0.1));
						shape[i].setFillColor(sf::Color(255,255,255, float(scale*255)));
						shp_Key.setScale(v2f(0.1,0.1));
						shp_Char.setScale(v2f(0.1,0.1));
					}
					state = destroy;
					break;
				}
				for(int i = 0; i < 2; i++) shape[i].setScale(v2f(scale,scale));
				shp_Key.setScale(v2f(scale,scale));
				shp_Char.setScale(v2f(scale,scale));
				if(dir == 0) shp_Char.rotate(0.25*time);
				else shp_Char.rotate(-0.25*time);
			}
			break;
		default: break;
		}
	}

	virtual void Draw()
	{
		for(auto it = vec_Effect.begin(); it != vec_Effect.end();)
		{
			auto& obj = *(*it);
			if(obj.getKill()) 
				it = vec_Effect.erase(it);
			else
			{
				obj.Update();
				it++;
			}
		}

		for(auto effect: vec_Effect) effect->Draw();
		for(int i = 0; i < 2; i++) wnd->draw(shape[i]);
		wnd->draw(shp_Key);
		if(!isPauseGame) wnd->draw(shp_Char);
	}

	virtual ~oKeyMove(void)
	{
	}
};

class KeyEpic :
	public oKeyMove
{

public:

	KeyEpic(uint keyNum, v2f pos, v2f siz, v2f speed, string name) : oKeyMove(keyNum, pos, siz, speed, name)
	{
		type = "Epic";
		ConstructShape(shape[0], v2f(pos.x, pos.y-20), siz, texture->RingEpic, true);
		shape[1] = shape[0];
		shape[1].setTextureRect(sf::IntRect(256,0,-256,256));
	}

	~KeyEpic(void)
	{
	}
};

class KeyFire :
	public oKeyMove
{

public:

	KeyFire(uint keyNum, v2f pos, v2f siz, v2f speed, string name) : oKeyMove(keyNum, pos, siz, speed, name)
	{
		type = "Fire";
		ConstructShape(shape[0], v2f(pos.x, pos.y-20), siz, texture->RingFire, true);
		shape[1] = shape[0];
		shape[1].setTextureRect(sf::IntRect(256,0,-256,256));
	}

	~KeyFire(void)
	{
	}
};

class KeyFrost :
	public oKeyMove
{
public:

	KeyFrost(uint keyNum, v2f pos, v2f siz, v2f speed, string name) : oKeyMove(keyNum, pos, siz, speed, name)
	{
		type = "Frost";
		ConstructShape(shape[0], v2f(pos.x, pos.y-20), siz, texture->RingFrost, true);
		shape[1] = shape[0];
		shape[1].setTextureRect(sf::IntRect(256,0,-256,256));
		timer_Effect = 0;
	}

	~KeyFrost(void)
	{
	}
};

class KeyNature :
	public oKeyMove
{

public:

	KeyNature(uint keyNum, v2f pos, v2f siz, v2f speed, string name) : oKeyMove(keyNum, pos, siz, speed, name)
	{
		type = "Nature";
		ConstructShape(shape[0], v2f(pos.x, pos.y-20), siz, texture->RingNature, true);
		shape[1] = shape[0];
		shape[1].setTextureRect(sf::IntRect(256,0,-256,256));
	}

	~KeyNature(void)
	{
	}
};

class KeyBlack :
	public oKeyMove
{

public:

	KeyBlack(uint keyNum, v2f pos, v2f siz, v2f speed, string name) : oKeyMove(keyNum, pos, siz, speed, name)
	{
		type = "Black";
		ConstructShape(shape[0], v2f(pos.x, pos.y-20), siz, texture->RingBlack, true);
		shape[1] = shape[0];
		shape[1].setTextureRect(sf::IntRect(256,0,-256,256));
	}

	~KeyBlack(void)
	{
	}
};

class KeyWhite :
	public oKeyMove
{

public:

	KeyWhite(uint keyNum, v2f pos, v2f siz, v2f speed, string name) : oKeyMove(keyNum, pos, siz, speed, name)
	{
		type = "White";
		ConstructShape(shape[0], v2f(pos.x, pos.y-20), siz, texture->RingWhite, true);
		shape[1] = shape[0];
		shape[1].setTextureRect(sf::IntRect(256,0,-256,256));
	}

	~KeyWhite(void)
	{
	}
};