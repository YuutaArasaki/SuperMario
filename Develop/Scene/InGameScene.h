#pragma once
#include "SceneBase.h"
#include "../Object/GameObjectManager.h"



class InGameScene : public SceneBase
{
private:
	class GameObjectManager* objm;
	std::vector<int> Cloudimage;
	Player* p;
	int stage_count;
	int load_line;
	int load_column;

public:
	virtual void Initialize() override;
	virtual eSceneType Update(float delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;
	virtual eSceneType GetNowSceneType() const override;
	virtual void CheckCollision(GameObject* target, GameObject* partner) override;

private:
	 void LoadStageMapCSV();		//マップ読み込み処理：引数：map_type = 読み込むマップの種類, x = 読み込みを開始する行
	 void LoadBackGroundCSV();
	 void DeleteObject();
};

