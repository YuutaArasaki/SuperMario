#include "Collision.h"

bool Collision::IsCheckHitTarget(eObjectType object_type) const
{
	// �K�p����I�u�W�F�N�g�^�C�v�Ȃ�Atrue
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