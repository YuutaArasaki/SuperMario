#include "JumpingState.h"
#include "../../../Utility/InputManager.h"

#define JUMP_VECTOR (-15.0f)

JumpingState::JumpingState(class Player* p)
	: PlayerStateBase(p)
{

}

JumpingState::~JumpingState()
{

}

void JumpingState::Initialize()
{
	this->player->Set_Isground(false);
	this->player->Set_Velocity(Vector2D(player->Get_Velocity().x, JUMP_VECTOR));
	this->player->jump_flag = false;
}

void JumpingState::Update()
{
	InputManager* input = InputManager::GetInstance();

	if (this->player->jump_flag == true)
	{
		if (input->GetKeyState(KEY_INPUT_A) == Pressed || input->GetKeyState(KEY_INPUT_A) == Held
			|| input->GetKeyState(KEY_INPUT_D) == Pressed || input->GetKeyState(KEY_INPUT_D) == Held)
		{
			player->SetNextState(ePlayerState::walk);
		}

		if (input->GetKeyState(KEY_INPUT_A) == None && input->GetKeyState(KEY_INPUT_D) == None)
		{
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