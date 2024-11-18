#pragma once
#include "PlayerStateBase.h"

class WalkingState : public PlayerStateBase
{
public:
	
public:
	WalkingState(class Player* p);
	virtual ~WalkingState();
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;
	virtual ePlayerState GetState() const override;
};

