#pragma once
#include "../../../Utility/Singleton.h"
#include "PlayerStateBase.h"


class PlayerStateFactory
{
private:
	 static PlayerStateFactory* instance;
	 class StoppedState* idle;
	 class WalkingState* walk;
	 class RunningState* run;
	 class JumpingState* jump;

private:
	void Initialize(class Player& p);

public:
	static PlayerStateBase* Get(Player& player, ePlayerState state);
	void Finalize();
	
};

