#pragma once
#include "PlayerStateBase.h"

class RunningState : public PlayerStateBase
{
public:
	RunningState(class Player* p);
	virtual ~RunningState();
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;
	virtual ePlayerState GetState() const override;
};

