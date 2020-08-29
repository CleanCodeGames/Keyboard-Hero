#pragma once
#include "System.h"

// Абстрактный класс портала

class oPortal : public System
{
protected:

	Shape shpPortal[2];
	Shape shpEffect[2];
	string name;
	string type;

public:

	oPortal(v2f pos, v2f siz, string name) : name(name)
	{
		for(int i = 0; i < 2; i++) ConstructShape(shpPortal[i], v2f(pos.x, pos.y-20), siz*1.15f, true);
		for(int i = 0; i < 2; i++) ConstructShape(shpEffect[i], v2f(pos.x, pos.y-20), siz*0.8f, true);
	}
	~oPortal(void){}
	virtual void Update() = 0;
	virtual void Draw() = 0;

public:

	virtual void setFillColor(const sf::Color color)
	{
		for(int i = 0; i < 2; i++)
		{
			shpPortal[i].setFillColor(color);
			shpEffect[i].setFillColor(color);
			shpPortal[i].setFillColor(color);
			shpEffect[i].setFillColor(color);
		}
	}

	virtual void setPosition(v2f pos)
	{
		for(int i = 0; i < 2; i++)
		{
			shpPortal[i].setPosition(pos);
			shpEffect[i].setPosition(pos);
		}
	}

	const string& getName() const { return name; }
	const string& getType() const {return type; }

	const v2f& getPosition() const
	{
		return shpPortal[0].getPosition();
	}

	const float getSize() const { return shpPortal[0].getSize().x; }
};

// Портал создающий символы

class PortalCreator : public oPortal
{
private:

	bool dir;
	Shape dop_effect[2];

public:

	PortalCreator(v2f pos, v2f siz, string name, bool dir) : oPortal(pos, siz, name), dir(dir)
	{
		type = "Creator";
		for(int i = 0; i < 2; i++) 
		{
			shpPortal[i].setTexture(&texture->KeyCreator);
			shpEffect[i].setTexture(&texture->Flour);
			shpEffect[i].setSize(shpPortal[i].getSize());
			shpEffect[i].setOrigin(shpEffect[i].getSize()/2.f);

			dop_effect[i].setTexture(&texture->Rainbow2);
			dop_effect[i].setSize(shpEffect[i].getSize());
			dop_effect[i].setOrigin(dop_effect[i].getSize()/2.f);
			dop_effect[i].setPosition(shpEffect[i].getPosition());
		}

		dop_effect[1].setTextureRect(sf::IntRect(128,0,-128,128));

		if(dir) shpPortal[0].setTextureRect(sf::IntRect(0,0,256,256));
		else shpPortal[0].setTextureRect(sf::IntRect(256,0,-256,256));
		shpPortal[1].setScale(v2f(0.5f, 0.5f));
		shpPortal[1].setTextureRect(sf::IntRect(256,0,-256,256));
		shpEffect[1].setTextureRect(sf::IntRect(256,0,-256,256));
		
	}

	virtual void setPosition(v2f pos)
	{
		for(int i = 0; i < 2; i++)
		{
			dop_effect[i].setPosition(pos);
			shpPortal[i].setPosition(pos);
			shpEffect[i].setPosition(pos);
		}
	}

	virtual void Update()
	{
		shpEffect[0].rotate( -0.05*time);
		shpEffect[1].rotate(  0.05*time);
		dop_effect[0].rotate( 0.07*time);
		dop_effect[1].rotate(-0.07*time);
		if(dir) 
		{
			shpPortal[0].rotate( 0.03*time);
			shpPortal[1].rotate(-0.07*time);
		}
		else
		{
			shpPortal[0].rotate(-0.03*time);
			shpPortal[1].rotate( 0.07*time);
		}
	}

	virtual void Draw()
	{
		for(int i = 0; i < 2; i++)
		{
			wnd->draw(shpPortal[i]);
			wnd->draw(shpEffect[i]);
			wnd->draw(dop_effect[i]);
		}
	}

	~PortalCreator(void){}
};

// Портал уничтожающий символы

class PortalCrematory : public oPortal
{
private:

	Shape effect[2];

public:

