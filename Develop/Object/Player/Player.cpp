#include "Player.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/InputManager.h"
#include "PlayerState/PlayerStateFactory.h"
#include "../../Utility/Application.h"
#include "DxLib.h"


#define D_GRAVITY (9.807f)		//重力加速度
#define P_SPEED (50.0f)

void Player::Initialize()
{
	player_state = PlayerStateFactory::Get((*this), ePlayerState::idle);
	next_state = none;

	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImageResource("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);

	collision.is_blocking = true;
	collision.object_type = eObjectType::ePlayer;
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eGround);
	collision.hit_object_type.push_back(eObjectType::eItem);
	collision.box_size = Vector2D(OBJECT_SIZE,OBJECT_SIZE);

	//レイヤー設定
	z_layer = 5;

	//可動性の設定
	is_mobility = true;

	//アニメーション画像の設定
	image = move_animation[0];

	//画像反転フラグの設定
	filp_flag = FALSE;	

	//地面に着地しているか判定フラグの設定
	is_ground = false;

	//ジャンプできる状態かの判定フラグ
	jump_flag = true;

	/*
	 オブジェクトにヒットしている = true
	オブジェクトにヒットしていない = false
	*/
	hit_flag = true;

	//横スクロール用カメラのポインタ
	camera = nullptr;

	//方
	slide_flag = false;

}

void Player::Update(float delta_seconde)
{
	//ePlayerState p_state;
	slide_flag = false;

	
	if (next_state != ePlayerState::none)
	{
		player_state = PlayerStateFactory::Get((*this), next_state);
		next_state = ePlayerState::none;
	}

	p_state = GetPlayerState();

	//プレイヤーの状態で、処理を変える
	switch (p_state)
	{
		case ePlayerState::idle:
			image = move_animation[0];
			player_state->Initialize();
			player_state->Update();
			break;

		case ePlayerState::walk:
			player_state->Initialize();
			player_state->Update();
			AnimationControl(delta_seconde);
			break;

		case ePlayerState::jump:
			player_state->Update();
			image = move_animation[5];
			break;

		default:
			break;
	}

	
	if (is_ground == false)
	{
		g_velocity += D_GRAVITY / 444.0f;
		velocity.y += g_velocity;
	}

	

	if (hit_flag == false && p_state != jump)
	{
		velocity.y = 3;
	}
	
	hit_flag = false;
	
	if (camera != nullptr)
	{
		float x = camera->Get_CameraLocation().x;
		if (this->location.x - OBJECT_SIZE / 2 < x - D_WIN_MAX_X / 2)
		{
			if (velocity.x < 1.0e-6f)
			{
				velocity.x = 0;
			}
		}
	}
	
	Movement(delta_seconde);

	/*if (velocity.y > 0)
	{
		is_VectorY = DOWN;
	}
	else if (velocity.y < 0)
	{
		is_VectorY = UP;
	}
	else
	{
		is_VectorY = NONE;
	}

	if (velocity.x > 0)
	{
		is_VectorX = RIGHT;
	}
	else if (velocity.x < 0)
	{
		is_VectorX = LEFT;
	}
	else
	{
		is_VectorX = NONE;
	}*/
	
}

void Player::Draw(const Vector2D& screen_offset) const
{
	//親クラスの処理を呼び出す
	__super::Draw(screen_offset);

	Vector2D ul = location - (collision.box_size / 2);
	Vector2D br = location + (collision.box_size / 2);
	DrawBoxAA(ul.x - screen_offset.x, ul.y, br.x - screen_offset.x, br.y, GetColor(255, 0, 0), FALSE);
	DrawCircle(location.x, location.y, 5, GetColor(0, 255, 0), 1);

	/*DrawFormatString(320, 240, GetColor(255, 0, 0), "X:%d", is_VectorX);
	DrawFormatString(360, 240, GetColor(255, 0, 0), "Y:%d", is_VectorY);*/
	DrawFormatString(320, 240, GetColor(255, 0, 0), "vX:%f,vY:%f", velocity.x, velocity.y);
	DrawFormatString(320, 270, GetColor(255, 0, 0), "X:%f,Y:%f", location.x,location.y);
	DrawFormatString(320, 300, GetColor(255, 0, 0), "U:%d R:%d D:%d L:%d",hit[0],hit[1],hit[2],hit[3]);
	DrawFormatString(320, 210, GetColor(255, 0, 0), "state:%d", p_state);
	//DrawFormatString(400, 320, GetColor(255, 0, 0), "idle:%d", p_state);
}

void Player::Finalize()
{
	move_animation.clear();
}

