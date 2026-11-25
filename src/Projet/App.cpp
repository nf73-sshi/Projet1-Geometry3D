#include "pch.h"
#include "App.h"
#include <chrono>

#include "Catcher/Game1.h"
#include "Hockey/Game2.h"
#include "Tron/Game3.h"

#include "Menu.h"
#include "End.h"

App* App::m_Inst = nullptr;

void App::Shutdown()
{
    delete m_pWindow; 
    delete m_pCam;

    for (auto it = m_pTextures.begin(); it != m_pTextures.end(); ++it)
    {
        delete it->second;
    }

    m_pTextures.clear();

    delete m_Inst;
}

App* App::Get()
{
	if (m_Inst == nullptr)
	{
		m_Inst = new App();
	}

	return m_Inst;
}

void App::SetEndMessage(std::wstring txt, float offsetX)
{
    m_EndMessage = txt;
    m_OffsetX_Message = offsetX;
}


float App::Frame(float& val, float min, float max)
{
    if (val > max)
        val = max;
    if (val < min)
        val = min;

    return val;
}

int App::Frame(int& val, int min, int max)
{
    if (val > max)
        val = max;
    if (val < min)
        val = min;

    return val;
}

void App::Init()
{
    srand(time(nullptr));

    //Window creation
    m_pWindow = new sr::Window(L"PartyGam", 1920, 1080);

    //Textures
    m_pTextures["UV"] = new sr::Texture("res/Textures/uv.png");

    //Scenes
    m_Scene_Manager.AddScene(Scene_Name::End, new End());
    m_Scene_Manager.AddScene(Scene_Name::Catcher, new CatcherGame());
    m_Scene_Manager.AddScene(Scene_Name::Shuffle, new ShuffleGame());
    m_Scene_Manager.AddScene(Scene_Name::Tron, new TronGame());
    m_Scene_Manager.AddScene(Scene_Name::Menu, new Menu()); 

    //Camera creation
    m_pCam = new sr::Camera(sr::CameraType::PERSPECTIVE);
    m_pCam->SetPosition({ 0, 0, 0 });
    m_pCam->SetFOV(gce::PI / 4.0f);
    m_pCam->SetFarPlane(500.0f);
    m_pCam->SetNearPlane(0.001f);
}

void App::Run()
{
    Init();

    using namespace std::chrono;
    steady_clock::time_point lastTime = steady_clock::now();

    //Rendering Loop
    m_Scene_Manager.GetCurrentScene()->Init();

    while (m_pWindow->IsOpen() && running == true)
    {
        steady_clock::time_point currentTime = steady_clock::now();
        duration<float> deltatime = duration_cast<duration<float>>(currentTime - lastTime);
        lastTime = currentTime;

        dt = static_cast<float>(deltatime.count());

        Scene* currentScene = m_Scene_Manager.GetCurrentScene();

        if (currentScene != nullptr)
        {
            currentScene->Draw();

            currentScene->Update();
        }
    }
}
