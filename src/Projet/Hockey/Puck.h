#pragma once
#include "../Entity.h"

class ShuffleGame;
class Puck : public Entity
{
protected:
	float m_Radius = 0.f;
	float m_Height = 0.f;

	float m_Default_Speed;
	float m_Speed;
	const float m_Max_Speed = 120.f;
	gce::Vector3f32 m_Direction = { 0.f, 0.f, 0.f };

	ShuffleGame* pScene = nullptr;
public:
	Puck(float radius, float heightt);

	void Start() override;
	void Update() override;

	//Get
	float GetSpeed() { return m_Speed; }
	float GetMaxSpeed() { return m_Max_Speed; }
	gce::Vector3f32& GetDirection() { return m_Direction; }

	void DecreaseSpeed();

	//Set
	void SetSpeed(float val) { m_Speed = val; if (m_Speed > m_Max_Speed)m_Speed = m_Max_Speed; }
	void SetDirection(gce::Vector3f32 newDir) { m_Direction = newDir.Normalize(); }
	void SetSpeedToDefaultSpeed() { m_Speed = m_Default_Speed; }

	float GetRadius() { return m_Radius; }
	float GetHeight() { return m_Height; }
	void HandleCollision();
};

