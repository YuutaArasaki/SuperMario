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

}

void StoppedState::Update()
{

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