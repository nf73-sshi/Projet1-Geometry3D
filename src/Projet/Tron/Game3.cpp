#include "pch.h"
#include "Game3.h"
#include "../App.h"
#include "Wall.h"
#include "Trail.h"
#include "Rider.h"

void TronGame::Clear()
{
	Scene::Clear();
}

void TronGame::Init()
{
    finish = false;

    m_Score = 0;
    m_Difficulty = 0;
    m_Difficulty_Progress = 0.f;

    m_Scoring_Progress = 0.f;
    m_Trail_Durability = 3.f;

    sr::Camera* pCam = App::GetCamera();
    pCam->SetPosition({ 0.f, 140.f, 0.f });
    pCam->SetRotation({ 90.f, 0.f, 0.f });

    m_pTerrain = new Entity("Tron Surface", new sr::Cube());
    m_pTerrain->SetScale({ 100.f, terrainHeight, 100.f });
    m_pTerrain->SetPosition({ 0.f, -0.5f, 0.f });
    Add(m_pTerrain);

    m_pP1_Rider = new Rider(1.f);
    Add(m_pP1_Rider);

    m_Spawn_Progress = 0.f;
    m_Spawn_Delay = m_pP1_Rider->GetSpawnDelay();
}

void TronGame::Update()
{
    Pause();

    if (isPaused)
    {
        return;
    }

    Scene::Update();
    EndConditions();
    DifficultyManager();

    HandleTrail();
}

void TronGame::EndConditions()
{
    if (finish || quit)
    {
        App::Get()->SetEndMessage(L"Score : " + std::to_wstring(m_Score), -100.f);
        App::Get()->GetSceneManager().ChangeScene(Scene_Name::End);
    }
    else
    {
        if (m_Scoring_Progress <= 0.f)
        {
            m_Scoring_Progress = 0.1f;
            m_Score += 1;
        }
        else
        {
            m_Scoring_Progress -= App::GetDeltaTime();
        }
    }
}

void TronGame::SpawnRandomWall()
{
    float size = 2.f;

    Wall* w = new Wall(size);

    int playerPos2DX = m_pP1_Rider->GetPosition().x;
    int playerPos2DZ = m_pP1_Rider->GetPosition().z;

    float wallSize = w->GetRadius() * 2;

    gce::Vector3f32 terrainScale = m_pTerrain->GetScale();
    gce::Vector2f32 rdmPos2D = { -(terrainScale.x) * 0.5f + wallSize + rand() % (int)(terrainScale.x - wallSize), -(terrainScale.z) * 0.5f + wallSize + rand() % (int)(terrainScale.z - wallSize)};

    w->SetPosition({ rdmPos2D.x, terrainHeight + w->GetRadius() * 2, rdmPos2D.y });

    Add(w);
}

void TronGame::UIManager()
{
    DrawText(L"Score : " + std::to_wstring(m_Score), { 0.0f, 0.0f }, gce::Color::Red);
    DrawText(L"Walls : " + std::to_wstring(m_Difficulty), { SCREEN_WIDTH * 0.80f, 0.0f }, gce::Color::Black);
}

void TronGame::Pause()
{
    UIManager();

    PauseKeyManager();
}

void TronGame::HandleTrail()
{
    if (m_pP1_Rider == nullptr)
        return;

    m_Spawn_Delay = m_pP1_Rider->GetSpawnDelay();

    if (m_Spawn_Progress < 0)
    {
        m_Spawn_Progress = m_Spawn_Delay;

        Trail* current = new Trail(m_Trail_Durability);

        gce::Vector3f32 myPos = m_pP1_Rider->GetPosition();

        current->SetPosition({ myPos.x, terrainHeight + current->GetRadius() * 0.5f, myPos.z });
        current->SetColor({ 1.f, 0.5f, 0.f });

        Add(current);
    }
    else
    {
        m_Spawn_Progress -= App::GetDeltaTime();
    }
}

void TronGame::DifficultyManager()
{
    if (m_Difficulty_Progress >= m_Difficulty_Time_To_Increase) // Increase Difficulty
    {
        m_Difficulty_Progress = 0.f;

        m_Difficulty++;
        m_Trail_Durability += 0.5f;
        SpawnRandomWall();
    }
    else
    {
        m_Difficulty_Progress += App::GetDeltaTime();
    }
}