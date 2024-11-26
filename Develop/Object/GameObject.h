#pragma once
#include "../Utility/Vector2D.h"
#include "../Utility/Collision.h"

#define OBJECT_SIZE	(24.0f)

class GameObject
{
protected:
	Vector2D location;
	Collision collision;
	int image;
	unsigned char z_layer;
	bool is_mobility;
	bool filp_flag;

public:
	virtual void Initialize();
	virtual void Update(float delta_second);
	virtual void Draw(const Vector2D& screen_offset) const;
	virtual void Finalize();
	virtual void OnHitCollision(GameObject* hit_object);
	virtual const Vector2D& GetLocation() const;
	void SetLocation(const Vector2D location);
	virtual const Collision& GetCollision() const;
	virtual const unsigned char GetZLayer() const;
	virtual const bool GetMobility() const;

};

