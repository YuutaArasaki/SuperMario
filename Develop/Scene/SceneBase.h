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
protected:
	int image;
private:
	Vector2D screen_offset;
	GameObjectManager* objm;

public:
	SceneBase() : screen_offset(0.0f),objm(nullptr),image(0)
	{
		if (objm == nullptr)
		{
			objm = GameObjectManager::GetInstance();
		}
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

		for (GameObject* obj : objm->GetObjectsList())
		{
			obj->Update(delta_second);
		}

		return GetNowSceneType();
	}

	virtual void Draw() const
	{
		
		GameObjectManager* game = GameObjectManager::GetInstance();
		
		if (!game->GetObjectsList().empty())
		{
			for (GameObject* obj : game->GetObjectsList())
			{
				obj->Draw(screen_offset);
			}
		}
	}

	virtual void Finalize()
	{

	}

	virtual eSceneType GetNowSceneType() const = 0;

	virtual void CheckCollision(GameObject* target, GameObject* partner)
	{

	}
};

