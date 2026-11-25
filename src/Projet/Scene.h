#pragma once
#include <vector>
#include "../lib/Geometries/Geometry.h"
#include "../lib/Text.h"
#include "pch.h"

class Entity; 

class Scene
{
protected:
	std::vector<Entity*> m_pEntities; 
	std::vector<sr::Text*> m_pTextes;

	bool quit = false; 
public:
	bool isPaused = false;

	Scene();
	~Scene();


	std::vector<Entity*>& GetEntities() { return m_pEntities; }

	template<typename T>
	T* GetFirst();
	template<typename T>
	std::vector<T*> GetAll();

	virtual void Clear();
	void Add(Entity* entity);

	void DrawText(std::wstring txt, gce::Vector2f32 pos, gce::Color color);

	virtual void Init() = 0;
	virtual void Update();
	void Draw();

	void PauseKeyManager();
};

template<typename T>
inline T* Scene::GetFirst()
{
	for (Entity* e : m_pEntities)
	{
		if (T* t = dynamic_cast<T*>(e))
			return t;
	}

	return nullptr;
}

template<typename T>
inline std::vector<T*> Scene::GetAll()
{
	std::vector<T*> selected_Entities;

	for (Entity* e : m_pEntities)
	{
		if (T* t = dynamic_cast<T*>(e))
		{
			selected_Entities.push_back(t);
		}
	}

	return selected_Entities;
}