	PortalCrematory(v2f pos, v2f siz, string name) : oPortal(pos, siz, name)
	{
		type = "Crematory";
		for(int i = 0; i < 2; i++) 
		{
			shpPortal[i].setTexture(&texture->PortalDark);
			shpEffect[i].setTexture(&texture->PortalKeyCrematory);
			effect[i].setTexture(&texture->WaterMultipleEffect);
		}

		for(int i = 0; i < 2; i++) ConstructShape(effect[i], v2f(pos.x, pos.y-20), siz*0.7f, texture->WaterMultipleEffect, true);
		effect[1].setTextureRect(sf::IntRect(256,0,-256,256));
		shpPortal[1].setTextureRect(sf::IntRect(256,0,-256,256));
		shpEffect[1].setTextureRect(sf::IntRect(256,0,-256,256));
	}

	virtual void Update()
	{
		shpEffect[0].rotate(-0.15*time);
		shpEffect[1].rotate( 0.15*time);
		effect[0].rotate(-0.3*time);
		effect[1].rotate( 0.3*time);
		shpPortal[0].rotate( 0.03*time);
		shpPortal[1].rotate(-0.03*time);
	}

	virtual void Draw()
	{
		for(int i = 0; i < 2; i++) wnd->draw(shpPortal[i]);
		for(int i = 0; i < 2; i++) wnd->draw(shpEffect[i]);
		for(int i = 0; i < 2; i++) wnd->draw(effect[i]);
	}

	~PortalCrematory(void){}
};

// Портал тьмы первый визуальный эффект

class PortalEpic : public oPortal
{
public:

	PortalEpic(v2f pos, v2f siz, string name) : oPortal(pos, siz, name)
	{
		type = "Epic";
		for(int i = 0; i < 2; i++) 
		{
			shpPortal[i].setTexture(&texture->PortalEpic);
			shpEffect[i].setTexture(&texture->PortalEffectEpic);
		}
		shpPortal[1].setTextureRect(sf::IntRect(256,0,-256,256));
		shpEffect[1].setTextureRect(sf::IntRect(256,0,-256,256));
	}

	virtual void Update()
	{
		shpEffect[0].rotate(-0.06*time);
		shpEffect[1].rotate( 0.06*time);
		shpPortal[0].rotate( 0.03*time);
		shpPortal[1].rotate(-0.03*time);
	}

	virtual void Draw()
	{
		for(int i = 0; i < 2; i++) wnd->draw(shpPortal[i]);
		for(int i = 0; i < 2; i++) wnd->draw(shpEffect[i]);
	}

	~PortalEpic(void){}
};

// Портал огня первый визуальный эффект

class PortalFire : public oPortal
{
public:

	PortalFire(v2f pos, v2f siz, string name) : oPortal(pos, siz, name)
	{
		type = "Fire";
		for(int i = 0; i < 2; i++) 
		{
			shpPortal[i].setTexture(&texture->PortalFire);
			shpEffect[i].setTexture(&texture->PortalEffectFire);
		}
		shpPortal[1].setTextureRect(sf::IntRect(256,0,-256,256));
		shpEffect[1].setTextureRect(sf::IntRect(256,0,-256,256));
	}

	virtual void Update()
	{
		shpEffect[0].rotate(-0.06*time);
		shpEffect[1].rotate( 0.06*time);
		shpPortal[0].rotate( 0.03*time);
		shpPortal[1].rotate(-0.03*time);
	}

	virtual void Draw()
	{
		for(int i = 0; i < 2; i++) wnd->draw(shpPortal[i]);
		for(int i = 0; i < 2; i++) wnd->draw(shpEffect[i]);
	}

	~PortalFire(void){}
};

// Портал холода первый визуальный эффект

class PortalFrost : public oPortal
{
public:

	PortalFrost(v2f pos, v2f siz, string name) : oPortal(pos, siz, name)
	{
		type = "Frost";
		for(int i = 0; i < 2; i++) 
		{
			shpPortal[i].setTexture(&texture->PortalFrost);
			shpEffect[i].setTexture(&texture->PortalEffectFrost);
		}
		shpPortal[1].setTextureRect(sf::IntRect(256,0,-256,256));
		shpEffect[1].setTextureRect(sf::IntRect(256,0,-256,256));
	}

	virtual void Update()
	{
		shpEffect[0].rotate(-0.06*time);
		shpEffect[1].rotate( 0.06*time);
		shpPortal[0].rotate( 0.03*time);
		shpPortal[1].rotate(-0.03*time);
	}

	virtual void Draw()
	{
		for(int i = 0; i < 2; i++) wnd->draw(shpPortal[i]);
		for(int i = 0; i < 2; i++) wnd->draw(shpEffect[i]);
	}

