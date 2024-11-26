#include "InGameScene.h"
#include "../Object/Player/Player.h"

void InGameScene::Initialize()
{
	objm = GameObjectManager::GetInstance();
	Vector2D location = Vector2D(320, 240);
	objm->CreateGameObject<Player>(location);
}

eSceneType InGameScene::Update(float delta_second)
{
	__super::Update(delta_second);

	Draw();

	return GetNowSceneType();
}

void InGameScene::Draw() const
{
	__super::Draw();
}

void InGameScene::Finalize()
{

}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}
