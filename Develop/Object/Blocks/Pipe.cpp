#include "Pipe.h"
#include "DxLib.h"

void Pipe::Initialize()
{
	pipe_image[0] = LoadGraph("Resource/Images/dokan_left_up.png");
	pipe_image[1] = LoadGraph("Resource/Images/dokan_left_down.png");
	pipe_image[2] = LoadGraph("Resource/Images/dokan_right_up.png");
	pipe_image[3] = LoadGraph("Resource/Images/dokan_right_down.png");

	collision.object_type = ePipe;
	collision.hit_object_type.push_back(ePlayer);
	collision.hit_object_type.push_back(eEnemy);
	collision.hit_object_type.push_back(eItem);

	collision.box_size = Vector2D(32, 32);
	
	image = pipe_image[0];
}

void Pipe::Update(float delta_seconde)
{

}

void Pipe::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Pipe::Finalize()
{

}

void Pipe::OnHitCollision(GameObject* hit_object)
{

}

const Vector2D& Pipe::GetLocation() const
{
	return location;
}

const Collision& Pipe::GetCollision() const
{
	return collision;
}

const unsigned char Pipe::GetZLayer() const
{
	return z_layer;
}

const bool Pipe::GetMobility() const
{
	return is_mobility;
}

void Pipe::Set_Image(int number)
{
	switch (number)
	{
	case 0:
		image = pipe_image[0];
		break;

	case 1:
		image = pipe_image[1];
		break;

	case 2:
		image = pipe_image[2];
		break;

	case 3:
		image = pipe_image[3];
		break;
	}
}