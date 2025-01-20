#include "Cloud.h"
#include "../../Utility/ResourceManager.h"

Cloud::Cloud()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	Cloudimage = rm->GetImageResource("Resource/Images/cloud.png", 6, 3, 2, 32, 32);
	image = Cloudimage[0];
	number = 0;
}

Cloud::~Cloud()
{

}

void Cloud::Initialize()
{
	for (int i = 0; i < Cloudimage.size(); i++)
	{
		if (Cloudimage[i] == NULL)
		{
			throw ("”wŒi(‹ó1)‚ª“Ç‚Ýž‚ß‚Ü‚¹‚ñ‚Å‚µ‚½\n");
		}
	}
}

void Cloud::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Cloud::Finalize()
{

}

const Vector2D& Cloud::GetLocation() const
{
	return location;
}

const Collision& Cloud::GetCollision() const
{
	return collision;
}

const unsigned char Cloud::GetZLayer() const
{
	return z_layer;
}

const bool Cloud::GetMobility() const
{
	return is_mobility;
}

void Cloud::Set_Cloudimage(int number)
{
	
	switch (number)
	{
	case 0:
		image = Cloudimage[0];
		break;

	case 1:
		image = Cloudimage[1];
		break;

	case 2:
		image = Cloudimage[2];
		break;

	case 3:
		image = Cloudimage[3];
		break;

	case 4:
		image = Cloudimage[4];
		break;

	case 5:
		image = Cloudimage[5];
		break;

		default:
		 break;
	}
}