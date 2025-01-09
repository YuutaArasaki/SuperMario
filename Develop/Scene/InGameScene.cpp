#include "InGameScene.h"
#include "../Utility/ResourceManager.h"
#include "../Object/Player/Player.h"
#include "../Utility/Collision.h"
#include "../Object/Enemy/Kuribo.h"
#include "../Object/Ground.h"
#include <fstream>

#define MAX_LOAD_LINE	20;
#define MAX_LOAD_COLUMN	(15);

void InGameScene::Initialize()
{
	p = nullptr;
	load_line = 0;
	ResourceManager* rm = ResourceManager::GetInstance();
	objm = GameObjectManager::GetInstance();
	Cloudimage = rm->GetImageResource("Resource/Images/cloud.png", 6, 3, 2, 32, 32);
	stage_count = 1;
	LoadStageMapCSV(stage_count,load_line);
}

eSceneType InGameScene::Update(float delta_second)
{

	__super::Update(delta_second);

	camera->Update();

	objm->HitCheck();

	DeleteObject();

	Draw();

	if (stage_count < 3)
	{
		if (p->GetLocation().x > 320 && stage_count == 2)
		{
 			LoadStageMapCSV(stage_count, load_line);
		}
	}

	return GetNowSceneType();
}

void InGameScene::Draw() const
{
	DrawFormatString(320,240,GetColor(255, 0, 0), "%f", p->GetLocation().x);
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

void InGameScene::LoadStageMapCSV(int map_type, int x)
{

	FILE* fp = NULL;
	std::string file_name  = "NULL";

	if (map_type == 1)
	{
		file_name = "Resource/Map/Map1.csv";
		stage_count++;
	}
	else if (map_type == 2)
	{
		file_name = "Resource/Map/Map2.csv";
		stage_count++;
	}


	// 指定されたファイルを開く
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// エラーチェック
	if (result != 0)
	{
		throw (file_name + "が開けません");
	}


	int y = 0;
	bool f = false;

	// ファイル内の文字を確認していく
	while (true)
	{

		// ファイルから1文字抽出する
		int c = fgetc(fp);
		
		/*int c = fgetc(fp);*/

		// 抽出した文字がEOFならループ終了
		if (c == EOF)
		{
			load_line += 20;
			break;
		}
		else if (x >= 20 + load_line)
		{
			x = 0 + load_line;
			y++;
		}
		//抽出した文字が'P'ならPlaeyrを描画する
		else if (c == 'P')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
			p = objm->CreateGameObject<Player>(generate_location);
			camera->Set_Player(p);
			x++;
		}
		// 抽出した文字がドットなら、地面を生成
		else if (c == '1')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
			objm->CreateGameObject<Ground>(generate_location);
			x++;
		}
		else if (c == 'K')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
			objm->CreateGameObject<Kuribo>(generate_location);
			x++;
		}
		// 抽出した文字が空白文字なら、生成しないで次の文字を見に行く
		else if (c == '0')
		{
			x++;
		}
		else if (c == '2')
		{
			x++;
		}
		// 抽出した文字が改行文字なら、次の行を見に行く
		/*else if (c == '\n')
		{
			x = 0;
			y++;
		}*/

	}

	// 開いたファイルを閉じる
	fclose(fp);
}

void InGameScene::DeleteObject()
{
	Vector2D camera_location = camera->Get_CameraLocation();
	std::vector<GameObject*> object_list = objm->GetObjectsList();
	
	if (!object_list.empty())
	{
		for (int i = 0; i < object_list.size(); i++)
		{
			 x = (object_list[i]->GetLocation().x + OBJECT_SIZE / 2) - camera_location.x;
			if (0 >= x)
			{
 				objm->DestroyGameObject(object_list[i]);
				/*load_line++;
				LoadStageMapCSV(load_line, 0);*/
			}
		}

	}
}