#include "pch.h"
#include "Trail.h"
#include "../App.h"
#include "Game3.h"
#include "Rider.h"

Trail::Trail(float survivabilityTime) : Entity("Trail", new sr::Cube())
{
	m_SurvivabilityTime = survivabilityTime;
}

void Trail::Start()
{
	pScene = App::Get()->GetSceneManager().GetScene<TronGame>();

	if (pScene == nullptr)
		return;

	auto pOwner = pScene->GetP1Rider();

	if (pOwner == nullptr)
		return;

	m_Radius = pOwner->GetRadius();

	SetScale({ m_Radius * 2, m_Radius * 0.5f, m_Radius * 2 });
}

void Trail::Update()
{
	if (m_ProgressTime > m_SurvivabilityTime)
	{
		toDestroy = true;
		return;
	}
	else
	{
		m_ProgressTime += App::GetDeltaTime(); 
	}

	HandleCollideBehaviour();
}

bool Trail::CheckCollision()
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

void Trail::HandleCollideBehaviour()
{
	auto pOwner = pScene->GetP1Rider();

	if (pOwner == nullptr)
		return;

	bool collision = CheckCollision();

	if (collision == false && collidable == false)
	{
		collidable = true;
	}
	else if (collision == true && collidable == true)
	{
		pOwner->toDestroy = true;
		pScene->SetP1Rider(nullptr); // Handle other Trails in the same frame
		pScene->finish = true;
		return;
	}
}
