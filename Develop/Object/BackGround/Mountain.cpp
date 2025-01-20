#include "Mountain.h"
#include "DxLib.h"

void Mountain::Initialize()
{
	mountain_image[top] = LoadGraph("Resource/Images/mountain_up.png");
	mountain_image[right] = LoadGraph("Resource/Images/mountain_right.png");
	mountain_image[center] = LoadGraph("Resource/Images/mountain_center.png");
	mountain_image[left] = LoadGraph("Resource/Images/mountain_left.png");

	number = 0;
}

void Mountain::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Mountain::Finalize()
{

}

const Vector2D& Mountain::GetLocation() const
{
	return location;
}

const Collision& Mountain::GetCollision() const
{
	return collision;
}

const unsigned char Mountain::GetZLayer() const
{
	return z_layer;
}

const bool Mountain::GetMobility() const
{
	return is_mobility;
}

