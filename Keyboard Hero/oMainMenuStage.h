#pragma once
#include "oButton.cpp"

class oMainMenuStage :
	public System
{
protected:

	vector<shared_ptr<oButton>> vButton;
	sf::Text text_ERROR;

public:

	virtual void Action() = 0;
	virtual void Update();
	virtual void Draw();

	oMainMenuStage(void);
	virtual ~oMainMenuStage(void);
};

