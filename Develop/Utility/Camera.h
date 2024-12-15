#pragma once
#include "ProjectConfig.h"
#include "Vector2D.h"
#include "../Object/Player/Player.h"

class Camera
{

private:
	Player* player;
	Vector2D camera_location;
	float pivot_loaction;


public:
	Camera();
	~Camera();

	void Update();
	void Finalize();
	void Set_CameraLocation(Vector2D location);
	Vector2D Get_CameraLocation();
	void Set_Player(Player* p);

};

