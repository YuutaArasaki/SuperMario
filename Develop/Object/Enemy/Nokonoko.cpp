#include "Nokonoko.h"
#include "../../Utility/ResourceManager.h"

#define SPEED (30)
#define D_GRAVITY (9.807f)		//重力加速度

void Nokonoko::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImageResource("Resource/Images/Enemy/nokonoko.png", 2, 2, 1, 32, 64);
	die_animation = rm->GetImageResource("Resource/Images/Enemy/nokonoko_revival.png", 2, 2, 1, 32, 32);

	for (int i = 0; i < 2; i++)
	{
		if (move_animation[i] == NULL)
		{
			throw("ノコノコの画像がありません\n");
		}
	}
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

	image_offset = 16;
}

void Nokonoko::Update(float delta_seconde)
{

	switch (state)
	{
	case live:
		image_offset = 16;
		collision.box_size = Vector2D(32, 32);
		Movement(delta_seconde);
		AnimationControl(delta_seconde);
		break;

	case die:
		image_offset = 0;
		die_time++;
		collision.box_size = Vector2D(32, 32);

		if (is_ground == false)
		{
			location.y += 16;
		}

		if (die_time <= 180)
		{
			image = die_animation[0];
		}
		else if (die_time > 180)
		{
			image = die_animation[1];
		}
		
		if (die_time == 300)
		{
			state = live;
			image = move_animation[0];
			die_time = 0;
		}

	}
}

void Nokonoko::Draw(const Vector2D& screen_offset) const
{
	Vector2D ul = location - (collision.box_size / 2);
	Vector2D br = location + (collision.box_size / 2);
	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);

	/*__super::Draw(screen_offset);*/
	Vector2D graph_location = this->location - screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y - image_offset, 1.0, 0.0, image, TRUE, filp_flag);
	DrawCircle(location.x, location.y, 5, GetColor(255, 0, 0), 1);
}

void Nokonoko::Finalize()
{

}

void Nokonoko::OnHitCollision(GameObject* hit_object)
{
	Vector2D diff, dv;
	Vector2D target_boxsize, this_boxsize;
	diff = 0.0f;
	dv = 0.0f;
	Vector2D target_location = hit_object->GetLocation();

	target_boxsize = hit_object->GetCollision().box_size;
	this_boxsize = this->collision.box_size;


	//2点間の距離を求める
	diff = this->location - target_location;

	//自身がHitしたオブジェクトよりも右側にいたとき
	if (diff.x > 0)
	{
		//自身がHitしたオブジェクトよりも下側にいたとき
		if (diff.y > 0)
		{
			dv.x = (target_location.x + target_boxsize.x / 2) - (this->location.x - this_boxsize.x / 2);
			dv.y = (target_location.y + target_boxsize.y / 2) - (this->location.y - this_boxsize.y / 2);

			if (dv.x > dv.y)
			{
				this->location.y += dv.y;
			}
			else
			{
				this->location.x += dv.x;
			}

			if (hit_object->GetCollision().object_type == ePlayer)
			{
				state = die;
			}
		}
		else	//自身がHitしたオブジェクトよりも上側にいたとき
		{
			dv.x = (target_location.x + target_boxsize.x / 2) - (this->location.x - this_boxsize.x / 2);
			dv.y = (this->location.y + this_boxsize.y / 2) - (target_location.y - target_boxsize.y / 2);

			if (dv.x > dv.y)
			{
				this->location.y += -dv.y;
				if (hit_object->GetCollision().object_type == eGround)
				{
					is_ground = true;
					g_velocity = 0;
					velocity.y = 0;
				}

			}
			else
			{
				this->location.x += dv.x;
			}
		}
	}
	else	//自身がHitしたオブジェクトよりも左側にいたとき
	{
		//自身がHitしたオブジェクトよりも下側にいたとき
		if (diff.y > 0)
		{
			dv.x = (this->location.x + this_boxsize.x / 2) - (target_location.x - target_boxsize.x / 2);
			dv.y = (target_location.y + target_boxsize.y / 2) - (this->location.y - this_boxsize.y / 2);

			if (dv.x > dv.y)
			{
				this->location.y += dv.y;
			}
			else
			{
				this->location.x += -dv.x;
			}

			if (hit_object->GetCollision().object_type == ePlayer)
			{
				state = die;
			}
		}
		else	//自身がHitしたオブジェクトよりも上側にいたとき
		{
			dv.x = (this->location.x + this_boxsize.x / 2) - (target_location.x - target_boxsize.x / 2);
			dv.y = (this->location.y + this_boxsize.y / 2) - (target_location.y - target_boxsize.y / 2);

			if (dv.x > dv.y)
			{
				this->location.y += -dv.y;

				if (hit_object->GetCollision().object_type == eGround)
				{
					is_ground = true;
					g_velocity = 0;
					velocity.y = 0;
				}
			}
			else
			{
				this->location.x += -dv.x;
			}
		}
	}
}

const Vector2D& Nokonoko::GetLocation() const
{
	return location;
}

const Collision& Nokonoko::GetCollision() const
{
	return collision;
}
const unsigned char Nokonoko::GetZLayer() const
{
	return z_layer;
}

const bool Nokonoko::GetMobility() const
{
	return is_mobility;
}

void Nokonoko::Filp_flag(bool flag)
{
	filp_flag = flag;
}

void Nokonoko::Set_Velocity(Vector2D velocity)
{
	this->velocity = velocity;
}

void Nokonoko::Set_Camera(Camera* c)
{
	camera = c;
}

void Nokonoko::Movement(float delta_seconde)
{
	location += velocity * SPEED * delta_seconde;
}

void Nokonoko::AnimationControl(float delta_seconde)
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
