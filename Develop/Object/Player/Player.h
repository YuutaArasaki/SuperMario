#pragma once
#include "../Character.h"
#include "PlayerState/PlayerStateBase.h"
#include <vector>

enum ePlayerState
{
	idle,
	walk,
	run,
	jump
};

class Player : public Character
{
private:
	/*std::vector<int> SmallMario_animation;
	std::vector<int> BigMario_animation;
	std::vector<int> FireMario_animation;*/
	std::vector<int> move_animation;
	class PlayerStateBase* player_state;
	float animation_time;
	int animation_count;

	int animation_num[3] = { 1, 2, 3};	//アニメーションの順番

public:
	virtual void Initialize() override;
	virtual void Update(float delta_seconde) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;
	virtual void OnHitCollision(GameObject*) override;
	ePlayerState GetPlayerState() const;

private:
	void Movement(float delta_second);
	void AnimationControl(float delta_second);

};

