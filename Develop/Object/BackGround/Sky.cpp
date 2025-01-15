#include "Sky.h"
#include "DxLib.h"

void Sky::Initialize()
{
	image = LoadGraph("Resource/Images/sora.png");

	z_layer = 1;
}

void Sky::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Sky::Finalize()
{

}

const Vector2D& Sky::GetLocation() const
{
	return location;
}

const Collision& Sky::GetCollision() const
{
	return collision;
}

const unsigned char Sky::GetZLayer() const
{
	return z_layer;
}

const bool Sky::GetMobility() const
{
	return is_mobility;
}

