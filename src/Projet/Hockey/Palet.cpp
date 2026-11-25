#include "pch.h"
#include "Palet.h"
#include "Puck.h"
#include "../App.h"
#include "../SceneManager.h"
#include "../Hockey/Game2.h"

Palet::Palet(float radius) : Entity("Palet", new sr::Cylinder())
{
	m_Radius = radius;
	m_Height = 0.75f;

	SetScale({ m_Radius * 2.f, m_Height, m_Radius * 2.f });
}

void Palet::Start()
{
	pScene = App::Get()->GetSceneManager().GetScene<ShuffleGame>();
}

void Palet::Update()
{
	HandleCollision();
	PuckCollision();
}

void Palet::PuckCollision()
{
	Puck* puck = pScene->GetPuck();

	if (puck == nullptr)
		return;

	gce::Vector3f32 myPos = GetPosition(); 
	gce::Vector3f32 puckPos = puck->GetPosition();

	float dx = puckPos.x - myPos.x;
	float dy = puckPos.z - myPos.z;

	float squareDistance = std::pow(dx, 2) + std::pow(dy, 2);
	
	if (squareDistance <= 0.0001f)
		return;

	if (squareDistance >= std::pow(puck->GetRadius() + GetRadius(), 2)) // If not colliding
		return;

	float dist = sqrtf(squareDistance);
	gce::Vector3f32 centerDirection = { dx / dist, 0.f, dy / dist };

	gce::Vector3f32 puckDirection = puck->GetDirection();
	if (puckDirection.Norm() <= 0.0001f)
	{
		puck->SetDirection(centerDirection);
	}
	else
	{
		float dot = puckDirection.DotProduct(centerDirection);
		if (dot < 0.f)
		{
			gce::Vector3f32 reflected = (puckDirection - centerDirection * dot * 2.f).Normalize();
			puck->SetDirection(reflected);
		}
	}

	float penetration = m_Radius + puck->GetRadius() - sqrtf(squareDistance);

	float ratio = penetration / (m_Radius + puck->GetRadius());

	puck->Translate(centerDirection * penetration * 1.1f);

	puck->SetSpeed(puck->GetSpeed() + ratio * puck->GetMaxSpeed());
}
