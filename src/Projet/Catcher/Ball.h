#pragma once
#include "../lib/Geometries/Geometry.h"
#include "Entity.h"

class CatcherGame;
class Ball : public Entity
{
    CatcherGame* pScene = nullptr;

    float m_defaultSpeed = 2.f;
    float m_Speed = m_defaultSpeed;
    float m_Radius = 0.5f;
public:
    Ball(const char* name = "None");

    float GetRadius() { return m_Radius; }
    float GetSpeed() { return m_Speed; }
    float GetDefaultSpeed() { return m_defaultSpeed; }

    void SetSpeed(float val) { m_Speed = val; }


    void Start() override;
    void Update() override;
};


