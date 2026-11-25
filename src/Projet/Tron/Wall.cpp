#include "pch.h"
#include "Wall.h"
#include "../App.h"
#include "Game3.h"
#include "Rider.h"

Wall::Wall(float radius) : Entity("Wall", new sr::Cube())
{
	m_Radius = radius;
}

void Wall::Start()
{
	SetColor({ 1.f, 1.f, 1.f });
	SetScale({ m_Radius * 2, m_Radius * 2, m_Radius * 2 });
	pScene = App::Get()->GetSceneManager().GetScene<TronGame>();
}

void Wall::Update()
{
	if (m_Progress_To_Collide < 0)
	{
		SetRotation({ 0.f, 0.f, 0.f });
		HandleCollideBehaviour();
	}
	else
	{
		float dt = App::GetDeltaTime();
		float speed = 20.f;

		float ratio = 1.f - m_Progress_To_Collide / 3.f;
			
		SetRotation({ ratio * 90.f, ratio * 90.f, 0.f });

		m_Progress_To_Collide -= dt;
	}
}

bool Wall::CheckCollision()
{
	auto pOwner = pScene->GetP1Rider();

	if (pOwner == nullptr)
		return false;

	// Sphere Collision to handle more entities

	gce::Vector3f32 p1Pos = pOwner->GetPosition();
	gce::Vector3f32 myPos = GetPosition();

	float squareDistance2D = std::pow(p1Pos.x - myPos.x, 2) + std::pow(p1Pos.z - myPos.z, 2);

	if (squareDistance2D < std::pow(pOwner->GetRadius() + m_Radius * 0.9f, 2))
	{
		return true;
	}

	return false;
}

void Wall::HandleCollideBehaviour()
{
	auto pOwner = pScene->GetP1Rider();
	
	if (pOwner == nullptr)
		return;

	if (CheckCollision() == true)
	{
		pOwner->toDestroy = true;
		pScene->SetP1Rider(nullptr); // Handle other Trails in the same frame
		pScene->finish = true;
		return;
	}
}