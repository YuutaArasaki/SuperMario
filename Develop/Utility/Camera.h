#pragma once
#include "ProjectConfig.h"
#include "Vector2D.h"
#include "../Object/Player/Player.h"

class Camera
{

private:
	class Player* player;
	Vector2D camera_location;
	Vector2D offset;


public:
	Camera();
	~Camera();

	void Update();
	void Finalize();
	Vector2D Get_Offset();
	Vector2D Get_CameraLocation();
	void Set_Player(Player* p);

};

