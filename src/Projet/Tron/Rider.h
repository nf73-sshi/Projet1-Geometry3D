#pragma once
#include "../Entity.h"

class Rider : public Entity
{
	float m_Default_Speed = 10.f;
	float m_Speed = m_Default_Speed;
	
	float m_Radius = 0.f;
	gce::Vector3f32 m_Direction = { 1.f, 0.f, 0.f };;

	float m_Trail_Survivability = 1.f; 

	float m_Default_Spawn_Delay = 0.15f;
	float m_Spawn_Delay = m_Default_Spawn_Delay;
public:
	Rider(float radius);

	void Start() override;
	void Update() override;

	//Get
	float GetRadius() { return m_Radius; }
	gce::Vector3f32& GetDirection() { return m_Direction; }
	float GetSpawnDelay() { return m_Spawn_Delay; }

	//Set
	void SetSpawnDelay(float val) { m_Spawn_Delay = val; }

	void IncreaseSpeed();

	void HandleTerrainCollisions();
	void Controls(); 
};

