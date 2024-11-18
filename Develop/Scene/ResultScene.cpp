#include "ResultScene.h"

void ResultScene::Initialize()
{

}

eSceneType ResultScene::Update(float delta_second)
{
	return GetNowSceneType();
}

void ResultScene::Draw() const
{

}

void ResultScene::Finalize()
{

}

eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}