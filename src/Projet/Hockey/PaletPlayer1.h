#pragma once
#include "Palet.h"

class PaletPlayer1 : public Palet
{
	gce::Vector2i32 oldMousePos;
public:
	PaletPlayer1(float radius) : Palet(radius) {}
	void Start() override;
	void Update() override;

	void HandleCollision() override;
	void Control();
};

