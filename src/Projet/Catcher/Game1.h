#pragma once
#include "../Scene.h"
#define DYNAMIC_CAM // Remove this to have a static view

/*
RULES !

Q : Left | D : Right -> Move
Hold Shift -> Decrease your speed by 2
Catch the falling balls
If a ball touches the ground, you lose a life !
The difficulty increases over time !
Your speed will increases when Balls will fall faster
Survive as long as you can and get the highest Score possible !
You can see it with the Time Text Color !
Fun fact : If you pass the pink Level you're legally skilled ^^

Have fun :3

*/


class Catcher_Player;
class Entity;
class CatcherGame : public Scene
{
	Entity* m_pRail = nullptr;
	Catcher_Player* m_pPlayer = nullptr;

	float m_Rail_Radius;
	float m_Rail_Height;

	int m_Score;
	int m_Lives;

	float m_Time;

	gce::Vector3f32 ballColor;

	float progressTimeToSpawn = 0.f;
	float defaultTimeToSpawn = 3.f;
	float timeToSpawn;

	float m_SpeedMultiplier = 1.f;
	gce::Color textColor;
public:
	void Init() override;
	void Update() override;

	void Clear() override;

	//Get
	Catcher_Player* GetPlayer() { return m_pPlayer; }
	Entity* GetRail() { return m_pRail; }
	float GetRailRadius() { return m_Rail_Radius; }
	float GetRailHeight() { return m_Rail_Height; }

	int GetScore() { return m_Score; }

	//Set
	void AddScore(int val) { m_Score += val; }

	void InitBase(float radius, float height);
	void SpawnBall();
	void DifficultyManager();
	void EndConditions(); 
	void UIManager();

	void DynamiCameraManager();

	void Pause();
};

