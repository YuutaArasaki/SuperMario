#pragma once
#include "../Character.h"
#include "PlayerState/PlayerStateBase.h"
#include "../../Utility/Camera.h"
#include <vector>

enum ePlayerState
{
	idle,
	walk,
	jump,
	none
};

enum ePlayer_Level
{
	Small,
	Big,
	Fire
};

class Player : public Character
{
private:
	/*std::vector<int> SmallMario_animation;
	std::vector<int> BigMario_animation;
	std::vector<int> FireMario_animation;*/
	std::vector<int> move_animation;
	class PlayerStateBase* player_state;
	ePlayerState next_state;
	float animation_time;
	int animation_count;
	float g_velocity;
	bool is_ground;
	float x;
	bool hit[4];
	ePlayerState p_state;
	class Camera* camera;

public:
	bool jump_flag;
	bool slide_flag;
	int animation_num[3] = { 1, 2, 3};	//アニメーションの順番

public:
	virtual void Initialize() override;
	virtual void Update(float delta_seconde) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;
	virtual void OnHitCollision(GameObject* hit_object) override;
	virtual const Collision& GetCollision() const override;
	virtual const unsigned char GetZLayer() const override;
	virtual const bool GetMobility() const override;
	ePlayerState GetPlayerState() const;
	void SetNextState(ePlayerState next_state);
	void SetFilp_flag(bool flag);
	bool GetFilp_flag();
	Vector2D Get_Velocity();
	void Set_Velocity(Vector2D velocity_x);
	void Set_IsGround(bool flag);
	void Set_Camera(Camera* c);
	void Set_SlideFlag(bool flag);

private:
	void Movement(float delta_second);
	void AnimationControl(float delta_second);

};

