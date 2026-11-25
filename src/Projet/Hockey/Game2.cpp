#include "pch.h"
#include "Game2.h"
#include "../App.h"
#include "PaletPlayer1.h"
#include "PaletPlayer2.h"
#include "Table.h"
#include "Puck.h"

void ShuffleGame::Clear()
{
	Scene::Clear();
}

void ShuffleGame::InitGoals()
{
    Rect rect = m_pTable->GetRect();

    m_p1_Goal = new Entity("P1 Goal", new sr::Cube());
    m_p1_Goal->SetColor({ 0.25f, 0.25f, 1.f });
    m_p1_Goal->SetScale({ rect.Xlength * 0.35f, 2.f, 2.f });
    m_p1_Goal->SetPosition({ 0.f, 0.f, -rect.Zwidth * 0.5f - m_p1_Goal->GetScale().z * 0.5f});
    Add(m_p1_Goal);

    m_p2_Goal = new Entity("P2 Goal", new sr::Cube());
    m_p2_Goal->SetColor({ 1.f, 0.25f, 0.25f });
    m_p2_Goal->SetScale({ rect.Xlength * 0.35f, 2.f, 2.f });
    m_p2_Goal->SetPosition({ 0.f, 0.f, rect.Zwidth * 0.5f + m_p1_Goal->GetScale().z * 0.5f });
    Add(m_p2_Goal);
}

void ShuffleGame::UIManager()
{
    DrawText(L"P1 Score : " + std::to_wstring(m_p1_Score), { 0.0f, (float)SCREEN_HEIGHT -300.f }, gce::Color::Blue);
    DrawText(L"P2 SCore : " + std::to_wstring(m_p2_Score), { 0.0f, 200.f }, gce::Color::Red);
    DrawText(L"Time Left : " + std::to_wstring(m_Time), { SCREEN_WIDTH * 0.85f, 0.0f }, gce::Color::Black);
}

void ShuffleGame::UpdateGoals()
{
    bool goal = false;

    Rect rect = m_pTable->GetRect();

    gce::Vector3f32 puckPos = m_pPuck->GetPosition();

    float radius = m_pPuck->GetRadius();

    float p1goalLength = m_p1_Goal->GetScale().x;
    float p2goalLength = m_p2_Goal->GetScale().x;

    if (puckPos.z < -rect.Zwidth * 0.5f + radius)
    {
        if (puckPos.x > -p1goalLength * 0.5f - radius && puckPos.x < p1goalLength * 0.5f + radius)
        {
            goal = true;
            m_p2_Score++;
        }
    }

    if (puckPos.z > rect.Zwidth * 0.5f - radius)
    {
       if (puckPos.x > -p2goalLength * 0.5f - radius && puckPos.x < p2goalLength * 0.5f + radius)
        {
            goal = true;
            m_p1_Score++;
        }
    }

    if (goal == true)
    {
        ResetPositions();
    }
}

void ShuffleGame::EndConditions()
{
    int maxScore = 5;
    std::wstring winner = L"None";

    bool finish = false;

    if (m_Time < 0 || quit == true)
    {
        if (m_p1_Score > m_p2_Score)
        {
            winner = L"P1";
            finish = true;
        }
        else if (m_p1_Score < m_p2_Score)
        {
            winner = L"P2";
            finish = true;
        }
        else
        {
            winner = L"DRAW";
            finish = true;
        }
    }
    else
    {
        m_Time -= App::GetDeltaTime();

        if (m_p1_Score >= maxScore)
        {
            winner = L"P1";
            finish = true;
        }
        else if (m_p2_Score >= maxScore)
        {
            winner = L"P2";
            finish = true;
        }
    }

    if (finish)
    {
        App::Get()->SetEndMessage(L"[Winner ! " + winner + L"] Score : P1 = " + std::to_wstring(m_p1_Score) + L" | P2 = " + std::to_wstring(m_p2_Score), -400.f);
        App::Get()->GetSceneManager().ChangeScene(Scene_Name::End);
    }
}

void ShuffleGame::ResetPositions()
{
    Rect rect = m_pTable->GetRect();

    m_pPlayer1->SetPosition({ 0.f, m_pTable->GetRect().Yheight, -rect.Zwidth * 0.5f + m_pPlayer1->GetRadius() * 2.f });
    m_pPlayer2->SetPosition({ 0.f, m_pTable->GetRect().Yheight, rect.Zwidth * 0.5f - m_pPlayer2->GetRadius() * 2.f });

    m_p1_Goal->SetPosition({ 0.f, 0.f, -rect.Zwidth * 0.5f - m_p1_Goal->GetScale().z * 0.5f });
    m_p2_Goal->SetPosition({ 0.f, 0.f, rect.Zwidth * 0.5f + m_p1_Goal->GetScale().z * 0.5f });

    m_pPuck->SetPosition({ 0.0f, rect.Yheight, 0.0f });
    m_pPuck->SetSpeedToDefaultSpeed();
    m_pPuck->SetDirection({ 0.f, 0.f, 0.f });

    sr::SetMousePosition({ (int)(SCREEN_WIDTH * 0.5f), (int)(SCREEN_HEIGHT * 0.7f) });
}

void ShuffleGame::Pause()
{
    UIManager(); 

    PauseKeyManager();
}

void ShuffleGame::Init()
{
    sr::SetMousePosition({ (int)(SCREEN_WIDTH * 0.5f), (int)(SCREEN_HEIGHT * 0.7f) });

    m_Time = m_BeginTime;
    m_p1_Score = 0;
    m_p2_Score = 0;

    sr::Camera* pCam = App::GetCamera();
    pCam->SetPosition({ 0.f, 50.f, -60.f });
    pCam->SetRotation({ 45.f, 0.f, 0.f });

    m_pTable = new Table(30.f, 2.f, 60.f);
    Add(m_pTable);
   
    Entity* pLine = new Entity("Table Line", new sr::Cube);
    pLine->SetColor({ 1.f, 1.f, 1.f });
    pLine->SetScale({ m_pTable->GetRect().Xlength, 0.25f, 0.2f });
    pLine->SetPosition({ 0.f, 1.5f, 0.f });
    Add(pLine);

    m_pPuck = new Puck(1.f, 0.5f);
    Add(m_pPuck);

    InitGoals();

    Rect rect = m_pTable->GetRect();

    m_pPlayer1 = new PaletPlayer1(2.f);
    m_pPlayer1->SetPosition({0.f, m_pTable->GetRect().Yheight, - rect.Zwidth * 0.5f + m_pPlayer1->GetRadius() * 2.f});
    Add(m_pPlayer1);

    m_pPlayer2 = new PaletPlayer2(2.f);
    m_pPlayer2->SetPosition({ 0.f, m_pTable->GetRect().Yheight, rect.Zwidth * 0.5f - m_pPlayer2->GetRadius() * 2.f });
    Add(m_pPlayer2); 
}

void ShuffleGame::Update()
{
    Pause();

    if (isPaused)
    {
        return;
    }

    Scene::Update();
    UpdateGoals();
    EndConditions();
}