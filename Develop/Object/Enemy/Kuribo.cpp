#include "Kuribo.h"
#include "../../Utility/ResourceManager.h"

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
	is_mobility = false;

	image = move_animation[0];
}

void Kuribo::Update(float delta_seconde)
{

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

void Kuribo::Movement(float delta_second)
{

}

void Kuribo::AnimationControl(float delta_second)
{

}