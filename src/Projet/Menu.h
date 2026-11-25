#pragma once
#include "Scene.h"
#include <vector>
#include "pch.h"

/*
RULES !

Up and Down Arrow -> Browse buttons
Enter -> Launch

While in game :
Echap -> Pause

Have fun :3

*/

class Button;

class Menu : public Scene 
{
	Button* m_Button_Catcher = nullptr;
	Button* m_Button_Hockey = nullptr;
	Button* m_Button_Tron = nullptr;

	std::vector<Button*> buttons;

	int index = 0;

	Button* selectedButton = nullptr;
public:
	void Clear() override; 

	void Init() override;
	void Update() override;

	void InitButtons();

	void ButtonSelectorManager();
};

