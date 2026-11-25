#pragma once
#include "../Scene.h"
#define MULTIPLAYER

/*
RULES !

Survive Mode :

ZQSD -> Move your Rider (Like snake, you can't go in the reverse direction)
You're constantly moving and you leave a trail behind you 
Your speed and you trail length increase over time
Don't touch your trail or you die !
Don't turn around to fast to prevent your Rider to instantly collide with the trail !
Some nasty Walls will spawn randomly on the map
While being in the spinning animation, there is no hitbox on this wall so you can pass through it !
Survive as long as you can !
The collisions are all 2D Circles (x, z) to handle a lot of Entities.
Fun fact : It's more like Snake 2 than Tron :>

Have fun :3

*/

constexpr float terrainHeight = 1.f;

class Rider;
class TronGame : public Scene
{
	Entity* m_pTerrain = nullptr;
	Rider* m_pP1_Rider = nullptr;

	float m_Spawn_Progress = 0.f;
	float m_Spawn_Delay;

	float m_Trail_Durability;

	int m_Score = 0;

	float m_Scoring_Progress = 0.f;

	int m_Difficulty = 0;

	float m_Difficulty_Progress = 0.f;
	float m_Difficulty_Time_To_Increase = 3.f;
public:
	bool finish = false;
	void Init() override;
	void Update() override;
	void Clear() override;

	//Get
	Entity* GetTerrain() { return m_pTerrain; }
	Rider* GetP1Rider() { return m_pP1_Rider; }

	//Set
	void SetP1Rider(Rider* pRider) { m_pP1_Rider = pRider; }

	void HandleTrail();

	void DifficultyManager();
	void UIManager();
	void Pause();
	void EndConditions();

	void SpawnRandomWall();
};

