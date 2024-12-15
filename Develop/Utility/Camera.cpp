#include "Camera.h"

Camera::Camera() : player(nullptr), camera_location(0)
{
	
}

Camera::~Camera()
{
	Finalize();
}

void Camera::Update()
{
	if (player->GetLocation().x > D_WIN_MAX_X / 2)
	{
		camera_location.x = player->GetLocation().x - (D_WIN_MAX_X / 2);
	}
}

void Camera::Finalize()
{
	delete player;
}

void Camera::Set_CameraLocation(Vector2D location)
{
	camera_location = location;
}

Vector2D Camera::Get_CameraLocation()
{
	return camera_location;
}

void Camera::Set_Player(Player* p)
{
	player = p;
}