void Player::OnHitCollision(GameObject* hit_object)
{
	hit_flag = true;

	Vector2D diff, dv;
	Vector2D target_boxsize, this_boxsize;
	diff = 0.0f;
	dv = 0.0f;
	Vector2D target_location = hit_object->GetLocation();
	Collision target_collision = hit_object->GetCollision();

	target_boxsize = hit_object->GetCollision().box_size;
	this_boxsize = this->collision.box_size;
	

	//2点間の距離を求める
	diff = this->location - target_location;
	
	if (diff.x > 0)
	{
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

			if (target_collision.object_type == eBlock)
			{
				velocity.y = 0;
			}
		}
		else
		{
			dv.x = (target_location.x + target_boxsize.x / 2) - (this->location.x - this_boxsize.x / 2);
			dv.y = (this->location.y + this_boxsize.y / 2) - (target_location.y - target_boxsize.y / 2);
			
			if (dv.x > dv.y)
			{
				if (target_collision.object_type != eEnemy)
				{
					this->location.y += -dv.y;
					if (target_collision.object_type == eGround || target_collision.object_type == eBlock)
					{
						is_ground = true;
						jump_flag = true;
						g_velocity = 0;
						velocity.y = 0;
					}
				}
				else
				{
					if (hit_object->GetMobility() == true)
					{
						velocity.y = 0;
						velocity.y += -20.0;
					}
				}
			
			}
			else
			{
				this->location.x += dv.x;
			}
		}
	}
	else
	{
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

			if (target_collision.object_type == eBlock)
			{
				velocity.y = 0;
			}
		}
		else
		{
			dv.x = (this->location.x + this_boxsize.x / 2) - (target_location.x - target_boxsize.x / 2);
			dv.y = (this->location.y + this_boxsize.y / 2) - (target_location.y - target_boxsize.y / 2);

			if (dv.x > dv.y)
			{
				if (target_collision.object_type != eEnemy)
				{
					this->location.y += -dv.y;

					if (target_collision.object_type == eGround || target_collision.object_type == eBlock)
					{
						is_ground = true;
						jump_flag = true;
						g_velocity = 0;
						velocity.y = 0;
					}
				}
				else
				{
					if (hit_object->GetMobility() == true)
					{
						velocity.y = 0;
						velocity.y += -20.0;
					}
				}
				
			}
			else
			{
				this->location.x += -dv.x;
			}
		}
	}

	//Vector2D dv = Vector2D(0, 0);

	//Collision target = hit_object->GetCollision();

	//Vector2D t_location = hit_object->GetLocation();

	//float side[2][4];

	////Playerの矩形当たり判定の辺の座標
	//side[0][UP] = this->location.y - (this->collision.box_size.y / 2);
	//side[0][RIGHT] = this->location.x + (this->collision.box_size.x / 2);
	//side[0][DOWN] = this->location.y + (this->collision.box_size.y / 2);
	//side[0][LEFT] = this->location.x - (this->collision.box_size.x / 2);

	////hit_objectの矩形当たり判定の辺の座標
	//side[1][UP] = t_location.y - (target.box_size.y / 2);
	//side[1][RIGHT] = t_location.x + (target.box_size.x / 2);
	//side[1][DOWN] = t_location.y + (target.box_size.y / 2);
	//side[1][LEFT] = t_location.x - (target.box_size.x / 2);

	////当たり判定（上辺）
	//if (HitCheckUp(hit_object, side) == true && is_VectorY == UP)
	//{
	//	jump_flag = false;
	//	velocity.y = 0.0f;
	//	if (target.object_type != eEnemy)
	//	{
	//		dv.y = (this->location.y - collision.box_size.y / 2) - (t_location.y + target.box_size.y / 2);
	//		hit[0] = true;
	//	}
 //		
	//}
	//else
	//{
	//	hit[0] = false;
	//}
	//

	////当たり判定（右辺）
	//if (HitCheckRight(hit_object, side) == true && is_VectorX == RIGHT)
	//{
	//	if (target.object_type != eEnemy)
	//	{
	//		dv.x = (this->location.x + collision.box_size.x / 2) - (t_location.x - target.box_size.x / 2);
	//		hit[1] = true;
	//	}
	//	
	//}
	//else
	//{
	//	hit[1] = false;
	//}
	//
	////当たり判定（下辺）
	//if (HitCheckDown(hit_object, side) == true && is_VectorY == DOWN)
	//{
	//	if (target.object_type != eEnemy)
	//	{
	//		jump_flag = true;
	//		dv.y = (this->location.y + collision.box_size.y / 2) - (t_location.y - target.box_size.y / 2);
	//		hit[2] = true;
	//	}
	//	else if (hit_object->GetMobility() == true)
	//	{
	//		velocity.y = 0;
	//		velocity.y += -20.0;
	//	}
	//
	//	if (target.object_type == eGround)
	//	{
	//		is_ground = true;
	//		g_velocity = 0.0f;
	//		velocity.y = 0;
	//	}
	//}
	//else
	//{
	//	hit[2] = false;
	//}
	//
	////当たり判定（左辺）
	//if (HitCheckLeft(hit_object, side) == true && is_VectorX == LEFT)
	//{
	//	if (target.object_type != eEnemy)
	//	{
	//		dv.x = (this->location.x - collision.box_size.x / 2) - (t_location.x + target.box_size.x / 2);
	//		hit[3] = true;
	//	}
	//	
	//}
	//else
	//{
	//	hit[3] = false;
	//}

	// //めり込んだ分だけ戻る
 // 	this->location += dv * -1;

}


const Collision& Player::GetCollision() const
{
	return collision;
}

const unsigned char Player:: GetZLayer() const
{
	return z_layer;
}

const bool Player:: GetMobility() const
{
	return is_mobility;
}

ePlayerState Player::GetPlayerState() const
{
	return player_state->GetState();
}

void Player::SetNextState(ePlayerState next_state)
{
	this->next_state = next_state;
}

void Player::SetFilp_flag(bool flag)
{
	filp_flag = flag;
}

bool Player::GetFilp_flag()
{
	return filp_flag;
}

Vector2D Player::Get_Velocity()
{
	return this->velocity;
}

void Player::Set_Velocity(Vector2D velocity)
{
	this->velocity = velocity;
}

void Player::Set_IsGround(bool flag)
{
	is_ground = flag;
}

void Player::Set_Camera(Camera* c)
{
	camera = c;
}

void Player::Set_SlideFlag(bool flag)
{
	slide_flag = flag;
}

void Player::Movement(float delta_second)
{
	location += velocity * P_SPEED * delta_second;
}

void Player::AnimationControl(float delta_second)
{
	//移動アニメーション
	animation_time += delta_second;

	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
	
		image = move_animation[animation_num[animation_count]];

		if (slide_flag == true)
		{
			image = move_animation[4];
		}

		animation_count++;
		
		if (animation_count >= 3)
		{
			animation_count = 0;
		}
		
	}

}


