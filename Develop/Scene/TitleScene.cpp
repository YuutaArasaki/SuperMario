#include "TitleScene.h"
#include "../Utility/ResourceManager.h"
#include "../Utility/InputManager.h"
#include "DxLib.h"

void TitleScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	UI_num = rm->GetImageResource("Images/UI/num.png", 15, 15, 1, 16, 16);
	UI_string = rm->GetImageResource("Images/UI/string.png", 26, 26, 1, 16, 16);
	UI_coin = rm->GetImageResource("Images/UI/uicoin.png", 4, 4, 1, 16, 16);
	num_image = UI_num[0];
	for (int i = 0; UI_string.begin() + i < UI_string.end(); i++)
	{
		string_image[i] = UI_string[i];
	}
	coin_image = UI_coin[0];

	__super::Initialize();
}

eSceneType TitleScene::Update(float delta_second)
{
	InputManager* input = InputManager::GetInstance();

 	if (input->GetKeyState(KEY_INPUT_SPACE) == eInputState::Pressed)
	{
		return eSceneType::eInGame;
	}

	return __super::Update(delta_second);
}

void TitleScene::Draw() const
{
	//タイトル背景画像の描画
	LoadGraphScreen(0, 0, "Images/title.png", TRUE);
	//UI：文字MARIOの描画
	LoadGraphScreen(88, 28, "Images/UI/name_mario.png", TRUE);
	//UI：スコアの描画（6桁の数字）
	int x, y;
	x = 96;
	y = 55;
	for (int i = 0; i < 6; i++)
	{
		DrawRotaGraphF(x, y, 1.0, 0.0, num_image, TRUE);
		x += 16;
	}
	//UI：コインの描画
	
	
	__super::Draw();
}

void TitleScene::Finalize()
{
	__super::Finalize();
}
eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}