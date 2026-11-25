#include "pch.h"
#include "Ball.h"
#include "Catcher/Game1.h"
#include "App.h"
#include "SceneManager.h"
#include "Catcher/Catcher_Player.h"

Ball::Ball(const char* name) : Entity(name, new sr::Sphere)
{
}

void Ball::Start()
{
	pScene = App::Get()->GetSceneManager().GetScene<CatcherGame>();

	SetScale({ m_Radius * 2, m_Radius * 2, m_Radius * 2});
}

void Ball::Update()
{
	if (pScene == nullptr)
		return;
	
	if (GetPosition().y - m_Radius < pScene->GetRailHeight() * 0.5f)
	{
		auto player = pScene->GetPlayer();

		if (player)
		{
			player->SetLives(player->GetLives() - 1);
		}

		toDestroy = true;
	}

	Translate(gce::Vector3f32(0.0f, -m_Speed, 0.0f) * App::GetDeltaTime());
}
