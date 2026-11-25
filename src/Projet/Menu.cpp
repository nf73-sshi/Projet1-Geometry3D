#include "pch.h"
#include "Menu.h"
#include "Button.h"
#include "App.h"

void Menu::Init()
{
	index = 0;

	m_Button_Catcher = nullptr;
	m_Button_Hockey = nullptr;
	m_Button_Tron = nullptr;

	InitButtons();

	sr::Camera* pCam = App::GetCamera();
	pCam->SetPosition({0.f, 0.f, -100.f });
	pCam->SetRotation({ 0.0f, 0.0f, 0.0f });
}

void Menu::Clear()
{
	buttons.clear();
}

void Menu::Update()
{
	Scene::Update();

	App::Get()->GetSceneManager().GetCurrentScene()->DrawText(L"PartyGam :3", { SCREEN_WIDTH * 0.43f, SCREEN_HEIGHT * 0.15f }, gce::Color(255, 50, 255, 255));

	ButtonSelectorManager();
}

void Menu::InitButtons()
{
	float offsetX = 75.f;

	m_Button_Catcher = new Button(L"Catcher", { 0.0f, 6.f }, { SCREEN_WIDTH * 0.5f - offsetX, SCREEN_HEIGHT * 0.4f }, 30, 15);
	m_Button_Catcher->selected = true;

	m_Button_Hockey = new Button(L"Shuffle", { 0.0f, -12.f }, { SCREEN_WIDTH * 0.5f - offsetX, SCREEN_HEIGHT * 0.6f }, 30, 15);
	m_Button_Tron = new Button(L"Tron", { 0.0f, -30.f }, { SCREEN_WIDTH * 0.5f - offsetX + 15.f, SCREEN_HEIGHT * 0.825f }, 30, 15);

	buttons.push_back(m_Button_Catcher);
	selectedButton = m_Button_Catcher;

	buttons.push_back(m_Button_Hockey);
	buttons.push_back(m_Button_Tron);

	Add(m_Button_Catcher);
	Add(m_Button_Hockey);
	Add(m_Button_Tron);
}

void Menu::ButtonSelectorManager()
{
	if (buttons[index] == nullptr)
		return;

	buttons[index]->selected = false;

	if (sr::GetKeyDown(sr::Keyboard::UP_ARROW))
	{
		index--;
	}
	else if (sr::GetKeyDown(sr::Keyboard::DOWN_ARROW))
	{
		index++;
	}

	if (index > 2)
		index = 0;

	if (index < 0)
		index = 2;

	buttons[index]->selected = true;
	selectedButton = buttons[index];

	switch (index)
	{
	case 0: // Catcher
		buttons[index]->ChangeSceneIfEnter(Scene_Name::Catcher);
		break;

	case 1: // Shuffle
		buttons[index]->ChangeSceneIfEnter(Scene_Name::Shuffle);
		break;

	case 2: // Tron
		buttons[index]->ChangeSceneIfEnter(Scene_Name::Tron); 
		break;

	default:
		break;
	}

}
