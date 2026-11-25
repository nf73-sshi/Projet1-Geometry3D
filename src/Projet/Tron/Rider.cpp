#include "pch.h"
#include "Rider.h"
#include "../App.h"
#include "Game3.h"
#include "Trail.h" 
#include "../Scene.h"

Rider::Rider(float radius) : Entity("Rider", new sr::Cube())
{
	m_Radius = radius;
}

void Rider::Start()
{
	float diameter = m_Radius * 2.f;

	SetPosition({ 0.f, m_Radius, 0.f });
	SetScale({ diameter, diameter, diameter });
	SetColor({ 1.f, 0.f, 0.f });
}

void Rider::Update()
{
	HandleTerrainCollisions();
	Controls();
	IncreaseSpeed();
}

void Rider::IncreaseSpeed()
{
	m_Speed += 0.25f * App::GetDeltaTime();

	m_Spawn_Delay = m_Default_Spawn_Delay * (m_Default_Speed / m_Speed);
}

void Rider::HandleTerrainCollisions()
{
	auto pScene = App::Get()->GetSceneManager().GetScene<TronGame>();

	Entity* pTerrain = pScene->GetTerrain();

	if (pTerrain == nullptr)
		return;

	gce::Vector3f32 myPos = GetPosition();
	gce::Vector3f32 terrainScale = pTerrain->GetScale();

	bool isOut = false;

	if (myPos.x < -terrainScale.x * 0.5f - m_Radius || myPos.x > terrainScale.x * 0.5f + m_Radius)
	{
		isOut = true;
	}

	if (myPos.z < -terrainScale.z * 0.5f - m_Radius || myPos.z > terrainScale.z * 0.5f + m_Radius)
	{
		isOut = true;
	}

	if (isOut)
	{
		toDestroy = true;
		pScene->SetP1Rider(nullptr); // Handle other Trails in the same frame
		pScene->finish = true;
	}
}

void Rider::Controls()
{
	gce::Vector3f32 newDir = m_Direction;

	bool chosen = false;

	if (sr::GetKeyDown(sr::Keyboard::Q) && chosen == false)
	{
		if (m_Direction.x == 0)
		{
			chosen = true;
			newDir.x = -1;
			newDir.z = 0;
		}
	}

	else if (sr::GetKeyDown(sr::Keyboard::D) && chosen == false)
	{
		if (m_Direction.x == 0)
		{
			chosen = true;
			newDir.x = 1;
			newDir.z = 0;
		}
	}

	if (sr::GetKeyDown(sr::Keyboard::S) && chosen == false)
	{
		if (m_Direction.z == 0)
		{
			chosen = true;
			newDir.z = -1;
			newDir.x = 0;
		}
	}
	else if (sr::GetKeyDown(sr::Keyboard::Z) && chosen == false)
	{
		if (m_Direction.z == 0)
		{
			chosen = true;
			newDir.z = 1;
			newDir.x = 0;
		}
	}

	newDir.y = 0;

	newDir = newDir.Normalize();
	m_Direction = newDir;
	Translate(newDir * m_Speed * App::GetDeltaTime());
}
