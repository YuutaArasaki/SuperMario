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
	//Player����ʒ��������O�ɂ���ƃJ�����̈ʒu���X�V����
	if (player->GetLocation().x > pivot_loaction)
	{
		//�J������X���W�X�V
		camera_location.x = player->GetLocation().x - (D_WIN_MAX_X / 2);

		//���ɃX�N���[���ł��Ȃ��悤�Ɋ���W��ς���
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
