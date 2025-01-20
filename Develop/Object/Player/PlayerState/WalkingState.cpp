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

	/*float x = player->Get_Velocity().x;
	if (x > 0 || x < 0)
	{
		speed = x;
	}*/
}

void WalkingState::Update()
{
	eInputState input_a, input_d;
	input_a = input->GetKeyState(KEY_INPUT_A);
	input_d = input->GetKeyState(KEY_INPUT_D);

	if (input_a == eInputState::Pressed || input_a == eInputState::Held)
	{
		if (input_d != eInputState::Pressed && input_d != eInputState::Held)
		{
			if (speed > 0)
			{
				player->slide_flag = true;
			}
			else
			{
				player->Filp_flag(TRUE);
			}

			if (speed > -4)
			{
				speed += (float)4 / 60 * -1;
			}
			player->Set_Velocity(Vector2D(speed, player->Get_Velocity().y));
		}
	
	}
	

	if (input_d == eInputState::Pressed || input_d == eInputState::Held)
	{
		if (input_a != eInputState::Pressed && input_a != eInputState::Held)
		{
			if (speed < 0)
			{
				player->slide_flag = true;
			}
			else
			{
				player->Filp_flag(FALSE);
			}

			if (speed < 4)
			{
				speed += (float)4 / 60;
			}
			player->Set_Velocity(Vector2D(speed, player->Get_Velocity().y));
		}
		
	}
	
	
	if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		speed = 0;
		player->SetNextState(ePlayerState::jump);
	}

	
	if (input_d == eInputState::None && input_a == eInputState::None)
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