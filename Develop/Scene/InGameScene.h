#pragma once
#include "SceneBase.h"
#include "../Object/GameObjectManager.h"



class InGameScene : public SceneBase
{
private:
	class GameObjectManager* objm;
	std::vector<int> Cloudimage;
	int sky_image;
	int leaf_image[3];
	int cloud_image[6];
	int mountain_image[6];
	Player* p;
	int stage_count;
	

public:
	virtual void Initialize() override;
	virtual eSceneType Update(float delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;
	virtual eSceneType GetNowSceneType() const override;
	virtual void CheckCollision(GameObject* target, GameObject* partner) override;

private:
	 void LoadStageMapCSV();
	 void LoadBackGroundCSV() const;
	 void DeleteObject();
};

