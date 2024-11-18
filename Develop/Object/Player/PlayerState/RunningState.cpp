#include "RunningState.h"

RunningState::RunningState(class Player* p)
	: PlayerStateBase(p)
{

}

RunningState::~RunningState()
{

}

void RunningState::Initialize()
{

}

void RunningState::Update()
{

}

void RunningState::Draw() const
{

}

void RunningState::Finalize()
{

}

ePlayerState RunningState::GetState() const
{
	return ePlayerState::run;
}