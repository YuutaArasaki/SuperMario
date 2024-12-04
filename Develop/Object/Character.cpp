#include "Character.h"

void Character::OnHitCollision(GameObject* hit_object)
{
	
}

const Vector2D& Character::GetLocation() const
{
	return location;
}

const Collision& Character:: GetCollision() const
{
	return collision;
}

const unsigned char Character:: GetZLayer() const
{
	return z_layer;
}

const bool Character:: GetMobility() const
{
	return is_mobility;
}