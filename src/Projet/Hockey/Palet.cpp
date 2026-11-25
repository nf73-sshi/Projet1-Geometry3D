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

	float squareDistance = std::pow(puckPos.x - myPos.x, 2) + std::pow(puckPos.z - myPos.z, 2);

	if (squareDistance >= std::pow(puck->GetRadius() + GetRadius(), 2)) // If not colliding
		return;

	gce::Vector3f32 centerDirection = { (puckPos.x - myPos.x), 0.f, (puckPos.z - myPos.z) };
	centerDirection = centerDirection.Normalize();

	if (puck->GetDirection() == gce::Vector3f32(0.f, 0.f, 0.f))
	{
		puck->SetDirection(centerDirection);
	}

	gce::Vector3f32 puckDirection = puck->GetDirection();

	float dot = puckDirection.DotProduct(centerDirection);

	gce::Vector3f32 reflected = puckDirection - centerDirection * dot * 2.f; // Physic Reflection : reflected = v - 2n * (v ° n)
	reflected = reflected.Normalize();

	puck->SetDirection(reflected);

	float epsilon = 0.02f + puck->GetSpeed() * 0.01f; // Shifting for less multiple collisions

	puck->Translate(centerDirection * epsilon);

#ifdef FRICTIONS
	puck->SetSpeed(1.f + puck->GetSpeed() * 1.1f);
#endif
}
