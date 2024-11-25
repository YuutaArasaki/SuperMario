#pragma once
#include "Vector2D.h"
#include <vector>
enum eObjectType : unsigned char
{
	eNone,
	ePlayer,
	eEnemy,
	eBlock,
	eGround,
	eItem
};
class Collision
{
public:
	bool is_blocking;
	Vector2D box_size;
	Vector2D pivot;
	eObjectType object_type;
	std::vector<eObjectType> hit_object_type;

	bool IsCheckHitTarget(eObjectType object_type) const;

};

