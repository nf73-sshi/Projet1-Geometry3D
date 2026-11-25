#pragma once
#include "../Scene.h"
#define FRICTIONS // To decrease the Puck Speed over the time 

/*
RULES !

Hold Left Click & Drag -> Move your Batter
You play a match against a very good AI (no)
The puck speed decreases when no collide (default) and increases with Batters collisions
Aim the goal to win a point !
The first who get 5 points wins the match !
The match lasts 120s (default)
The collisions can be weird sometimes.
Fun fact : You can block the puck in a corner and Unleash its True Power :O

Have fun :3

*/

class Palet;
class Table;
class Puck;

class ShuffleGame : public Scene
{
	Table* m_pTable = nullptr;

	Palet* m_pPlayer1 = nullptr;
	Palet* m_pPlayer2 = nullptr;
	Puck* m_pPuck = nullptr;

	Entity* m_p1_Goal = nullptr;
	Entity* m_p2_Goal = nullptr;

	int m_p1_Score = 0;
	int m_p2_Score = 0;

	const float m_BeginTime = 120.f;
	float m_Time;

public:

	//Get
	Table* GetTable() { return m_pTable; }
	Puck* GetPuck() { return m_pPuck; }

	void Init() override;
	void Update() override;
	void Clear() override;

	void UIManager();
	void InitGoals();
	void UpdateGoals();
	void EndConditions();

	void ResetPositions();

	void Pause();
};

