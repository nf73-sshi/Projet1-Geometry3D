#include "pch.h"
#include "PaletPlayer1.h"
#include "../App.h"
#include "../Hockey/Table.h"
#include "../SceneManager.h"
#include "../Hockey/Game2.h"

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
	gce::Vector2i32 mousePos = sr::GetMousePosition();

	gce::Vector3f32 direction2 = { -(float)(oldMousePos.x - mousePos.x), 0.f, (float)(oldMousePos.y - mousePos.y) };

	if (sr::GetButton(sr::Mouse::LEFT))
	{
		Translate(direction2 * m_Speed * 0.25f * App::GetDeltaTime());
	}

	oldMousePos = mousePos;
}