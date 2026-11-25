#pragma once
#include "lib/Inputs/InputsMethods.h"
#include "lib/Geometries/Geometries.h"
#include "lib/Camera.h"
#include "lib/Texture.h"
#include "lib/Window.h"
#include "lib/Text.h"
///
#include <map>
#include "SceneManager.h"
#include <string>

constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;

namespace Scene_Name
{
	constexpr const char* Catcher = "CatcherScene";
	constexpr const char* Shuffle = "ShuffleScene";
	constexpr const char* Tron = "TronScene";
	constexpr const char* Menu = "MenuScene";
	constexpr const char* End = "EndScene";
}

class App
{
	static App* m_Inst;

	sr::Window* m_pWindow = nullptr;
	sr::Camera* m_pCam = nullptr;
	float dt = 0; // DeltaTime

	SceneManager m_Scene_Manager;

	std::map<const char*, sr::Texture*> m_pTextures;

	std::wstring m_EndMessage = L"Nothing to Dipslay"; // Visible in the End scene;
	float m_OffsetX_Message = 0.f;
public:
	bool running = true;
	void Shutdown();
	// Get
	static App* Get();
	static sr::Window* GetWindow() { return Get()->m_pWindow; }
	static sr::Camera* GetCamera() { return Get()->m_pCam; }
	static float GetDeltaTime() { return Get()->dt; }
	static sr::Texture& GetTexture(const char* name) { return *Get()->m_pTextures[name]; }
	SceneManager& GetSceneManager() { return m_Scene_Manager; }
	std::wstring& GetEndMessage() { return m_EndMessage; }
	float GetOffsetX_Message() { return m_OffsetX_Message; }

	//Set
	void SetEndMessage(std::wstring txt, float offsetX);

	//Utils
	static float Frame(float& val, float min, float max);
	static int Frame(int& val, int min, int max);

	// Main
	void Init();
	void Run();
};

