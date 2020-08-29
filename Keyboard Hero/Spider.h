#pragma once
#include"oKeyMove.h"

class Spider : public System
{
private:

	float speed;
	float timer_create;
	shared_ptr<oKeyMove> key;
	Shape shape;
	float scale;
	float scale_rate;
	float timer_dead;
	bool is_end;
	float angle;

	enum START_DIRECTION {left, right, front} dir;
	enum STATE {create, move_attack, kill} state;

public:

	Spider(v2f pos, float speed) : 
		speed(speed), 
		dir(START_DIRECTION(rand()%3)), 
		state(create),
		timer_create(rand()%1000+2500),
		timer_dead(3000),
		is_end(false),
		scale(0),
		angle(0)
	{
		scale_rate = timer_create;
		const int key_type = rand()%4;
		ConstructShape(shape, pos, v2f(11,11), texture->Spider, false);
		shape.setRotation(0);
		if (key_type == 0) key = make_shared<KeyFire>(KeyFire(getRandKeyNum(), pos / scr_1, v2f(5, 5), v2f(), "Fire"));
		if (key_type == 1) key = make_shared<KeyFrost>(KeyFrost(getRandKeyNum(), pos / scr_1, v2f(5, 5), v2f(), "Frost"));
		if (key_type == 2) key = make_shared<KeyEpic>(KeyEpic(getRandKeyNum(), pos / scr_1, v2f(5, 5), v2f(), "Epic"));
		if (key_type == 3) key = make_shared<KeyNature>(KeyNature(getRandKeyNum(), pos / scr_1, v2f(5, 5), v2f(), "Nature"));
		key->setKeyInBoss();
	}

	void Kill(float _angle) 
	{ 
		angle = _angle;
		key->setFillColor(sf::Color::Transparent); 
		state = kill; 
	}

	void End() { is_end = true; }

	bool isKill() 
	{ 
		if(state == kill) 
			return true; 
		return false;
	}

	bool isEnd() const { return is_end; }
	
	void Update()
	{
		if(state != kill) 
		{
			shape.setRotation(atan2f((scr_1*10) - shape.getPosition().y, (-scr_1*50) - shape.getPosition().x) * 180.f / PI);
			key->Update();
		}

		switch(state)
		{
		case create:

			timer_create > 0 ? timer_create -= time : timer_create = 0;
			scale = 1.f - (timer_create / scale_rate);
			shape.setScale(v2f(1.f, scale));

			if(dir != front) key->setScale(v2f(1.f, scale));
			else key->setScale(v2f(scale, 1.f));

			switch(dir)
			{
				case left : shape.move(v2f(0, 0.012*modifier_speed)*(scr_1*time)); break;
				case right: shape.move(v2f(0,-0.012*modifier_speed)*(scr_1*time)); break;
				case front: shape.move(v2f(-0.010,0*modifier_speed)*(scr_1*time)); break;
			}

			if(timer_create < 0)
			{
				state = move_attack;
				sound->SpiderAttack.play();
			}
			break;

		case move_attack:

			shape.move(v2f(cos(shape.getRotation()), sin(shape.getRotation()))*((speed*modifier_speed)*time));

			break;

		case kill:

			timer_dead -= time;
			if(timer_dead < 0)
			{
				timer_dead = 0;
				is_end = true;
			}

			if(dir == front) shape.rotate(0.77*time);
			else shape.rotate(-0.77*time);

			shape.move(v2f(cos(angle), sin(angle))*(speed*time)*1.5f);
			shape.setScale(v2f(1.f,1.f)*(timer_dead/3000));
			shape.setFillColor(sf::Color(255, 255, 255, 255*(timer_dead/3000)));
			key->setScale(shape.getScale());

			break;
		}


		key->setPostion(shape.getPosition());
	}

	void Draw()
	{
		wnd->draw(shape);
		key->Draw();
	}

	shared_ptr<oKeyMove> Key() { return key; }

	~Spider(void){}
};