#include "WalkingState.h"
#include "../../../Utility/Vector2D.h"



WalkingState::WalkingState(class Player* p)
	: PlayerStateBase(p),input(nullptr), speed(0)
{

}

WalkingState::~WalkingState()
{

}

void WalkingState::Initialize()
{
	//���͏��
	input = InputManager::GetInstance();

}

void WalkingState::Update()
{
	bool input_a, input_d;
	input_a = false;
	input_d = false;

	if (input->GetKeyState(KEY_INPUT_A) == eInputState::Pressed || input->GetKeyState(KEY_INPUT_A) == eInputState::Held)
	{
		
		player->Filp_flag(TRUE);
		player->Set_Velocity(Vector2D(-3.0f + speed, 0.0f));
	
	}
	


	if (input->GetKeyState(KEY_INPUT_D) == eInputState::Pressed || input->GetKeyState(KEY_INPUT_D) == eInputState::Held)
	{
		player->Filp_flag(FALSE);
		player->Set_Velocity(Vector2D(3.0f + speed, 0.0f));
		
	}
	
	

	if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		player->SetNextState(ePlayerState::jump);
	}

	
	if (input->GetKeyState(KEY_INPUT_D) == eInputState::None && input->GetKeyState(KEY_INPUT_A) == eInputState::None)
	{
		player->SetNextState(ePlayerState::idle);
	}
	

	
}

void WalkingState::Draw() const
{

}

void WalkingState::Finalize()
{

}

ePlayerState WalkingState::GetState() const
{
	return ePlayerState::walk;
}