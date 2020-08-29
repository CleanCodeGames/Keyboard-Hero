#pragma once
#include"System.h"

class oSpecEffect : public System
{
public:

	oSpecEffect() {}
	virtual ~oSpecEffect(void) {}

	virtual void setRect(sf::IntRect rect, uint siz) = 0;
	virtual void Update() = 0;
	virtual void Scaling() = 0;
	virtual bool getKill() const = 0;
	virtual void Draw() = 0;
};

// Ёффект дл€ двух круглых шейпов

class SpecEffect_TwoCircleRotation : public oSpecEffect
{
protected:

	Shape shape[2];
	float alpha;

public:

	SpecEffect_TwoCircleRotation(v2f pos, float siz, IMG& img)
	{
		alpha = 255.f;
		for(int i = 0; i < 2; i++) 
			ConstructShape(shape[i], pos, v2f(siz,siz)/scr_1, img, false);
		shape[1].setTextureRect(sf::IntRect(shape[1].getTextureRect().width,0,-shape[1].getTextureRect().width,shape[1].getTextureRect().height));
	}

	virtual void setRect(sf::IntRect rect, uint siz)
	{
		shape[0].setTextureRect(rect);
		shape[1].setTextureRect(sf::IntRect(rect.left+siz, rect.top, rect.width-siz, rect.height));
	}

	virtual void Update()
	{
		alpha -= 0.25f * time;
		for(int i = 0; i < 2; i++) 
			shape[i].setFillColor(sf::Color(255,255,255,uint(alpha)));
		shape[0].rotate( 0.08f * time);
		shape[1].rotate(-0.08f * time);
	}

	virtual void Scaling()
	{
		for(int i = 0; i < 2; i++)
			shape[i].setScale(v2f(shape[i].getFillColor().a,shape[i].getFillColor().a)/255.f);
	}

	bool getKill() const
	{
		if(alpha < 10) return true;
		return false;
	}

	virtual void Draw()
	{
		for(int i = 0; i < 2; i++) 
			wnd->draw(shape[i]);
	}

	virtual ~SpecEffect_TwoCircleRotation(void)
	{

	}
};

// Ёффект дл€ одного шейпа. Ѕ≈« ¬–јў≈Ќ»я.
class SpecEffect_OneNoRotation : public oSpecEffect
{
protected:

	Shape shape;
	float alpha;

public:

	SpecEffect_OneNoRotation(v2f pos, float siz, IMG& img)
	{
		alpha = 255.f;
		ConstructShape(shape, pos, v2f(siz,siz)/scr_1, img, false);
	}

	virtual void setRect(sf::IntRect rect, uint siz)
	{
		shape.setTextureRect(rect);
		shape.setTextureRect(sf::IntRect(rect.left+siz, rect.top, rect.width-siz, rect.height));
	}

	virtual void Update()
	{
		alpha -= 0.25f * time;
		shape.setFillColor(sf::Color(255,255,255,uint(alpha)));
	}

	virtual void Scaling()
	{
		shape.setScale(v2f(shape.getFillColor().a,shape.getFillColor().a)/255.f);
	}

	bool getKill() const
	{
		if(alpha < 10) return true;
		return false;
	}

	virtual void Draw()
	{
		wnd->draw(shape);
	}

	virtual ~SpecEffect_OneNoRotation(void)
	{

	}
};

// Ёффект дл€ одного шейпа. — ¬–јў≈Ќ»≈ћ.
class SpecEffect_OneYesRotation : public oSpecEffect
{
protected:

	Shape shape;
	float alpha;
	short isLeft;

public:

	SpecEffect_OneYesRotation(v2f pos, float siz, IMG& img, sf::Color color) : isLeft(rand()%2)
	{
		alpha = 255.f;
		ConstructShape(shape, pos, v2f(siz,siz)/scr_1, img, color, false);
	}

	virtual void setRect(sf::IntRect rect, uint siz)
	{
		shape.setTextureRect(rect);
	}

	virtual void Update()
	{
		alpha -= 0.25f * time;
		if(isLeft == 0) shape.rotate(0.08f * time);
		else shape.rotate(-0.08f * time);
		shape.setFillColor(sf::Color(shape.getFillColor().r,shape.getFillColor().g,shape.getFillColor().b,uint(alpha)));
	}

	virtual void Scaling()
	{
		shape.setScale(v2f(shape.getFillColor().a,shape.getFillColor().a)/255.f);
	}

	bool getKill() const
	{
		if(alpha < 10) return true;
		return false;
	}

	virtual void Draw()
	{
		wnd->draw(shape);
	}

	virtual ~SpecEffect_OneYesRotation(void)
	{

	}
};