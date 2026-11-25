#include "pch.h"
#include "Button.h"
#include "../lib/Inputs/InputsMethods.h"
#include "../lib/Inputs/InputsEnums.h"
#include "../lib/Inputs/InputSystem.h"
#include "App.h"
#include "Scene.h"

Button::Button(std::wstring txt, gce::Vector2f32 pos, gce::Vector2f32 txtPos, float width, float height) : Entity("Button", new sr::Cube())
{
    message = txt;
    m_Pos = pos;
    m_TxtPos = txtPos;

    SetPosition({pos.x, pos.y, 0.f});
    SetScale({ width, height, 1.f });
    SetColor({ 0.f, 1.f, 1.f });
}

void Button::Start()
{
}

void Button::Update()
{
    auto currentScene = App::Get()->GetSceneManager().GetCurrentScene();

    if (currentScene == nullptr)
        return;

    if (selected == true)
    {
        currentScene->DrawText(message, m_TxtPos, gce::Color::White);
    }
    else
    {
        currentScene->DrawText(message, m_TxtPos, gce::Color::Black);
    }
}

bool Button::CheckMouseOnButton()
{
    return false;
}

void Button::ChangeSceneIfEnter(const char* name)
{
    if(sr::GetKeyDown(sr::Keyboard::ENTER))
        App::Get()->GetSceneManager().ChangeScene(name);
}
