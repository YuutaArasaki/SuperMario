#include "Character.h"
#include "Player/Player.h"

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


const bool Character::HitCheckUp(GameObject* hit_object, float side[][4])
{
	Vector2D diff;

	if (this->GetLocation().x >= hit_object->GetLocation().x)
	{
		diff.x = side[1][RIGHT] - side[0][LEFT];
		diff.y = side[1][DOWN] - side[0][UP];

	}
	else if (this->GetLocation().x < hit_object->GetLocation().x)
	{
		diff.x = side[0][RIGHT] - side[1][LEFT];
		diff.y = side[0][UP] - side[1][DOWN];
	}

	if (diff.x < 0)
	{
		diff.x *= -1;
	}

	if (diff.y < 0)
	{
		diff.y *= -1;
	}

	if (diff.x > diff.y)
	{
		return true;
	}

	return false;

}


const bool	Character::HitCheckRight(GameObject* hit_object, float side[][4])
{
	Vector2D diff;

	if (this->GetLocation().y <= hit_object->GetLocation().y)
	{
		diff.x = side[0][RIGHT] - side[1][LEFT];
		diff.y = side[0][DOWN] - side[1][UP];

	}
	else if (this->GetLocation().y > hit_object->GetLocation().y)
	{
		diff.x = side[0][RIGHT] - side[1][LEFT];
		diff.y = side[1][DOWN] - side[0][UP];
	}

	if (diff.x < 0)
	{
		diff.x *= -1;
	}

	if (diff.y < 0)
	{
		diff.y *= -1;
	}

	if (diff.x < diff.y)
	{
		return true;
	}

	return false;
}

const bool Character::HitCheckDown(GameObject* hit_object, float side[][4])
{
	Vector2D diff;

	if (this->GetLocation().x >= hit_object->GetLocation().x)
	{
		diff.x = side[1][RIGHT] - side[0][LEFT];
		diff.y = side[0][DOWN] - side[1][UP];
		
	}
	else if (this->GetLocation().x < hit_object->GetLocation().x)
	{
		diff.x = side[0][RIGHT] - side[1][LEFT];
		diff.y = side[0][DOWN] - side[1][UP];
	}
	
	if (diff.x < 0)
	{
		diff.x *= -1;
	}

	if (diff.y < 0)
	{
		diff.y *= -1;
	}
	
	if (diff.x >= diff.y)
	{
		return true;
	}
	else
	{
		return	false;
	}

	
}

const bool Character::HitCheckLeft(GameObject* hit_object, float side[][4])
{
	Vector2D diff;

	if (this->GetLocation().y <= hit_object->GetLocation().y)
	{
		diff.x = side[1][RIGHT] - side[0][LEFT];
		diff.y = side[0][DOWN] - side[1][UP];

	}
	else if (this->GetLocation().y > hit_object->GetLocation().y)
	{
		diff.x = side[1][RIGHT] - side[0][LEFT];
		diff.y = side[0][UP] - side[1][DOWN];
	}

	if (diff.x < 0)
	{
		diff.x *= -1;
	}

	if (diff.y < 0)
	{
		diff.y *= -1;
	}

	if (diff.x < diff.y)
	{
		return true;
	}

	return false;
	
}