#pragma once
#include "../Entity.h"

struct Rect
{
	float Xlength = 0;
	float Yheight = 0;
	float Zwidth = 0;
};

class Table : public Entity
{
	Rect rect;
public:
	Table(float xLength, float yHeight, float zWidth);

	virtual void Start();

	Rect& GetRect() { return rect; }

	virtual void Update();
};

