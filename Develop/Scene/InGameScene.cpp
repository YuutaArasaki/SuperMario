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
	LoadBackGroundCSV();

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

	std::string file_name = "Resource/Map/Stage_Object.csv";


	// �w�肳�ꂽ�t�@�C�����J��
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw (file_name + "���J���܂���");
	}

	int x = 0;
	int y = 0;
	Ground* ground = nullptr;
	Cloud* cloud = nullptr;
	Kuribo* k = nullptr;
	Nokonoko* n = nullptr;

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
		//���o����������'P'�Ȃ�Plaeyr��`�悷��
		else if (c == 'M')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
			p = objm->CreateGameObject<Player>(generate_location);
			camera->Set_Player(p);
			p->Set_Camera(camera);

			x++;
		}
		// ���o����������G�Ȃ�A�n�ʂ𐶐�
		else if (c == 'G')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
			ground = objm->CreateGameObject<Ground>(generate_location);
			ground->Set_Camera(camera);
			x++;
		}
		//���o����������K�Ȃ�A�N���{�[�i�G�j�𐶐�����
		else if (c == 'C')
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
		else if (c == 'B')
		{
			fgetc(fp);
			switch (c)
			{
			case '?':
				x++;
				break;

			case '0':
				x++;
				break;

			case '1':
				x++;
				break;

			case 'H':
				x++;
				break;
			}
		}
		else if (c == 'P')
		{
			fgetc(fp);

			switch (c)
			{
			case 't':
				x++;
				break;

			case '1':
				x++;
				break;
			}
		}
		else if (c == 'F')
		{
			fgetc(fp);
			switch (c)
			{
			case '1':
				x++;
				break;

			case 't':
				x++;
				break;
			}
		}
		//���o����������0�Ȃ牽�����������A���̕���������
		else if (c == '0')
		{
			x++;
		}
		// ���o�������������s�����Ȃ�A���̍s�����ɍs��
		else if (c == '\n')
		{
			x = 0;
			y++;
		}

		
		
	}

	// �J�����t�@�C�������
	fclose(fp);
}

void InGameScene::LoadBackGroundCSV() const
{

	FILE* fp = NULL;

	std::string file_name = "Resource/Map/BackGround.csv";
	int sky_image = LoadGraph("Resource/Images/sora.png");
	int mountain_image[5] = { 0,0,0,0,0, };
	mountain_image[0] = LoadGraph("Resource/Images/mountain_up.png");
	mountain_image[1] = LoadGraph("Resource/Images/mountain_left.png");
	mountain_image[2] = LoadGraph("Resource/Images/mountain_.png");

	// �w�肳�ꂽ�t�@�C�����J��
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw (file_name + "���J���܂���");
	}

	int x = 0;
	int y = 0;
	Cloud* cloud = nullptr;

	// �t�@�C�����̕������m�F���Ă���
	while (true)
	{
		Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
		float Dx = camera->Get_CameraLocation().x + 288;//D_WIN_MAX_X / 2;

		// �t�@�C������1�������o����
		int c = fgetc(fp);

		// ���o����������EOF�Ȃ烋�[�v�I��
		if (c == EOF)
		{
			break;
		}
		// ���o����������S�Ȃ��i�w�i�j�𐶐�����
		if (c == '0')
		{
			if (generate_location.x - OBJECT_SIZE / 2 < Dx)
			{
				DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, sky_image, TRUE);
			}
			x++;
		}
		//���o����������C�Ȃ�_�i�w�i�j�𐶐�����
		else if (c == 'C')
		{
			c = fgetc(fp);
			if (c == '0')
			{
				if (generate_location.x - OBJECT_SIZE / 2 < Dx)
				{
					DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, Cloudimage[0], TRUE);
				}
				x++;
			}
			else if (c == '1')
			{
				if (generate_location.x - OBJECT_SIZE / 2 < Dx)
				{
					DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, Cloudimage[1], TRUE);
				}
				x++;
			}
			else if (c == '2')
			{
				if (generate_location.x - OBJECT_SIZE / 2 < Dx)
				{
					DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, Cloudimage[2], TRUE);
				}
				x++;
			}
			else if (c == '3')
			{
				if (generate_location.x - OBJECT_SIZE / 2 < Dx)
				{
					DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, Cloudimage[3], TRUE);
				}
				x++;
			}
			else if (c == '4')
			{
				if (generate_location.x - OBJECT_SIZE / 2 < Dx)
				{
					DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, Cloudimage[4], TRUE);
				}
				x++;
			}
			else if (c == '5')
			{
				if (generate_location.x - OBJECT_SIZE / 2 < Dx)
				{
					DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, Cloudimage[5], TRUE);
				}
				x++;
			}

		}
		//���o�����������h�b�g�Ȃ牽�����������A���̕���������
		else if (c == '.')
		{
			x++;
		}
		// ���o�������������s�����Ȃ�A���̍s�����ɍs��
		else if (c == '\n')
		{
			x = 0;
			y++;
		}

	}

	// �J�����t�@�C�������
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