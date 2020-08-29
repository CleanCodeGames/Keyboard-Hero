#pragma once
#include "oKeyKillEffect.h"

class KeyKillEffectWhite : public oKeyKillEffect
{
public:

	virtual void Update()
	{
		oKeyKillEffect::Update();
		if(!isScaleEnd)
		{
			if(scale >= 1.0f) 
			{
				for(int i = 0; i < 2; i++) 
					shpBang[i].setScale(v2f(1,1));

				for(int i = 0; i < 18; i++)
				{
					vec_shpEffect1.push_back(make_shared<Shape>(Shape()));
					ConstructShape(*vec_shpEffect1.back(), shpBang[0].getPosition()/scr_1, v2f(3,3), texture->SphereWhite, true);
					vec_shpEffect2.push_back(make_shared<Shape>(Shape()));
					ConstructShape(*vec_shpEffect2.back(), shpBang[0].getPosition()/scr_1, v2f(3,3), texture->SphereWhite, true);
					vec_shpEffect2.back()->setTextureRect(sf::IntRect(128,0,-128,128));
				}
				isScaleEnd = true;
			}
		}
	}

	KeyKillEffectWhite(v2f pos, float siz) : oKeyKillEffect()
	{
		ConstructShape(shpBang[0], pos/scr_1, v2f(siz/scr_1,siz/scr_1)*1.5f, texture->BangWhite, true);
		shpBang[1] = shpBang[0];
		shpBang[1].setTextureRect(sf::IntRect(256,0,-256,256));
	}

	virtual ~KeyKillEffectWhite(void)
	{
	}
};