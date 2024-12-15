#include "Block.h"
#include "DxLib.h"


void Block::Initialize()
{
	image = LoadGraph("Resource/Images/Block/floor.png");

	if (image == NULL)
	{
		throw ("ブロック(地面)が読み込めませんでした\n");
	}

	collision.object_type = eGround;
	collision.hit_object_type.push_back(ePlayer);

	collision.box_size = Vector2D(32, 32);

	is_mobility = false;


}

void Block::Update(float delta_seconde)
{

}

void Block::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
	Vector2D ul = location - (collision.box_size / 2);
	Vector2D br = location + (collision.box_size / 2);
	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
}

void Block::Finalize()
{

}

void Block::OnHitCollision(GameObject* hit_object)
{

}

const Vector2D& Block::GetLocation() const
{
	return location;
}

const Collision& Block::GetCollision() const
{
	return collision;
}

const unsigned char Block::GetZLayer() const
{
	return z_layer;
}

const bool Block::GetMobility() const
{
	return is_mobility;
}