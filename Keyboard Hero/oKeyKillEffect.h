#pragma once
#include "System.h"

class oKeyKillEffect : public System
{
protected:

	vector<shared_ptr<Shape>> vec_shpEffect1, vec_shpEffect2;
	Shape shpBang[2];
	float scale;
	bool isScaleEnd;
	bool is_End;

public:

	virtual bool isEnd() const { return is_End; }
	virtual void Update()
	{
		shpBang[0].rotate(-0.12*time);
		shpBang[1].rotate( 0.12*time);

		if(!isScaleEnd)
		{
			scale += time*0.0005f;
			for(int i = 0; i < 2; i++) 
				shpBang[i].setScale(v2f(scale,scale));
		}
		else
		{
			scale -= time*0.0003f;

			for(int i = 0; i < 2; i++) 
			{
				shpBang[i].setScale(v2f(scale,scale));
				shpBang[i].setFillColor(sf::Color(255,255,255,scale*255));
			}

			int i = 0;
			for(auto effect: vec_shpEffect1) 
			{
				i++;
				effect->rotate(-0.2*time);
				const float _a = i * 20 * PI / 180;
				const float _b = 0.003*scr_1*time;
				effect->move(v2f(cosf(_a), sinf(_a))*_b);
				effect->setFillColor(sf::Color(255,255,255,scale*255));
			}
			i = 0;
			for(auto effect: vec_shpEffect2)
			{
				i++;
				effect->rotate( 0.2*time);
				const float _a = i * 20 * PI / 180;
				const float _b = 0.003*scr_1*time;
				effect->move(v2f(cosf(_a), sinf(_a))*_b);
				effect->setFillColor(sf::Color(255,255,255,scale*255));
			}

			if(scale <= 0.1f) 
			{
				for(int i = 0; i < 2; i++) 
					shpBang[i].setScale(v2f(0.1,0.1));
				is_End = true;
			}
		}
	}

	virtual void Draw()
	{
		for(int i = 0; i < 2; i++) 
			wnd->draw(shpBang[i]);

		if(isScaleEnd)
		{
			for(auto effect: vec_shpEffect1) wnd->draw(*effect);
			for(auto effect: vec_shpEffect2) wnd->draw(*effect);
		}
	}

	oKeyKillEffect()
	{
		isScaleEnd = false;
		is_End = false;
		scale = 0.1f;
		for(int i = 0; i < 2; i++) shpBang[i].setScale(v2f(scale,scale));
	}

	virtual ~oKeyKillEffect(void)
	{
	}
};