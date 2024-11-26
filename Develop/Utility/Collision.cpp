#include "Collision.h"

bool Collision::IsCheckHitTarget(eObjectType object_type) const
{
	// 適用するオブジェクトタイプなら、true
	for (eObjectType type : hit_object_type)
	{
		if (type == object_type)
		{
			return true;
		}
	}

	return false;
}

bool Collision::IsCheckHitCollision(Collision target1, Collision target2)
{
	target1.box_size;
}