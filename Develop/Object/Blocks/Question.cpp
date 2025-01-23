#include "Question.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

void Question::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	block_image = rm->GetImageResource("Resource/Images/Block/hatena.png", 4, 4, 1, 32, 32);
	kara_block = LoadGraph("Resource/Images/Block/kara_block.png");
	collision.object_type = eBlock;
	collision.hit_object_type.push_back(ePlayer);
	collision.hit_object_type.push_back(eEnemy);
	collision.hit_object_type.push_back(eItem);

	collision.box_size = Vector2D(32, 32);

	is_mobility = false;

	image = block_image[0];

	animation_time = 0.0f;
	
	animation_count = 0;

	up_count = 0;

	down_count = 0;

	hit_flag = false;

}

void Question::Update(float delta_seconde)
{
	if (hit_flag == true)
	{
		if (up_count < 8)
		{
			this->location.y += -1;
			up_count++;
		}
		else if (down_count < 8)
		{
			this->location.y += 1;
			down_count++;
		}
	}
	AnimationControl(delta_seconde);
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
	Vector2D diff = 0.0f;
	Vector2D target_boxsize, this_boxsize;
	Vector2D target_location = hit_object->GetLocation();

	//2“_ŠÔ‚Ì‹——£‚ð‹‚ß‚é
	diff = this->location - target_location;


	if (diff.y < 0)
	{
		if (hit_object->GetCollision().object_type == ePlayer)
		{
			image = kara_block;
			hit_flag = true;
		}
	}


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

void Question::AnimationControl(float delta_seconde)
{
	animation_time += delta_seconde;

	if (animation_time >= 0.2)
	{
		animation_time = 0.0f;

		animation_count++;

		if (animation_count >= 4)
		{
			animation_count = 0;
		}

		if (hit_flag == false)
		{
			image = block_image[animation_count];
		}
		else
		{
			image = kara_block;
		}
		
	}
}