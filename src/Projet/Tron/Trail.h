#pragma once
#include "../Entity.h"

class Rider;
class TronGame;
class Trail : public Entity 
{
	float m_Radius = 0.f; // Sphere hitbox

	float m_ProgressTime = 0.f;
	float m_SurvivabilityTime = 3.f;

	TronGame* pScene = nullptr;

	bool collidable = false;
public:
	Trail(float survivabilityTime);

	void Start() override;
	void Update() override;

	float GetRadius() { return m_Radius; } 

	bool CheckCollision();

	void HandleCollideBehaviour();
};

