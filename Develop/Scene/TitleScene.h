#pragma once
#include "SceneBase.h"

class TitleScene : public SceneBase
{
public:
	std::vector<int> UI_num;
	std::vector<int> UI_string;
	std::vector<int> UI_coin;

	int num_image;
	int string_image[26];
	int coin_image;

	virtual void Initialize() override;
	virtual eSceneType Update(float delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;
	virtual eSceneType GetNowSceneType() const override;
};

