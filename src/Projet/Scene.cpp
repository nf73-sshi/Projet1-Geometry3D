#include "pch.h"
#include "Scene.h"
#include "App.h"
#include "Entity.h"
#include <lib/Geometries/Geometry.h>

Scene::Scene()
{
}

Scene::~Scene()
{
	Clear();
}

void Scene::Clear()
{
	for (Entity* e : m_pEntities)
	{
		delete e;
	}

	m_pEntities.clear();

	for (sr::Text* t : m_pTextes)
	{
		delete t;
	}

	m_pTextes.clear();

	quit = false;
}

void Scene::Add(Entity* entity)
{
	entity->Start(); 
	m_pEntities.push_back(entity);
}

void Scene::DrawText(std::wstring txt, gce::Vector2f32 pos, gce::Color color)
{
	sr::Text* text = new sr::Text(txt);

	text->SetText(txt);
	text->SetPosition(pos);
	text->SetColor(color);

	m_pTextes.push_back(text);
}

void Scene::Draw() 
{
	sr::Window* win = App::GetWindow();

	win->Begin(*App::GetCamera());
	
	for (Entity* e : m_pEntities)
	{
		auto geo = e->GetGeo();

		if (geo == nullptr)
			continue;

		win->Draw(*geo);
	}

	for (auto it = m_pTextes.begin(); it != m_pTextes.end(); ++it)
	{
		win->DrawText(**it);
	}

	win->End();
	win->Display();

	for (auto it = m_pTextes.begin(); it != m_pTextes.end();)
	{
		delete* it;

		it = m_pTextes.erase(it);
	}
}

void Scene::PauseKeyManager()
{
	if (sr::GetKeyDown(sr::Keyboard::ESCAPE))
	{
		isPaused = !isPaused;
	}

	if (isPaused)
	{
		DrawText(L"Continue = Echap", { (float)SCREEN_WIDTH * 0.4f,  (float)SCREEN_HEIGHT * 0.5f - 150 }, gce::Color::Blue);
		DrawText(L"Retry = R", { (float)SCREEN_WIDTH * 0.4f,  (float)SCREEN_HEIGHT * 0.5f - 50 }, gce::Color::Green);
		DrawText(L"Quit = BackSpace (Retour)", { (float)SCREEN_WIDTH * 0.4f,  (float)SCREEN_HEIGHT * 0.5f + 50 }, gce::Color::Red);

		if (sr::GetKeyDown(sr::Keyboard::R))
		{
			isPaused = false;
			App::Get()->GetSceneManager().ResetCurrentScene();
		}
		else if (sr::GetKeyDown(sr::Keyboard::BACKSPACE))
		{
			isPaused = false;
			quit = true;
		}
	}
}

void Scene::Update()
{
	for (auto it = m_pEntities.begin(); it != m_pEntities.end();)
	{
		if ((*it)->toDestroy)
		{
			delete* it;

			it = m_pEntities.erase(it);
		}
		else
		{
			(*it)->Update();

			++it;
		}
	}
}