	~PortalFrost(void){}
};

// Портал жизни первый визуальный эффект

class PortalNature : public oPortal
{
public:

	PortalNature(v2f pos, v2f siz, string name) : oPortal(pos, siz, name)
	{
		type = "Nature";
		for(int i = 0; i < 2; i++) {
			shpPortal[i].setTexture(&texture->PortalNature);
			shpEffect[i].setTexture(&texture->PortalEffectNature);
		}
		shpPortal[1].setTextureRect(sf::IntRect(256,0,-256,256));
		shpEffect[1].setTextureRect(sf::IntRect(256,0,-256,256));
	}

	virtual void Update()
	{
		shpEffect[0].rotate(-0.06*time);
		shpEffect[1].rotate( 0.06*time);
		shpPortal[0].rotate( 0.03*time);
		shpPortal[1].rotate(-0.03*time);
	}

	virtual void Draw()
	{
		for(int i = 0; i < 2; i++) wnd->draw(shpPortal[i]);
		for(int i = 0; i < 2; i++) wnd->draw(shpEffect[i]);
	}

	~PortalNature(void){}
};

// Портал тьмы второй визуальный эффект

class PortalTornadoEpic : public oPortal
{
public:

	PortalTornadoEpic(v2f pos, v2f siz, string name) : oPortal(pos, siz, name)
	{
		type = "Epic";
		for(int i = 0; i < 2; i++) 
		{
			shpPortal[i].setTexture(&texture->PortalEpic);
			shpEffect[i].setTexture(&texture->PortalEffectTornadoEpic);
		}
		shpPortal[1].setTextureRect(sf::IntRect(256,0,-256,256));
		shpEffect[1].setTextureRect(sf::IntRect(256,0,-256,256));
	}

	virtual void Update()
	{
		shpEffect[0].rotate(-0.06*time);
		shpEffect[1].rotate( 0.06*time);
		shpPortal[0].rotate( 0.03*time);
		shpPortal[1].rotate(-0.03*time);
	}

	virtual void Draw()
	{
		for(int i = 0; i < 2; i++) wnd->draw(shpPortal[i]);
		for(int i = 0; i < 2; i++) wnd->draw(shpEffect[i]);
	}

	~PortalTornadoEpic(void){}
};

// Портал огня второй визуальный эффект

class PortalTornadoFire : public oPortal
{
public:

	PortalTornadoFire(v2f pos, v2f siz, string name) : oPortal(pos, siz, name)
	{
		type = "Fire";
		for(int i = 0; i < 2; i++) 
		{
			shpPortal[i].setTexture(&texture->PortalFire);
			shpEffect[i].setTexture(&texture->PortalEffectTornadoFire);
		}

		shpPortal[1].setTextureRect(sf::IntRect(256,0,-256,256));
		shpEffect[1].setTextureRect(sf::IntRect(256,0,-256,256));
	}

	virtual void Update()
	{
		shpEffect[0].rotate(-0.06*time);
		shpEffect[1].rotate( 0.06*time);
		shpPortal[0].rotate( 0.03*time);
		shpPortal[1].rotate(-0.03*time);
	}

	virtual void Draw()
	{
		for(int i = 0; i < 2; i++) wnd->draw(shpPortal[i]);
		for(int i = 0; i < 2; i++) wnd->draw(shpEffect[i]);
	}

	~PortalTornadoFire(void){}
};

// Портал холода второй визуальный эффект

class PortalTornadoFrost : public oPortal
{
public:

	PortalTornadoFrost(v2f pos, v2f siz, string name) : oPortal(pos, siz, name)
	{
		type = "Frost";
		for(int i = 0; i < 2; i++) 
		{
			shpPortal[i].setTexture(&texture->PortalFrost);
			shpEffect[i].setTexture(&texture->PortalEffectTornadoFrost);
		}

		shpPortal[1].setTextureRect(sf::IntRect(256,0,-256,256));
		shpEffect[1].setTextureRect(sf::IntRect(256,0,-256,256));
	}

	virtual void Update()
	{
		shpEffect[0].rotate(-0.06*time);
		shpEffect[1].rotate( 0.06*time);
		shpPortal[0].rotate( 0.03*time);
		shpPortal[1].rotate(-0.03*time);
	}

