#include "InGameScene.h"
#include "../Utility/ResourceManager.h"
#include "../Object/Player/Player.h"
#include "../Utility/Collision.h"
#include "../Object/Enemy/Kuribo.h"
#include "../Object/Enemy/Nokonoko.h"
#include "../Object/Blocks/Ground.h"
#include "../Object/BackGround/Cloud.h"
#include "../Object/BackGround/Sky.h"
#include <fstream>

#define MAX_LOAD_LINE	20;
#define MAX_LOAD_COLUMN	(15);

void InGameScene::Initialize()
{
	p = nullptr;
	ResourceManager* rm = ResourceManager::GetInstance();
	objm = GameObjectManager::GetInstance();
	Cloudimage = rm->GetImageResource("Resource/Images/cloud.png", 6, 3, 2, 32, 32);
	stage_count = 1;
	LoadStageMapCSV();
}

eSceneType InGameScene::Update(float delta_second)
{
	objm->HitCheck();

	__super::Update(delta_second);

	camera->Update();

	DeleteObject();

	Draw();


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

void InGameScene::LoadStageMapCSV()
{

	FILE* fp = NULL;

	std::string file_name = "Resource/Map/Map1.csv";


	// 指定されたファイルを開く
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// エラーチェック
	if (result != 0)
	{
		throw (file_name + "が開けません");
	}

	int x = 0;
	int y = 0;
	Cloud* cloud = nullptr;
	Kuribo* k = nullptr;
	Nokonoko* n = nullptr;

	// ファイル内の文字を確認していく
	while (true)
	{

		// ファイルから1文字抽出する
		int c = fgetc(fp);
	
		// 抽出した文字がEOFならループ終了
		if (c == EOF)
		{
			break;
		}
		//抽出した文字が'P'ならPlaeyrを描画する
		else if (c == 'P')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
			p = objm->CreateGameObject<Player>(generate_location);
			camera->Set_Player(p);
			p->Set_Camera(camera);
			objm->CreateGameObject<Sky>(generate_location);
			x++;
		}
		// 抽出した文字がGなら、地面を生成
		else if (c == 'G')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
			objm->CreateGameObject<Ground>(generate_location);
			x++;
		}
		//抽出した文字がKなら、クリボー（敵）を生成する
		else if (c == 'K')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
			k = objm->CreateGameObject<Kuribo>(generate_location);
			k->Set_Camera(camera);
			objm->CreateGameObject<Sky>(generate_location);
			x++;
		}
		else if (c == 'N')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
			n = objm->CreateGameObject<Nokonoko>(generate_location);
			n->Set_Camera(camera);
			x++;
		}
		// 抽出した文字がSなら空（背景）を生成する
		else if (c == 'S')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
			objm->CreateGameObject<Sky>(generate_location);
			x++;
		}
		//抽出した文字がCなら雲（背景）を生成する
		else if (c == 'C')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
			cloud = objm->CreateGameObject<Cloud>(generate_location);
			c = fgetc(fp);
			if (c == '0')
			{
				cloud->Set_Cloudimage(0);
				x++;
			}
			else if (c == '1')
			{
				cloud->Set_Cloudimage(1);
				x++;
			}
			else if (c == '2')
			{
				cloud->Set_Cloudimage(2);
				x++;
			}
			else if (c == '3')
			{
				cloud->Set_Cloudimage(3);
				x++;
			}
			else if (c == '4')
			{
				cloud->Set_Cloudimage(4);
				x++;
			}
			else if (c == '5')
			{
				cloud->Set_Cloudimage(5);
				x++;
			}
			
		}
		//抽出した文字が0なら何も生成せず、次の文字を見る
		else if (c == '0')
		{
			x++;
		}
		// 抽出した文字が改行文字なら、次の行を見に行く
		else if (c == '\n')
		{
			x = 0;
			y++;
		}

	}

	// 開いたファイルを閉じる
	fclose(fp);
}

void InGameScene::LoadBackGroundCSV()
{

	FILE* fp = NULL;

	std::string file_name = "Resource/Map/BackGround.csv";


	// 指定されたファイルを開く
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// エラーチェック
	if (result != 0)
	{
		throw (file_name + "が開けません");
	}

	int x = 0;
	int y = 0;
	Cloud* cloud = nullptr;
	

	// ファイル内の文字を確認していく
	while (true)
	{

		// ファイルから1文字抽出する
		int c = fgetc(fp);

		// 抽出した文字がEOFならループ終了
		if (c == EOF)
		{
			break;
		}
		// 抽出した文字がSなら空（背景）を生成する
		if (c == '0')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
			objm->CreateGameObject<Sky>(generate_location);
			x++;
		}
		//抽出した文字がCなら雲（背景）を生成する
		else if (c == 'C')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
			cloud = objm->CreateGameObject<Cloud>(generate_location);
			c = fgetc(fp);
			if (c == '0')
			{
				cloud->Set_Cloudimage(0);
				x++;
			}
			else if (c == '1')
			{
				cloud->Set_Cloudimage(1);
				x++;
			}
			else if (c == '2')
			{
				cloud->Set_Cloudimage(2);
				x++;
			}
			else if (c == '3')
			{
				cloud->Set_Cloudimage(3);
				x++;
			}
			else if (c == '4')
			{
				cloud->Set_Cloudimage(4);
				x++;
			}
			else if (c == '5')
			{
				cloud->Set_Cloudimage(5);
				x++;
			}

		}
		//抽出した文字が0なら何も生成せず、次の文字を見る
		else if (c == '0')
		{
			x++;
		}
		// 抽出した文字が改行文字なら、次の行を見に行く
		else if (c == '\n')
		{
			x = 0;
			y++;
		}

	}

	// 開いたファイルを閉じる
	fclose(fp);
}

void InGameScene::DeleteObject()
{
	float offset = camera->Get_Offset().x;
	std::vector<GameObject*> object_list = objm->GetObjectsList();
	
	if (!object_list.empty())
	{
		for (int i = 0; i < object_list.size(); i++)
		{
			int x = (object_list[i]->GetLocation().x + OBJECT_SIZE / 2) - offset;
			if (0 >= x)
			{
 				objm->DestroyGameObject(object_list[i]);
			}
		}

	}
}