#include "oMainMenuStage.h"

oMainMenuStage::oMainMenuStage(void)
{
	//ConstructText(text_ERROR,
}

void oMainMenuStage::Update()
{
	for(auto button: vButton) 
		button->Update();
}

void oMainMenuStage::Draw()
{
	for(auto button: vButton)
		button->Draw();
}

oMainMenuStage::~oMainMenuStage(void)
{
}
