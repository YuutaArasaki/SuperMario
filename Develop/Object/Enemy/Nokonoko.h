#pragma once
#include "../Character.h"
#include "../../Utility/Camera.h"

class Nokonoko : public Character
{
private:
	std::vector<int> move_animation;
	std::vector<int> die_animation;
	int animation_count;
	float animation_time;
	Camera* camera;
	bool is_ground;
	float g_velocity;
	int image_offset;

public:
	virtual void Initialize() override;
	virtual void Update(float delta_seconde) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;
	virtual void OnHitCollision(GameObject* hit_object) override;
	virtual const Vector2D& GetLocation() const override;
	virtual const Collision& GetCollision() const override;
	virtual const unsigned char GetZLayer() const override;
	virtual const bool GetMobility() const override;
	void Filp_flag(bool flag);
	void Set_Velocity(Vector2D velocity);
	void Set_Camera(Camera* c);

private:
	void Movement(float delta_seconde);
	void AnimationControl(float delta_seconde);
};

