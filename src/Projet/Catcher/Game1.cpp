#include "pch.h"
#include "Game1.h"
#include "../App.h"
#include "../Entity.h"
#include "Ball.h"
#include "Catcher_Player.h"
#include "../../lib/Window.h"

const float camDistance = -25.f;

void CatcherGame::Clear()
{
    Scene::Clear();
}

void CatcherGame::Init()
{
    sr::Camera* pCam = App::GetCamera();
    pCam->SetPosition({ 0.0f, 25.f, camDistance });
    pCam->SetRotation({ 45.f, 0.0f, 0.0f });

    textColor = { 0, 175, 0, 255 };

    m_Time = 0.f;
    m_Score = 0;
    progressTimeToSpawn = 0.f;
    timeToSpawn = defaultTimeToSpawn;

    ballColor = {0.0f, 1.0f, 0.f}; // Green

    m_SpeedMultiplier = 1.f;

    InitBase(10.0f, 1.f);

    m_Lives = m_pPlayer->GetLives(); 
}

void CatcherGame::Update()
{
    Pause();

    if (isPaused)
    {
        return;
    }

#ifdef DYNAMIC_CAM
    DynamiCameraManager();
#endif

    Scene::Update();
    EndConditions();
    DifficultyManager();
    SpawnBall(); 
}

void CatcherGame::InitBase(float rail_radius, float rail_height)
{
    m_Rail_Radius = rail_radius;
    m_Rail_Height = rail_height;

    m_pRail = new Entity("rail", new sr::Cylinder());
    m_pRail->SetPosition({ 0.0f, 0.0f, 0.0f });
    m_pRail->SetScale({ rail_radius * 2, rail_height, rail_radius * 2});
    m_pRail->SetColor({ 0.5f, 0.5f, 0.5f });
    Add(m_pRail);

    Entity* deco = new Entity("railOutline", new sr::Cylinder());
    deco->SetPosition({ 0.0f, -0.25f, 0.0f });
    deco->SetScale({ rail_radius * 2.5f, rail_height * 1.f, rail_radius * 2.5f });
    deco->SetColor({ 0.2f, 0.2f, 0.2f });
    Add(deco);

    m_pPlayer = new Catcher_Player();
    m_pPlayer->SetPosition({ rail_radius, rail_height * 0.5f + m_pPlayer->GetHeight() * 0.5f, 0.f});
    m_pPlayer->SetColor({ 0.0f, 0.0f, 1.0f });
    Add(m_pPlayer);
}

void CatcherGame::SpawnBall()
{
    if (progressTimeToSpawn < 0)
    {
        progressTimeToSpawn = timeToSpawn;

        Ball* b = new Ball();

        float randomAngle = rand() % 360;

        float radians = randomAngle * gce::PI / 180;

        b->SetPosition({ std::sin(radians) * m_Rail_Radius, 20.f, std::cos(radians) * m_Rail_Radius });
        b->SetSpeed(b->GetDefaultSpeed() * m_SpeedMultiplier);
        b->SetColor(ballColor);
        Add(b);
    }
    else
    {
        progressTimeToSpawn -= App::GetDeltaTime(); 
    }
}

void CatcherGame::DifficultyManager()
{
    if (m_pPlayer == nullptr)
        return;

    float playerDefaultSpeed = m_pPlayer->GetDefaultSpeed();

    if (m_Time > 180.f) // Mode : Master
    {
        textColor = gce::Color::Blue;
        ballColor = { 0.f, 0.f, 1.0f }; // Blue
        timeToSpawn = defaultTimeToSpawn * 0.2f;
       
        m_pPlayer->SetSpeed(playerDefaultSpeed * 4.f);
        m_SpeedMultiplier = 3.f;
    }
    else if (m_Time > 120.f) // Mode : Super Expert
    {
        textColor = { 255, 150, 255, 255 };
        ballColor = { 1.0f, 0.5f, 1.0f }; // Pink
        timeToSpawn = defaultTimeToSpawn * 0.25f;

        m_pPlayer->SetSpeed(playerDefaultSpeed * 3.f);
        m_SpeedMultiplier = 2.5f;
    }
    else if (m_Time > 80.f ) // Mode : Expert
    {
        textColor = gce::Color::Magenta;
        ballColor = { 1.0f, 0.0f, 1.0f }; // Magenta
        timeToSpawn = defaultTimeToSpawn * 0.3f;

        m_pPlayer->SetSpeed(playerDefaultSpeed * 2.f);
        m_SpeedMultiplier = 2.f;
    }
    else if (m_Time > 50.f) // Mode : Hard
    {
        textColor = gce::Color::Red;
        ballColor = { 1.0f, 0.0f, 0.0f }; // Red
        timeToSpawn = defaultTimeToSpawn * 0.4f;

        m_pPlayer->SetSpeed(playerDefaultSpeed * 1.75f);
        m_SpeedMultiplier = 1.75f;
    }
    else if (m_Time > 30.f) // Mode : Medium
    {
        textColor = { 255, 125, 0, 255 };
        ballColor = { 1.0f, 0.5f, 0.0f }; // Orange
        timeToSpawn = defaultTimeToSpawn * 0.6f;

        m_pPlayer->SetSpeed(playerDefaultSpeed * 1.5f);
        m_SpeedMultiplier = 1.5f;
    }
    else if (m_Time > 15.f) // Mode : Easy
    {
        textColor = gce::Color::Yellow;
        ballColor = { 1.0f, 1.0f, 0.0f }; // Yellow
        timeToSpawn = defaultTimeToSpawn * 0.8f;

        m_pPlayer->SetSpeed(playerDefaultSpeed * 1.25f);
        m_SpeedMultiplier = 1.25f; 
    }
}

void CatcherGame::EndConditions()
{
    if (m_pPlayer)
    {
        m_Lives = m_pPlayer->GetLives();
    }

    m_Time += App::GetDeltaTime();

    if (m_Lives <= 0 || quit == true)
    {
        App::Get()->SetEndMessage(L"Score : " + std::to_wstring(m_Score), - 100.f);
        App::Get()->GetSceneManager().ChangeScene(Scene_Name::End);
    }
}

void CatcherGame::UIManager()
{
    DrawText(L"Score : " + std::to_wstring(m_Score), { 0.0f, 0.0f }, gce::Color::Red);
    DrawText(L"Lives : " + std::to_wstring(m_Lives), { 0.0f, (float)SCREEN_HEIGHT * 0.85 }, gce::Color({ 0, 100, 0, 255 }));
    DrawText(L"Surviving Time : " + std::to_wstring(m_Time), { SCREEN_WIDTH * 0.8f, 0.0f }, textColor);
}

void CatcherGame::DynamiCameraManager()
{
    float playerAngle = m_pPlayer->GetAngle() + 180.f;

    float radians = playerAngle * gce::PI / 180.f;

    sr::Camera* pCam = App::GetCamera();

    pCam->SetPosition({ std::sin(radians) * camDistance, 25.f, std::cos(radians) * camDistance });
    pCam->SetRotation({ 45.f, playerAngle, 0.f });
}

void CatcherGame::Pause()
{
    UIManager();

    PauseKeyManager();
}