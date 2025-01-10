#include "StoppedState.h"
 
StoppedState::StoppedState(class Player* p)
	: PlayerStateBase(p)
	, input(nullptr)
{

}

StoppedState::~StoppedState()
{

}

void StoppedState::Initialize()
{
	input = InputManager::GetInstance();
	player->Set_Velocity(Vector2D(0.0f, 0.0f));
}

void StoppedState::Update()
{
	if (input->GetKeyState(KEY_INPUT_A) == eInputState::Pressed)
	{
		player->SetNextState(ePlayerState::walk);
	}

	if (input->GetKeyState(KEY_INPUT_D) == eInputState::Pressed)
	{
		player->SetNextState(ePlayerState::walk);
	}

	if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		player->SetNextState(ePlayerState::jump);
	}
}

void StoppedState::Draw() const
{

}
void StoppedState::Finalize()
{

}

ePlayerState StoppedState::GetState() const
{
	return ePlayerState::idle;
}