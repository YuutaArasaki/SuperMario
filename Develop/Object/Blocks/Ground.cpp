#include "Ground.h"
#include "DxLib.h"
#include "../GameObject.h"

void Ground::Initialize()
{
	image = LoadGraph("Resource/Images/Block/floor.png");

	if (image == NULL)
	{
		throw ("ブロック(地面)が読み込めませんでした\n");
	}

	collision.object_type = eGround;
	collision.hit_object_type.push_back(ePlayer);
	collision.hit_object_type.push_back(eEnemy);
	collision.hit_object_type.push_back(eItem);

	collision.box_size = Vector2D(32, 32);

	is_mobility = false;

	player = nullptr;

}

void Ground::Update(float delta_seconde)
{

}

void Ground::Draw(const Vector2D& screen_offset) const
{

	float x = camera->Get_CameraLocation().x + D_WIN_MAX_X / 2;
	
	 
	if (this->location.x - (OBJECT_SIZE / 2) < x)
	{
		__super::Draw(screen_offset);
	}

	Vector2D ul = location - (collision.box_size / 2);
	Vector2D br = location + (collision.box_size / 2);
	DrawBoxAA(ul.x - screen_offset.x, ul.y, br.x - screen_offset.x, br.y, GetColor(255, 0, 0), FALSE);
}

void Ground::Finalize()
{

}

void Ground::OnHitCollision(GameObject* hit_object)
{

}

const Vector2D& Ground::GetLocation() const
{
	return location;
}

const Collision& Ground::GetCollision() const
{
	return collision;
}

const unsigned char Ground::GetZLayer() const
{
	return z_layer;
}

const bool Ground::GetMobility() const
{
	return is_mobility;
}

void Ground::Set_Camera(Camera* c)
{
	camera = c;
}