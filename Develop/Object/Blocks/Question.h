#pragma once
#include "BlockBase.h"

class Question : public BlockBase
{
private:
	std::vector<int> block_image;
	int kara_block;
	float animation_time;
	int animation_count;
	float up_count;
	float down_count;
	bool hit_flag;

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
	
private:
	void AnimationControl(float delta_seconde);
};

