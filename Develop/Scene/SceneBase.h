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

	}
	
	virtual ~SceneBase()
	{
		Finalize();
	}

	virtual void Initialize()
	{
		if (objm == nullptr)
		{
			objm = GameObjectManager::GetInstance();
		}
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
		if (!objm->GetObjectsList().empty())
		{
			for (GameObject* obj : objm->GetObjectsList())
			{
				obj->Draw(screen_offset);
			}
		}
	}

	virtual void Finalize()
	{

	}

	virtual eSceneType GetNowSceneType() const = 0;
};

