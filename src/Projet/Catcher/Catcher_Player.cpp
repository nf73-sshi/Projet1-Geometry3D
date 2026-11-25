#include "pch.h"
#include "Catcher_Player.h"
#include "Game1.h"
#include "../App.h"
#include "Ball.h"

Catcher_Player::Catcher_Player() : Entity("Catcher_Player", new sr::Cylinder)
{
}

void Catcher_Player::SetLives(int val)
{
	m_Lives = val; App::Frame(m_Lives, 0, m_Max_Lives);
}

void Catcher_Player::Start()
{
	m_Lives = m_Max_Lives;
	m_Angle = 180.f;
	m_Speed = m_DefaultSpeed;

	SetScale({ m_Radius * 2, m_Height, m_Radius * 2 });

	m_pScene = App::Get()->GetSceneManager().GetScene<CatcherGame>();
}

void Catcher_Player::Update()
{
	Movements();

	CheckCollision();
}

void Catcher_Player::Movements()
{
	float shift = 1.f;

	if ((sr::GetKey(sr::Keyboard::LSHIFT)))
	{
		shift = 0.5f;
	}

	if (sr::GetKey(sr::Keyboard::Q))
	{
		m_Angle += m_Speed * shift * App::GetDeltaTime();
	}
	if (sr::GetKey(sr::Keyboard::D))
	{
		m_Angle -= m_Speed * shift * App::GetDeltaTime();
	}

	float radius = m_pScene->GetRailRadius();

	if (m_Angle > 360)
	{
		m_Angle -= 360;
	}
	if (m_Angle < 0)
	{
		m_Angle += 360;
	}

	float radians = m_Angle * gce::PI / 180.f;

	SetPosition({ std::sin(radians) * radius, GetPosition().y, std::cos(radians) * radius });
}

void Catcher_Player::CheckCollision()
{
	if (m_pScene == nullptr)
		return;

	std::vector allColllectibles = m_pScene->GetAll<Ball>();

	for (auto it = allColllectibles.begin(); it != allColllectibles.end(); ++it)
	{
		auto myPos = GetPosition();
		auto ballPos = (*it)->GetPosition();

		if(ballPos.y - (*it)->GetRadius() < m_Height + m_pScene->GetRailHeight() * 0.5f)
		{
			float square2D_Distance = std::pow((ballPos.x - myPos.x), 2) + std::pow((ballPos.z - myPos.z), 2); // Only in X, Z

			if ( square2D_Distance < std::pow(m_Radius + (*it)->GetRadius(), 2) ) // distance² < sum of the 2 radius ² = collision 
			{
				m_pScene->AddScore(100);

				(*it)->toDestroy = true;
			}
		}
	}
}
