#pragma once
#include "../Entity.h"

class CatcherGame;
class Catcher_Player : public Entity
{
	CatcherGame* m_pScene = nullptr;
	float m_Radius = 1.0f;
	float m_Height = 2.0f;
	float m_Angle = 180.f; // In Degrees
	float m_DefaultSpeed = 100.f;
	float m_Speed = m_DefaultSpeed;
	float m_Rail_Height = 0.0f;

	int m_Max_Lives = 4;
	int m_Lives;
public:
	Catcher_Player();

	//Get
	float GetAngle() { return m_Angle; }
	float GetRadius() { return m_Radius; }
	float GetHeight() { return m_Height; }
	int GetLives() { return m_Lives; }
	float GetSpeed() { return m_Speed; }
	float GetDefaultSpeed() { return m_DefaultSpeed; }

	//Set
	void SetLives(int val);
	void SetSpeed(float val) { m_Speed = val; }

	void Start() override;
	void Update() override;

	void Movements();
	void CheckCollision();
};

