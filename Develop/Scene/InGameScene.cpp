#include "InGameScene.h"
#include "../Object/Player/Player.h"
#include "../Utility/Collision.h"
#include "../Object/Enemy/Kuribo.h"

void InGameScene::Initialize()
{
	objm = GameObjectManager::GetInstance();
	Vector2D location = Vector2D(320, 240);
	objm->CreateGameObject<Player>(location);
	objm->CreateGameObject<Kuribo>(Vector2D(360, 240));
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

void InGameScene::CheckCollision(GameObject* target, GameObject* partner)
{
	if (target == nullptr || partner == nullptr)
	{
		return;
	}

	Collision tc = target->GetCollision();
	Collision pc = partner->GetCollision();

	if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
	{
		tc.pivot += target->GetLocation();
		pc.pivot += partner->GetLocation();

		if (tc.IsCheckHitCollision(tc, pc))
		{
			target->OnHitCollision(partner);
			partner->OnHitCollision(target);
		}
	}

	
}
