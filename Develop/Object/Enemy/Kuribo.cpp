#include "Kuribo.h"
#include "../../Utility/ResourceManager.h"

#define SPEED (30)

void Kuribo::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImageResource("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32);

	collision.is_blocking = true;
	collision.object_type = eEnemy;
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eGround);
	collision.box_size = Vector2D(32, 32);

	//レイヤー設定
	z_layer = 4;

	//可動性の設定
	is_mobility = true;

	image = move_animation[0];

	velocity.x = -1.0f;

	animation_count = 0;

	animation_time = 0;

	state = live;

	die_time = 0;

}

void Kuribo::Update(float delta_seconde)
{
	float x = camera->Get_CameraLocation().x + D_WIN_MAX_X / 2;

	switch (state)
	{
	case live:
		if (location.x - OBJECT_SIZE / 2 < x)
		{
			Movement(delta_seconde);
			AnimationControl(delta_seconde);
		}
		break;

	case die:
		is_mobility = false;
		image = move_animation[2];
		break;
	}

}

void Kuribo::Draw(const Vector2D& screen_offset) const
{
	//親クラスの処理を呼び出す
	__super::Draw(screen_offset);

	Vector2D ul = location - (collision.box_size / 2);
	Vector2D br = location + (collision.box_size / 2);
	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
}

void Kuribo::Finalize()
{
	move_animation.clear();
}

void Kuribo::OnHitCollision(GameObject* hit_object)
{
	if (state != die)
	{
		Collision target = hit_object->GetCollision();

		Vector2D t_location = hit_object->GetLocation();

		float side[2][4];

		
		side[0][UP] = this->location.y - (this->collision.box_size.y / 2);
		side[0][RIGHT] = this->location.x + (this->collision.box_size.x / 2);
		side[0][DOWN] = this->location.y + (this->collision.box_size.y / 2);
		side[0][LEFT] = this->location.x - (this->collision.box_size.x / 2);

		
		side[1][UP] = t_location.y - (target.box_size.y / 2);
		side[1][RIGHT] = t_location.x + (target.box_size.x / 2);
		side[1][DOWN] = t_location.y + (target.box_size.y / 2);
		side[1][LEFT] = t_location.x - (target.box_size.x / 2);

		
		if (HitCheckUp(hit_object, side) == true && target.object_type == ePlayer)
		{
			velocity.y = 0.0f;
			state = die;
		}
	}

}

const Vector2D& Kuribo::GetLocation() const
{
	return location;
}

const Collision& Kuribo::GetCollision() const
{
	return collision;
}

const unsigned char Kuribo::GetZLayer() const
{
	return z_layer;
}

const  bool Kuribo::GetMobility() const
{
	return is_mobility;
}

void Kuribo::Filp_flag(bool flag)
{

}

void Kuribo::Set_Velocity(Vector2D velocity)
{

}

void Kuribo::Set_Camera(Camera* c)
{
	camera = c;
}

void Kuribo::Movement(float delta_seconde)
{
	location += velocity * SPEED * delta_seconde;
}

void Kuribo::AnimationControl(float delta_seconde)
{
	animation_time += delta_seconde;

	if (animation_time >= 0.5)
	{
		animation_time = 0.0f;

		image = move_animation[animation_count];

		animation_count++;

		if (animation_count > 1)
		{
			animation_count = 0;
		}

	}

}