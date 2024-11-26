#pragma once
#include "GameObject.h"

class Character : public GameObject
{
protected:
	Vector2D velocity;
	int hit_point;
	bool on_ground;

public:
	virtual void OnHitCollision(GameObject* hit_object) override;
	virtual const Vector2D& GetLocation() const override;
	virtual const Collision& GetCollision() const override;
	virtual const unsigned char GetZLayer() const override;
	virtual const bool GetMobility() const override;

};
