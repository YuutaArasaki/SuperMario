#include "Question.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

void Question::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	block_image = rm->GetImageResource("Resource/Images/Block/hatena.png", 4, 4, 1, 32, 32);
	collision.object_type = eBlock;
	collision.hit_object_type.push_back(ePlayer);
	collision.hit_object_type.push_back(eEnemy);
	collision.hit_object_type.push_back(eItem);

	collision.box_size = Vector2D(32, 32);

	is_mobility = false;

	image = block_image[0];

}

void Question::Update(float delta_seconde)
{

}

void Question::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Question::Finalize()
{

}

void Question::OnHitCollision(GameObject* hit_object)
{

}

const Vector2D& Question::GetLocation() const
{
	return location;
}

const Collision& Question::GetCollision() const
{
	return collision;
}

const unsigned char Question::GetZLayer() const
{
	return z_layer;
}

const bool Question::GetMobility() const
{
	return is_mobility;
}
