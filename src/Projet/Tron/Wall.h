#pragma once
#include "../Entity.h"

class TronGame;
class Wall : public Entity
{
	float m_Radius = 0.f; // Sphere Hitbox

	TronGame* pScene;

	float m_Progress_To_Collide = 3.f;
public:
	Wall(float radius);

	void Start() override;
	void Update() override;

	float GetRadius() { return m_Radius; }

	bool CheckCollision();

	void HandleCollideBehaviour();
};

