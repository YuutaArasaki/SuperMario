#include "PlayerStateFactory.h"
#include "StoppedState.h"
#include "WalkingState.h"
#include "RunningState.h"
#include "JumpingState.h"

#include "../Player.h"

PlayerStateFactory* PlayerStateFactory::instance = nullptr;

void PlayerStateFactory::Initialize(class Player& p)
{
	idle = new StoppedState(&p);
	walk = new WalkingState(&p);
	run = new RunningState(&p);
	jump = new JumpingState(&p);
}

void PlayerStateFactory::Finalize()
{
	idle->Finalize();
	walk->Finalize();
	run->Finalize();
	jump->Finalize();

	delete idle;
	delete walk;
	delete run;
	delete jump;
}

 PlayerStateBase* PlayerStateFactory::Get(Player& player, ePlayerState state)
{
	 if (instance == nullptr)
	 {
		instance = new PlayerStateFactory;
		instance->Initialize(player);
	 }

	 PlayerStateBase* ret = nullptr;

	 switch (state)
	 {
	 case ePlayerState::idle:
		 instance->idle->Initialize();
		 ret = instance->idle;
		 break;

	 case ePlayerState::walk:
		 instance->walk->Initialize();
		 ret = instance->walk;
		 break;

	 case ePlayerState::run:
		 instance->run->Initialize();
		 ret = instance->run;
		 break;

	 case ePlayerState::jump:
		 instance->jump->Initialize();
		 ret = instance->jump;
		 break;
	 }

	 return ret;
}