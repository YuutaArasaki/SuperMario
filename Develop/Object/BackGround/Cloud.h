#pragma once
#include "../GameObject.h"

class Cloud : public GameObject
{
private:
	std::vector<int> Cloudimage;
	int number;

public:
	Cloud();
	~Cloud();
	virtual void Initialize() override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;
	virtual const Vector2D& GetLocation() const override;
	virtual const Collision& GetCollision() const override;
	virtual const unsigned char GetZLayer() const override;
	virtual const bool GetMobility() const override;
	void Set_Cloudimage(int number);
};