	virtual void Draw()
	{
		for(int i = 0; i < 2; i++) wnd->draw(shpPortal[i]);
		for(int i = 0; i < 2; i++) wnd->draw(shpEffect[i]);
	}

	~PortalTornadoFrost(void){}
};

// Портал жизни второй визуальный эффект

class PortalTornadoNature : public oPortal
{
public:

	PortalTornadoNature(v2f pos, v2f siz, string name) : oPortal(pos, siz, name)
	{
		type = "Nature";
		for(int i = 0; i < 2; i++) 
		{
			shpPortal[i].setTexture(&texture->PortalNature);
			shpEffect[i].setTexture(&texture->PortalEffectTornadoNature);
		}

		shpPortal[0].setTextureRect(sf::IntRect(0,0,256,256));
		shpPortal[1].setTextureRect(sf::IntRect(256,0,-256,256));

		shpEffect[0].setTextureRect(sf::IntRect(0,0,256,256));
		shpEffect[1].setTextureRect(sf::IntRect(256,0,-256,256));
	}

	virtual void Update()
	{
		shpEffect[0].rotate(-0.06*time);
		shpEffect[1].rotate( 0.06*time);
		shpPortal[0].rotate( 0.03*time);
		shpPortal[1].rotate(-0.03*time);
	}

	virtual void Draw()
	{
		for(int i = 0; i < 2; i++) wnd->draw(shpPortal[i]);
		for(int i = 0; i < 2; i++) wnd->draw(shpEffect[i]);
	}

	~PortalTornadoNature(void){}
};

// Портал многоцветный, меняет цвет при нажатии на пробел (реализация внутри oLevel)

class PortalMulticolor : public oPortal
{
private:

	Shape shpBackType[2];
	Shape shpNextType[2];
	Shape shpGlow[2];
	sf::Text space, enter;

public:

	PortalMulticolor(v2f pos, v2f siz, string name, string _type) : oPortal(pos, siz, name)
	{
		type = _type;
		ConstructShape(shpGlow[0], v2f(pos.x, pos.y-20+siz.y/2.f)*scr_1, siz/2.75f, false);
		ConstructShape(shpGlow[1], v2f(pos.x, pos.y-20-siz.y/2.f)*scr_1, siz/2.75f, false);
		
		for(int i = 0; i < 2; i++) 
		{
			ConstructShape(shpBackType[i], v2f(pos.x, pos.y-20+siz.y/2.f)*scr_1, siz/3.f, false);
			ConstructShape(shpNextType[i], v2f(pos.x, pos.y-20-siz.y/2.f)*scr_1, siz/3.f, false);
			
			if(type == "Fire")
			{
				shpPortal[i].setTexture(&texture->PortalFire);
				shpBackType[i].setTexture(&texture->PortalNature);
				shpNextType[i].setTexture(&texture->PortalFrost);
				if(i==1){
					shpGlow[0].setTexture(&texture->BangNature);
					shpGlow[1].setTexture(&texture->BangFrost);
				}
			}
			if(type == "Frost")
			{
				shpPortal[i].setTexture(&texture->PortalFrost);
				shpBackType[i].setTexture(&texture->PortalFire);
				shpNextType[i].setTexture(&texture->PortalEpic);
				if(i==1){
					shpGlow[0].setTexture(&texture->BangFire);
					shpGlow[1].setTexture(&texture->BangEpic);
				}
			}
			if(type == "Epic")
			{
				shpPortal[i].setTexture(&texture->PortalEpic);
				shpBackType[i].setTexture(&texture->PortalFrost);
				shpNextType[i].setTexture(&texture->PortalNature);
				if(i==1){
					shpGlow[0].setTexture(&texture->BangFrost);
					shpGlow[1].setTexture(&texture->BangNature);
				}
			}
			if(type == "Nature")
			{
				shpPortal[i].setTexture(&texture->PortalNature);
				shpBackType[i].setTexture(&texture->PortalEpic);
				shpNextType[i].setTexture(&texture->PortalFire);
				if(i==1){
					shpGlow[0].setTexture(&texture->BangEpic);
					shpGlow[1].setTexture(&texture->BangFire);
				}
			}
		}
		shpBackType[1].setTextureRect(sf::IntRect(256,0,-256,256));
		shpNextType[1].setTextureRect(sf::IntRect(256,0,-256,256));

		shpGlow[1].setTextureRect(sf::IntRect(256,0,-256,256));
		shpPortal[1].setTextureRect(sf::IntRect(256,0,-256,256));
		shpEffect[0].setTexture(&texture->EffectRainbow);
		shpEffect[1].setTexture(&texture->BallRainbow);

		ConstructText(space, shpNextType[0].getPosition(), (shpNextType[0].getSize().x/3.f)/scr_1, sf::Color(255,255,255,100), "Space", font_modeka);
		ConstructText(enter, shpBackType[0].getPosition(), (shpBackType[0].getSize().x/3.f)/scr_1, sf::Color(255,255,255,100), "Enter", font_modeka);
	}

