#pragma once
#include "../Utility/Vector2D.h"
#include "../Object/GameObject.h"
#include "../Object/GameObjectManager.h"

enum eSceneType
{
	eTitle,
	eInGame,
	eResult,
	eExit
};

class SceneBase
{
private:
	Vector2D screen_offset;
	GameObjectManager* objm;

public:
	SceneBase() : screen_offset(0.0f),objm(nullptr)
	{

	}
	
	virtual ~SceneBase()
	{
		Finalize();
	}
	virtual void Initialize()
	{

	}

	virtual eSceneType Update(float delta_second)
	{
		objm = GameObjectManager::GetInstance();

		for (GameObject* obj : objm->GetObjectsList())
		{
			obj->Update(delta_second);
		}

		return GetNowSceneType();
	}

	virtual void Draw() const
	{

		for (GameObject* obj : objm->GetObjectsList())
		{
			obj->Draw(screen_offset);
		}
	}
	virtual void Finalize()
	{

	}

	virtual eSceneType GetNowSceneType() const = 0;
};

