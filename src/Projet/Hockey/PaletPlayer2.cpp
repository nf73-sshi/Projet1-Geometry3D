#include "pch.h"
#include "PaletPlayer2.h"
#include "../App.h"
#include "../Hockey/Table.h"
#include "../SceneManager.h"
#include "../Hockey/Game2.h"
#include "Puck.h"

void PaletPlayer2::Start()
{
	Palet::Start();
	SetColor({ 1.f, 0.f, 0.f });
}

void PaletPlayer2::Update()
{
	Palet::Update();
	AI();
}

void PaletPlayer2::HandleCollision()
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

	if (pos.z < m_Radius)
	{
		limitedPos.z = m_Radius;
	}
	if (pos.z > rect.Zwidth * 0.5f - m_Radius)
	{
		limitedPos.z = rect.Zwidth * 0.5f - m_Radius;
	}

	SetPosition({ limitedPos.x, limitedPos.y, limitedPos.z });
}

void PaletPlayer2::AI()
{
	Rect rect = pScene->GetTable()->GetRect();

	gce::Vector3f32 pos = GetPosition();
	gce::Vector3f32 puckPos = pScene->GetPuck()->GetPosition();

	gce::Vector3f32 direction = gce::Vector3f32({ 0.f, 0.f, 0.f });

	if (puckPos.z < -2.f) // Defense
	{
		direction = gce::Vector3f32({ puckPos.x - pos.x , 0.f, 1});
	}
	else // Attack
	{
		direction = gce::Vector3f32({ puckPos.x - pos.x, 0.f, puckPos.z - pos.z + 2.f});
	}

	direction = direction.Normalize();

	Translate(direction * m_Speed * 1.5f * App::GetDeltaTime());
}