#pragma once
#include "PlayerStateBase.h"
#include "../../../Utility/InputManager.h"

class StoppedState : public PlayerStateBase
{
private:
	InputManager* input;


public:
	StoppedState(class Player* p);
	virtual ~StoppedState();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;
	virtual ePlayerState GetState() const override;
};

