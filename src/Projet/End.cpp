#include "pch.h"
#include "End.h"
#include "App.h";
#include "Entity.h"

void End::Clear()
{
	Scene::Clear();

	m_Message = L"Nothing to Dipslay";
}

void End::Init()
{
	m_Message = App::Get()->GetEndMessage();

	Entity* background = new Entity("Background EndScene", new sr::Cube);

	background->SetScale({ 4.f, 4.f, 1.f });
	background->SetColor({ 0.f, 0.f, 1.f });

	Add(background); 
}

void End::Update()
{
	sr::Camera* pCam = App::GetCamera();
	pCam->SetPosition({ 0.f, 0.f, -2.f });
	pCam->SetRotation({ 0.0f, 0.0f, 0.0f });

	auto get = App::Get(); 

	get->GetSceneManager().GetCurrentScene()->DrawText(m_Message, { (float)SCREEN_WIDTH * 0.5f + get->GetOffsetX_Message(), (float)SCREEN_HEIGHT * 0.5f}, gce::Color::White);

	if (sr::GetKeyDown(sr::Keyboard::ENTER) || sr::GetKeyDown(sr::Keyboard::SPACE))
	{
		App::Get()->GetSceneManager().ChangeScene(Scene_Name::Menu);
	}
}