#include "WalkingState.h"
#include "../../../Utility/Vector2D.h"
#include "DxLib.h"


WalkingState::WalkingState(class Player* p)
	: PlayerStateBase(p),input(nullptr), speed(0)
{

}

WalkingState::~WalkingState()
{

}

void WalkingState::Initialize()
{
	//“ü—Íî•ñ
	input = InputManager::GetInstance();

}

void WalkingState::Update()
{
	bool input_a, input_d;
	input_a = false;
	input_d = false;

	if (input->GetKeyState(KEY_INPUT_A) == eInputState::Pressed || input->GetKeyState(KEY_INPUT_A) == eInputState::Held)
	{
		if (input->GetKeyState(KEY_INPUT_D) != eInputState::Pressed && input->GetKeyState(KEY_INPUT_D) != eInputState::Held)
		{
			if (speed > -4)
			{
				speed += (float)4 / 60 * -1;
			}

			player->Filp_flag(TRUE);
			player->Set_Velocity(Vector2D(speed, player->Get_Velocity().y));
		}
	
	}
	

	if (input->GetKeyState(KEY_INPUT_D) == eInputState::Pressed || input->GetKeyState(KEY_INPUT_D) == eInputState::Held)
	{
		if (input->GetKeyState(KEY_INPUT_A) != eInputState::Pressed && input->GetKeyState(KEY_INPUT_A) != eInputState::Held)
		{
			if (speed < 4)
			{
				speed += (float)4 / 60;
			}

			player->Filp_flag(FALSE);
			player->Set_Velocity(Vector2D(speed, player->Get_Velocity().y));
		}
		
	}
	
	

	if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		speed = 0;
		player->SetNextState(ePlayerState::jump);
	}

	
	if (input->GetKeyState(KEY_INPUT_D) == eInputState::None && input->GetKeyState(KEY_INPUT_A) == eInputState::None)
	{
		if (speed > 0)
		{
			speed += (float)-4 / 30;
			if (speed < 1.0e-6f)
			{
				speed = 0;
				player->SetNextState(ePlayerState::idle);
			}
		}
		else
		{
			speed += (float)4 / 30;
			if (speed > -1.0e-6f)
			{
				speed = 0;
				player->SetNextState(ePlayerState::idle);
			}
		}
		
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