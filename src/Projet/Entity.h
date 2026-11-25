#pragma once
#include "../lib/Geometries/Geometry.h"
#include "../lib/Geometries/Geometries.h"
#include <Geometry.h>

class Entity
{
protected:
	const char* m_Name;
	sr::Geometry* m_pGeo;
public:
    bool toDestroy = false;

	Entity(const char* name, sr::Geometry* geo) { m_Name = name, m_pGeo = geo; }
    ~Entity();

    //Get
	const char* GetName() { return m_Name; }
	sr::Geometry* GetGeo() { return m_pGeo; }

	virtual void Start() {};
	virtual void Update() {};

    void SetPosition(gce::Vector3f32 const& pos) { m_pGeo->SetPosition(pos); }
    void SetRotation(gce::Vector3f32 const& rot) { m_pGeo->SetRotation(rot); }
    void SetScale(gce::Vector3f32 const& scale) { m_pGeo->SetScale(scale); }

    void Translate(gce::Vector3f32 const& translation) { m_pGeo->Translate(translation); }
    void Rotate(gce::Vector3f32 const& rotation) { m_pGeo->Rotate(rotation); }
    void Scale(gce::Vector3f32 const& scale) { m_pGeo->Scale(scale); }

    gce::Vector3f32 GetPosition() { return m_pGeo->GetPosition(); }
    gce::Vector3f32 GetRotation() { return m_pGeo->GetRotation(); }
    gce::Vector3f32 GetScale() { return m_pGeo->GetScale(); }

    void SetTexture(sr::Texture const& texture) { m_pGeo->SetTexture(texture); }
    void SetColor(gce::Vector3f32 const& color) { m_pGeo->SetColor(color); }
};

