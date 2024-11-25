#include "InGameScene.h"


void InGameScene::Initialize()
{
	objm = GameObjectManager::GetInstance();
}

eSceneType InGameScene::Update(float delta_second)
{
	return GetNowSceneType();
}

void InGameScene::Draw() const
{

}

void InGameScene::Finalize()
{

}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}
