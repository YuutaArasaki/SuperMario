#include "Camera.h"

Camera::Camera() : player(nullptr), camera_location(0), pivot_loaction(D_WIN_MAX_X / 2)
{
	
}

Camera::~Camera()
{
	Finalize();
}

void Camera::Update()
{
	//Playerが画面中央よりも前にいるとカメラの位置を更新する
	if (player->GetLocation().x > pivot_loaction)
	{
		//カメラのX座標更新
		camera_location.x = player->GetLocation().x - (D_WIN_MAX_X / 2);

		//左にスクロールできないように基準座標を変える
		/*pivot_loaction = player->GetLocation().x;*/
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
