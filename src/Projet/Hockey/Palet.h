#pragma once
#include "../Entity.h"

class ShuffleGame;

class Palet : public Entity // The Players
{
protected:
	float m_Radius = 0.f;
	float m_Height = 0.f;

	float m_Speed = 50.f;

	ShuffleGame* pScene = nullptr;

	float mDelayProgress = 0.f;
	float mDelayBeforeReCollide = 0.1f;
public:
	Palet(float radius);

	virtual void Start();
	virtual void Update();

	float GetRadius() { return m_Radius; }
	float GetHeight() { return m_Height; }
	virtual void HandleCollision() {};

	void PuckCollision();
};

