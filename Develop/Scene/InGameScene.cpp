#include "InGameScene.h"
#include "../Utility/ResourceManager.h"
#include "../Object/Player/Player.h"
#include "../Utility/Collision.h"
#include "../Object/Enemy/Kuribo.h"
#include "../Object/Ground.h"
#include <fstream>


void InGameScene::Initialize()
{
	x = 0;
	Player* p;
	ResourceManager* rm = ResourceManager::GetInstance();
	objm = GameObjectManager::GetInstance();
	p = objm->CreateGameObject<Player>(Vector2D(320, 240));
	camera->Set_Player(p);
	Cloudimage = rm->GetImageResource("Resource/Images/cloud.png", 6, 3, 2, 32, 32);
	LoadStageMapCSV();
}

eSceneType InGameScene::Update(float delta_second)
{

	__super::Update(delta_second);

	camera->Update();

	objm->HitCheck();

	DeleteObject();

	Draw();

	return GetNowSceneType();
}

void InGameScene::Draw() const
{
	DrawFormatString(320,240,GetColor(255, 0, 0), "%f", x);
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
	std::string file_name = "Resource/Map/Map.csv";

	// �w�肳�ꂽ�t�@�C�����J��
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw (file_name + "���J���܂���");
	}

	int x = 0;
	int y = 0;
	int i = 0;

	// �t�@�C�����̕������m�F���Ă���
	while (true)
	{
		// �t�@�C������1�������o����
		int c = fgetc(fp);

		// ���o����������EOF�Ȃ烋�[�v�I��
		if (c == EOF)
		{
			break;
		}
		else if (x >= 20)
		{
			x = 0;
			y++;
		}
		//���o����������'P'�Ȃ�Plaeyr��`�悷��
		/*else if (c == 'P')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
			objm->CreateGameObject<Player>(generate_location);
			x++;
		}*/
		// ���o�����������h�b�g�Ȃ�A�n�ʂ𐶐�
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
		// ���o�����������󔒕����Ȃ�A�������Ȃ��Ŏ��̕��������ɍs��
		else if (c == '0')
		{
			x++;
		}
		else if (c == '2')
		{
			x++;
		}
		// ���o�������������s�����Ȃ�A���̍s�����ɍs��
		/*else if (c == '\n')
		{
			x = 0;
			y++;
		}*/

	}

	// �J�����t�@�C�������
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
			}
		}

	}
}