	virtual void Update()
	{
		shpEffect[0].rotate( 0.06*time);
		shpEffect[1].rotate(-0.06*time);
		shpPortal[0].rotate( 0.03*time);
		shpPortal[1].rotate(-0.03*time);
		shpGlow[0].rotate( 0.15*time);
		shpGlow[1].rotate(-0.15*time);
		shpBackType[0].rotate( 0.10*time);
		shpBackType[1].rotate(-0.10*time);
		shpNextType[0].rotate( 0.10*time);
		shpNextType[1].rotate(-0.10*time);
	}

	virtual void Draw()
	{
		for(int i = 0; i < 2; i++) wnd->draw(shpPortal[i]);
		for(int i = 0; i < 2; i++) wnd->draw(shpEffect[i]);
		for(int i = 0; i < 2; i++) wnd->draw(shpBackType[i]);
		for(int i = 0; i < 2; i++) wnd->draw(shpNextType[i]);
		for(int i = 0; i < 2; i++) wnd->draw(shpGlow[i]);
		wnd->draw(space);
		wnd->draw(enter);
	}

	void SetNextColor()
	{
		for(int i = 0; i < 2; i++) 
		{
			if(type == "Fire")
			{
				if(i==1){
					type = "Frost";
					name = "Frost";
					shpGlow[0].setTexture(&texture->BangFire);
					shpGlow[1].setTexture(&texture->BangEpic);
				}
				shpPortal[i].setTexture(&texture->PortalFrost);
				shpBackType[i].setTexture(&texture->PortalFire);
				shpNextType[i].setTexture(&texture->PortalEpic);
			}
			else if(type == "Frost")
			{
				if(i==1){ 
					type = "Epic";
					name = "Epic";
					shpGlow[0].setTexture(&texture->BangFrost);
					shpGlow[1].setTexture(&texture->BangNature);
				}
				shpPortal[i].setTexture(&texture->PortalEpic);
				shpBackType[i].setTexture(&texture->PortalFrost);
				shpNextType[i].setTexture(&texture->PortalNature);
			}
			else if(type == "Epic")
			{
				if(i==1){
					type = "Nature";
					name = "Nature";
					shpGlow[0].setTexture(&texture->BangEpic);
					shpGlow[1].setTexture(&texture->BangFire);
				}
				shpPortal[i].setTexture(&texture->PortalNature);
				shpBackType[i].setTexture(&texture->PortalEpic);
				shpNextType[i].setTexture(&texture->PortalFire);
			}
			else if(type == "Nature")
			{
				if(i==1){
					type = "Fire";
					name = "Fire";
					shpGlow[0].setTexture(&texture->BangNature);
					shpGlow[1].setTexture(&texture->BangFrost);
				}
				shpPortal[i].setTexture(&texture->PortalFire);
				shpBackType[i].setTexture(&texture->PortalNature);
				shpNextType[i].setTexture(&texture->PortalFrost);
			}
		}
	}

