#pragma once
#include "Scene.h"

/*
RULES !

Your score or stats will be displayed here !

Press Enter or Space to Get Back in the Menu !

*/

class End : public Scene
{
	std::wstring m_Message = L"";
public:
	void Clear() override;

	void Init() override;
	void Update() override;
};

