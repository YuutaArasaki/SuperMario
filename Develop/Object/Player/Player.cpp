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
	collision.box_size = Vector2D(32,32);

	//���C���[�ݒ�
	z_layer = 5;

	//�����̐ݒ�
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

	//�v���C���[�̏�ԂŁA������ς���
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
	//�e�N���X�̏������Ăяo��
	__super::Draw(screen_offset);

	Vector2D ul = location - (collision.box_size / 2);
	Vector2D br = location + (collision.box_size / 2);
	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
}

void Player::Finalize()
{
	move_animation.clear();
}

void Player::OnHitCollision(GameObject* hit_object)
{
	Collision hc = hit_object->GetCollision();

	// �߂荞�񂾍���
	float diff = (this->GetCollision().box_size / 2 + hc.box_size / 2 - dv.Length();

	// diff�̕������߂�
	location += dv.Normalize() * diff;
}
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
	//�ړ��A�j���[�V����
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
