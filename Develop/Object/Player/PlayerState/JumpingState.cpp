#include "JumpingState.h"
#include "../../../Utility/InputManager.h"

#define JUMP_VECTOR (-15.0f)
#define D_GRAVITY (9.807f)		//�d�͉����x

JumpingState::JumpingState(class Player* p)
	: PlayerStateBase(p),g_velocity(0)
{

}

JumpingState::~JumpingState()
{

}

void JumpingState::Initialize()
{
	this->player->Set_Isground(false);
	this->player->Set_Velocity(Vector2D(player->Get_Velocity().x, JUMP_VECTOR));
	j_velocity = player->Get_Velocity();
	this->player->jump_flag = false;
}

void JumpingState::Update()
{
	InputManager* input = InputManager::GetInstance();

	//�d�͑��x�̌v�Z
	if (j_velocity.y < 0)
	{
		g_velocity += D_GRAVITY / 444.0f;
		j_velocity.y += g_velocity;
		player->Set_Velocity(j_velocity);
	}
	else if (j_velocity.y >= 0 && j_velocity.y <= 9)
	{
		j_velocity.y += 3;
		player->Set_Velocity(j_velocity);
	}

	if (this->player->jump_flag == true)
	{
		if (input->GetKeyState(KEY_INPUT_A) == Pressed || input->GetKeyState(KEY_INPUT_A) == Held
			|| input->GetKeyState(KEY_INPUT_D) == Pressed || input->GetKeyState(KEY_INPUT_D) == Held)
		{
			g_velocity = 0;
			player->SetNextState(ePlayerState::walk);
		}

		if (input->GetKeyState(KEY_INPUT_A) == None && input->GetKeyState(KEY_INPUT_D) == None)
		{
			g_velocity = 0;
			player->SetNextState(ePlayerState::idle);
		}
	}

}
void JumpingState::Draw() const
{

}

void JumpingState::Finalize()
{

}

ePlayerState JumpingState::GetState() const
{
	return ePlayerState::jump;
}