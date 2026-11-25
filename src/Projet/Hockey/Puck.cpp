#include "pch.h"
#include "Puck.h"
#include "../App.h"
#include "../Hockey/Table.h"
#include "../SceneManager.h"
#include "../Hockey/Game2.h"

Puck::Puck(float radius, float height) : Entity("Puck", new sr::Cylinder())
{
	m_Radius = radius;
	m_Height = height;

	SetScale({ m_Radius * 2.f, m_Height, m_Radius * 2.f });
	SetColor({ 0.1f, 0.1f, 0.1f });
}

void Puck::Start()
{
#ifdef FRICTIONS
	m_Default_Speed = 0.f;
#else
	m_Default_Speed = 25.f;
#endif

	m_Speed = m_Default_Speed;
	pScene = App::Get()->GetSceneManager().GetScene<ShuffleGame>();

	if (pScene)
		SetPosition({ 0.0f, pScene->GetTable()->GetRect().Yheight, 0.0f });

	m_Direction = { 0.f, 0.f, 0.f };
}

void Puck::Update()
{
	HandleCollision(); 

	Translate(m_Direction * m_Speed * App::GetDeltaTime());

#ifdef FRICTIONS 
	DecreaseSpeed();
#endif
}

void Puck::DecreaseSpeed()
{
	if (m_Speed < 0)
		m_Speed = 0;
	else
	{
		m_Speed -= 10 * App::GetDeltaTime();
	}
}

void Puck::HandleCollision()
{
	if (pScene == nullptr)
		return;

	Rect rect = pScene->GetTable()->GetRect();

	gce::Vector3f32 pos = GetPosition();

	gce::Vector3f32 limitedPos = pos;

	if (pos.x < -rect.Xlength * 0.5f + m_Radius)
	{
		limitedPos.x = -rect.Xlength * 0.5f + m_Radius;

		m_Direction.x = -m_Direction.x;
	}
	if (pos.x > rect.Xlength * 0.5f - m_Radius)
	{
		limitedPos.x = rect.Xlength * 0.5f - m_Radius;

		m_Direction.x = -m_Direction.x;
	}

	if (pos.z < -rect.Zwidth * 0.5f + m_Radius)
	{
		limitedPos.z = -rect.Zwidth * 0.5f + m_Radius;

		m_Direction.z = -m_Direction.z;
	}
	if (pos.z > rect.Zwidth * 0.5f - m_Radius)
	{
		limitedPos.z = rect.Zwidth * 0.5f - m_Radius;

		m_Direction.z = -m_Direction.z;
	}

	SetPosition({ limitedPos.x, limitedPos.y, limitedPos.z });

#ifndef FRICTIONS
	SetSpeed(m_Speed += 5 * App::GetDeltaTime());
#endif

}
