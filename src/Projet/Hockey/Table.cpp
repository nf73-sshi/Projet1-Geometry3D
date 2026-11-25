#include "pch.h"
#include "Table.h"

Table::Table(float xLength, float yHeight, float zWidth) : Entity("Shuffle Table", new sr::Cube())
{
	rect.Xlength = xLength;
	rect.Yheight = yHeight;
	rect.Zwidth = zWidth;

	SetPosition({ 0.f, 0.f, 0.f });
	SetScale({ rect.Xlength, rect.Yheight, rect.Zwidth });
	SetColor({ 0.75f, 0.75f, 0.75f });
}

void Table::Start()
{
	
}

void Table::Update()
{

}