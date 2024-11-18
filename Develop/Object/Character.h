#pragma once
#include "GameObject.h"

class Character : public GameObject
{
protected:
	Vector2D velocity;
	int hit_point;
	bool on_ground;

public:
	virtual void OnHitCollision(GameObject*) override;

};