	void SetBackColor()
	{
		for(int i = 0; i < 2; i++) 
		{
			if(type == "Fire")
			{
				if(i==1){
					type = "Nature";
					name = "Nature";
					shpGlow[0].setTexture(&texture->BangEpic);
					shpGlow[1].setTexture(&texture->BangFire);
				}
				shpPortal[i].setTexture(&texture->PortalNature);
				shpBackType[i].setTexture(&texture->PortalEpic);
				shpNextType[i].setTexture(&texture->PortalFire);
			}
			else if(type == "Frost")
			{
				if(i==1){ 
					type = "Fire";
					name = "Fire";
					shpGlow[0].setTexture(&texture->BangNature);
					shpGlow[1].setTexture(&texture->BangFrost);
				}
				shpPortal[i].setTexture(&texture->PortalFire);
				shpBackType[i].setTexture(&texture->PortalNature);
				shpNextType[i].setTexture(&texture->PortalFrost);
			}
			else if(type == "Epic")
			{
				if(i==1){
					type = "Frost";
					name = "Frost";
					shpGlow[0].setTexture(&texture->BangFire);
					shpGlow[1].setTexture(&texture->BangEpic);
				}
				shpPortal[i].setTexture(&texture->PortalFrost);
				shpBackType[i].setTexture(&texture->PortalFire);
				shpNextType[i].setTexture(&texture->PortalEpic);
			}
			else if(type == "Nature")
			{
				if(i==1){
					type = "Epic";
					name = "Epic";
					shpGlow[0].setTexture(&texture->BangFrost);
					shpGlow[1].setTexture(&texture->BangNature);
				}
				shpPortal[i].setTexture(&texture->PortalEpic);
				shpBackType[i].setTexture(&texture->PortalFrost);
				shpNextType[i].setTexture(&texture->PortalNature);
			}
		}
	}

	~PortalMulticolor(void){}
};

// Телепорт

class PortalTeleport : public oPortal
{
private:

	struct Effect;

	bool isIN;
	vector<shared_ptr<Effect>> vec_effect;
	float timer;

	struct Effect
	{
		Shape shape[2];
		float scale;
		bool isin;

		Effect(v2f pos, v2f siz, bool is_IN) : isin(is_IN)
		{
			if(!isin) scale = 0.1f;
			else scale = 1.0f;

			for(int i = 0; i < 2; i++)
			{
				shape[i].setSize(siz);
				shape[i].setPosition(pos);
				shape[i].setOrigin(siz/2.f);
				shape[i].setTexture(&texture->TeleportEff1);
				shape[i].setScale(scale,scale);
				shape[i].setRotation(rand()%360);
			}
			shape[1].setTextureRect(sf::IntRect(256,0,-256,256));
		}

		bool getLife() const
		{
			if(scale >= 0.1f && scale <= 1.f) 
				return true;
			return false;
		}

		void Update()
		{
			if(isin) scale-=0.0003f*time;
			else scale+=0.0003f*time;

			for(int i = 0; i < 2; i++)
			{
				shape[i].setScale(scale,scale);
				shape[i].setFillColor(sf::Color(255, 255, 255, scale*255));
			}

			shape[0].rotate(0.1*time);
			shape[1].rotate(-.1*time);
		}

		void Draw()
		{
			for(int i = 0; i < 2; i++) 
				wnd->draw(shape[i]);
		}
	};

public:

	PortalTeleport(v2f pos, v2f siz, string name, bool is_IN) : oPortal(pos, siz, name), isIN(is_IN), timer(0)
	{
		type = name;
		for(int i = 0; i < 2; i++)
		{
			shpEffect[i].setTexture(&texture->TeleportEff2);
			shpPortal[i].setTexture(&texture->PortalTeleport);
			if(!isIN) 
				shpPortal[i].setFillColor(sf::Color(100,100,100));
			shpEffect[i].setScale(1.75, 1.75);
		}
		shpEffect[1].setTextureRect(sf::IntRect(256,0,-256,256));
	}

	virtual void Update()
	{
		timer += time;
		if(timer >= 333) 
		{
			timer = 0;
			vec_effect.push_back(make_shared<Effect>(Effect(shpPortal[0].getPosition(), shpPortal[0].getSize(),isIN)));
		}

		for(vector<shared_ptr<Effect>>::iterator it = vec_effect.begin(); it != vec_effect.end();)
		{
			Effect& effect = *(*it);
			if(effect.getLife()) { effect.Update(); it++; }
			else it = vec_effect.erase(it);
		}
		
		if(isIN)
		{
			shpPortal[0].rotate( 0.1*time);
			shpPortal[1].rotate( 0.12*time);
		}
		else
		{
			shpPortal[0].rotate(-0.1*time);
			shpPortal[1].rotate(-0.12*time);
		}

		shpEffect[0].rotate(-0.06*time);
		shpEffect[1].rotate( 0.06*time);
	}

	virtual void Draw()
	{
		for(int i = 0; i < 2; i++) wnd->draw(shpPortal[i]);
		for(auto effect: vec_effect) effect->Draw();
		for(int i = 0; i < 2; i++) wnd->draw(shpEffect[i]);
	}

	~PortalTeleport(void){}
};