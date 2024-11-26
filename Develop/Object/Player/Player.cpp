#include "Player.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/InputManager.h"
#include "PlayerState/PlayerStateFactory.h"
#include "DxLib.h"

void Player::Initialize()
{
	player_state = PlayerStateFactory::Get((*this), ePlayerState::idle);
	next_state = none;

	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImageResource("Images/Mario/mario.png", 9, 9, 1, 32, 32);

	collision.is_blocking = true;
	collision.object_type = eObjectType::ePlayer;
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eGround);
	collision.hit_object_type.push_back(eObjectType::eItem);

	//レイヤー設定
	z_layer = 5;

	//可動性の設定
	is_mobility = true;

	image = move_animation[0];

	filp_flag = FALSE;	

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
			Movement(delta_seconde);
			AnimationControl(delta_seconde);
			break;

		case ePlayerState::run:
			player_state->Update();
			AnimationControl(delta_seconde);
			break;

		case ePlayerState::jump:
			player_state->Update();
			break;
	}
}

void Player::Draw(const Vector2D& screen_offset) const
{
	//親クラスの処理を呼び出す
	__super::Draw(screen_offset);
}

void Player::Finalize()
{
	move_animation.clear();
}

void Player::OnHitCollision(GameObject*)
{
	
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

void Player::Set_Velocity(Vector2D velocity)
{
	this->velocity = velocity;
}
void Player::Movement(float delta_second)
{
	location += velocity * delta_second;
}

void Player::AnimationControl(float delta_second)
{
	//移動アニメーション
	animation_time += delta_second;

	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;

		if (animation_count >= 3)
		{
			animation_count = 0;
		}
		else
		{
			image = move_animation[animation_num[animation_count]];		
		}
	}
}
