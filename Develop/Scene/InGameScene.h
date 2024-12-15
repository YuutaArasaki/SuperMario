#pragma once
#include "SceneBase.h"
#include "../Object/GameObjectManager.h"

class InGameScene : public SceneBase
{
private:
	class GameObjectManager* objm;

public:
	virtual void Initialize() override;
	virtual eSceneType Update(float delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;
	virtual eSceneType GetNowSceneType() const override;
	virtual void CheckCollision(GameObject* target, GameObject* partner) override;

private:
	 void LoadStageMapCSV();
};

