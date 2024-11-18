#include "JumpingState.h"

JumpingState::JumpingState(class Player* p)
	: PlayerStateBase(p)
{

}

JumpingState::~JumpingState()
{

}

void JumpingState::Initialize()
{

}

void JumpingState::Update()
{

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