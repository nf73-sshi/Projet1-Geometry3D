#pragma once
#include "Entity.h"
#include "../lib/Text.h"
#include <string>

class Button : public Entity
{
	std::wstring message = L"";
	gce::Vector2f32 m_Pos;
	gce::Vector2f32 m_TxtPos;

public:
	bool selected = false;
	Button(std::wstring txt, gce::Vector2f32 pos, gce::Vector2f32 txtPos, float width, float height);
	void Start() override;
	void Update() override;
	bool CheckMouseOnButton();

	void ChangeSceneIfEnter(const char* name);
};

