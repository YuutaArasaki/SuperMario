#include "TitleScene.h"
#include "../Utility/ResourceManager.h"
#include "../Utility/InputManager.h"

void TitleScene::Initialize()
{

}

eSceneType TitleScene::Update(float delta_second)
{
	InputManager* input = InputManager::GetInstance();

	if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		return eSceneType::eInGame;
	}

	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	__super::Draw();
	SetFontSize(100);
	DrawFormatString(320, 240, GetColor(0, 0, 0), "TitleScene\n");

}

void TitleScene::Finalize()
{
	__super::Finalize();
}
eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}