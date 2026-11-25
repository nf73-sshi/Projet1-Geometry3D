#pragma once
#include "Palet.h"

class PaletPlayer2 : public Palet
{
	float m_Speed = 25.f;
public:
	PaletPlayer2(float radius) : Palet(radius) {}

	void Start() override;
	void Update() override;

	void HandleCollision() override;
	void AI();
};

