#pragma once
#include "GameObject.h"

enum State
{
	live,
	die
};
class Character : public GameObject
{
protected:
	Vector2D velocity;
	int hit_point;
	bool on_ground;
	State state;
	float die_time;

public:
	virtual void OnHitCollision(GameObject* hit_object) override;
	virtual const Vector2D& GetLocation() const override;
	virtual const Collision& GetCollision() const override;
	virtual const unsigned char GetZLayer() const override;
	virtual const bool GetMobility() const override;
	virtual const State GetState();
	
	virtual const  bool HitCheckUp(GameObject* hit_object, float side[][4]);
	virtual const  bool HitCheckRight(GameObject* hit_object, float side[][4]);
	virtual const  bool HitCheckDown(GameObject* hit_object, float side[][4]);
	virtual const  bool HitCheckLeft(GameObject* hit_object, float side[][4]);
};
