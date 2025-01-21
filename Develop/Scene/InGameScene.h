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
	 void LoadStageMapCSV();		//�}�b�v�ǂݍ��ݏ����F�����Fmap_type = �ǂݍ��ރ}�b�v�̎��, x = �ǂݍ��݂��J�n����s
	 void LoadBackGroundCSV();
	 void DeleteObject();
};

