#pragma once
#include "../Player.h"

class PlayerStateBase
{
protected:
	class Player* player;

public:
	PlayerStateBase(Player* p) : player(p)
	{

	}

	~PlayerStateBase() = default;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() const = 0;
	virtual void Finalize() = 0;
	virtual enum ePlayerState GetState() const = 0;
};
