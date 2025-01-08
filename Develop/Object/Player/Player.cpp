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
	collision.box_size = Vector2D(32,32);

	//レイヤー設定
	z_layer = 5;

	//可動性の設定
	is_mobility = true;

	image = move_animation[0];

	filp_flag = FALSE;	

	is_ground = false;

	jump_flag = true;

	is_VectorX = NONE;

	is_VectorY = NONE;

	for (int i = 0; i < 4; i++)
	{
		hit[i] = 0;
	}

	p_state = 0;
}

void Player::Update(float delta_seconde)
{
	ePlayerState state;
	
	if (next_state != ePlayerState::none)
	{
		player_state = PlayerStateFactory::Get((*this), next_state);
		next_state = ePlayerState::none;
	}

	state = GetPlayerState();

	

	//プレイヤーの状態で、処理を変える
	switch (state)
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

	
	if (state != jump)
	{
		velocity.y = 3;
	}

	if (state == idle)
	{
		p_state = 1;
	}
	else
	{
		p_state = 0;
	}
	
	Movement(delta_seconde);

	

	if (velocity.y > 0)
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
	}

	
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
	/*DrawFormatString(320, 240, GetColor(255, 0, 0), "vX:%f,vY:%f", velocity.x, velocity.y);
	DrawFormatString(320, 280, GetColor(255, 0, 0), "X:%f,Y:%f", location.x,location.y);
	DrawFormatString(320, 300, GetColor(255, 0, 0), "U:%d R:%d D:%d L:%d",hit[0],hit[1],hit[2],hit[3]);
	DrawFormatString(320, 320, GetColor(255, 0, 0), "ground:%d", is_ground);
	DrawFormatString(400, 320, GetColor(255, 0, 0), "idle:%d", p_state);*/
}

void Player::Finalize()
{
	move_animation.clear();
}

void Player::OnHitCollision(GameObject* hit_object)
{

	Vector2D dv = Vector2D(0, 0);

	
	Collision target = hit_object->GetCollision();

	Vector2D t_location = hit_object->GetLocation();

	float side[2][4];

	//target1の矩形当たり判定の辺の座標
	side[0][UP] = this->location.y - (this->collision.box_size.y / 2);
	side[0][RIGHT] = this->location.x + (this->collision.box_size.x / 2);
	side[0][DOWN] = this->location.y + (this->collision.box_size.y / 2);
	side[0][LEFT] = this->location.x - (this->collision.box_size.x / 2);

	//target2の矩形当たり判定の辺の座標
	side[1][UP] = t_location.y - (target.box_size.y / 2);
	side[1][RIGHT] = t_location.x + (target.box_size.x / 2);
	side[1][DOWN] = t_location.y + (target.box_size.y / 2);
	side[1][LEFT] = t_location.x - (target.box_size.x / 2);

	//当たり半手（上辺）
	if (HitCheckUp(hit_object, side) == true && is_VectorY == UP)
	{
		jump_flag = false;
		velocity.y = 0.0f;
 		dv.y = (this->location.y - collision.box_size.y / 2) - (t_location.y + target.box_size.y / 2);
		hit[0] = true;
	}
	else
	{
		hit[0] = false;
	}
	

	//当たり判定（右辺）
	if (HitCheckRight(hit_object, side) == true && is_VectorX == RIGHT)
	{

		dv.x = (this->location.x + collision.box_size.x / 2) - (t_location.x - target.box_size.x / 2);
		hit[1] = true;
		
	}
	else
	{
		hit[1] = false;
	}
	
	//当たり判定（下辺）
	if (HitCheckDown(hit_object, side) == true && is_VectorY == DOWN)
	{
		jump_flag = true;
		dv.y = (this->location.y + collision.box_size.y / 2) - (t_location.y - target.box_size.y / 2);
		hit[2] = true;
		if (target.object_type == eGround)
		{
			is_ground = true;
			g_velocity = 0.0f;
			velocity.y = 0.0f;
		}
	}
	else
	{
		hit[2] = false;
	}
	
	//当たり判定（左辺）
	if (HitCheckLeft(hit_object, side) == true && is_VectorX == LEFT)
	{
		dv.x = (this->location.x - collision.box_size.x / 2) - (t_location.x + target.box_size.x / 2);
		hit[3] = true;
	}
	else
	{
		hit[3] = false;
	}

	// めり込んだ分だけ戻る
  	this->location -= dv;

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

void Player::Filp_flag(bool flag)
{
	filp_flag = flag;
}

Vector2D Player::Get_Velocity()
{
	return this->velocity;
}

void Player::Set_Velocity(Vector2D velocity)
{
	this->velocity = velocity;
}

void Player::Set_Isground(bool flag)
{
	is_ground = flag;
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

		animation_count++;
		
		if (animation_count >= 3)
		{
			animation_count = 0;
		}
		
	}

}

Vector2D Player::Get_1Velocity()
{
	Vector2D v1;
	v1 = velocity / GetRefreshRate();
	return v1;	
}
