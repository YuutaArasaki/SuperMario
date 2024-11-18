#include "WalkingState.h"

WalkingState::WalkingState(class Player* p)
	: PlayerStateBase(p)
{

}

WalkingState::~WalkingState()
{

}

void WalkingState::Initialize()
{

}

void WalkingState::Update()
{

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