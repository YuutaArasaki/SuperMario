#include "Brick.h"
#include "DxLib.h"

void Brick::Initialize()
{
	collision.object_type = eBlock;
	collision.hit_object_type.push_back(ePlayer);
	collision.hit_object_type.push_back(eEnemy);
	collision.hit_object_type.push_back(eItem);

	image = LoadGraph("Resource/Images/Block/block.png");

	is_mobility = false;

}

void Brick::Update(float delta_seconde)
{

}

void Brick::Draw(const Vector2D& screen_offset) const
{

}

void Brick::Finalize()
{

}

void Brick::OnHitCollision(GameObject* hit_object)
{

}

const Vector2D& Brick::GetLocation() const
{
	return location;
}

const Collision& Brick::GetCollision() const
{
	return collision;
}

const unsigned char Brick::GetZLayer() const
{
	return z_layer;
}

const bool Brick::GetMobility() const
{
	return is_mobility;
}
