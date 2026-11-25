#include "pch.h"
#include "PaletPlayer1.h"
#include "../App.h"
#include "../Hockey/Table.h"
#include "../SceneManager.h"
#include "../Hockey/Game2.h"
#include <algorithm>

void PaletPlayer1::Start()
{
	oldMousePos = sr::GetMousePosition();  

	Palet::Start();
	SetColor({ 0.f, 0.f, 1.f });
}

void PaletPlayer1::Update()
{
	Control(); 
	Palet::Update();
}

void PaletPlayer1::HandleCollision() 
{
	if (pScene == nullptr)
		return;

	Rect rect = pScene->GetTable()->GetRect();

	gce::Vector3f32 pos = GetPosition();

	gce::Vector3f32 limitedPos = pos;

	if (pos.x < -rect.Xlength * 0.5f + m_Radius)
	{
		limitedPos.x = -rect.Xlength * 0.5f + m_Radius;
	}
	if (pos.x > rect.Xlength * 0.5f - m_Radius)
	{
		limitedPos.x = rect.Xlength * 0.5f - m_Radius;
	}

	if (pos.z < -rect.Zwidth * 0.5f + m_Radius)
	{
		limitedPos.z = -rect.Zwidth * 0.5f + m_Radius;
	}
	if (pos.z > - m_Radius)
	{
		limitedPos.z = - m_Radius;
	}

	SetPosition({ limitedPos.x, limitedPos.y, limitedPos.z});
}

void PaletPlayer1::Control()
{
	gce::Vector2f32 mousePos = sr::GetMousePosition();
	mousePos.x /= App::GetWindow()->m_width;
	mousePos.y /= App::GetWindow()->m_height;
	mousePos.y = 1.f - std::clamp(mousePos.y, 0.f, 1.f);

	mousePos.x = 2.f * (- 0.5f + mousePos.x);
	mousePos.y = 1.5f * (-0.5f + mousePos.y);

	const gce::Vector3f32& pos = pScene->GetTable()->GetPosition();
	const Rect& rect = pScene->GetTable()->GetRect();

	gce::Vector3f32 t = {};
	t.x = pos.x + rect.Xlength * mousePos.x;
	t.y = GetPosition().y;
	t.z = pos.z + rect.Zwidth * mousePos.y;

	SetPosition(t);
	oldMousePos = mousePos;
}