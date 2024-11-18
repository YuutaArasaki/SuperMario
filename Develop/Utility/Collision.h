#pragma once
#include "Vector2D.h"

enum ObjectType : unsigned char
{
	eNone,
	ePlayer,
	eEnemy,
	eGround,
	eItem

};
class Collision
{
public:
	bool is_blocking;
	Vector2D boxsize;
	Vector2D povot;

};

