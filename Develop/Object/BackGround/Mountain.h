#pragma once
#include "../GameObject.h"

enum mountain_type
{
	top,
	right,
	center,
	left
};

class Mountain : public GameObject
{
private:
	std::vector<int> mountain_image;
	int number;

public:
	virtual void Initialize() override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;
	virtual const Vector2D& GetLocation() const override;
	virtual const Collision& GetCollision() const override;
	virtual const unsigned char GetZLayer() const override;
	virtual const bool GetMobility() const override;


};

