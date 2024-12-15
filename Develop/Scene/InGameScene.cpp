#include "InGameScene.h"
#include "../Object/Player/Player.h"
#include "../Utility/Collision.h"
#include "../Object/Enemy/Kuribo.h"
#include "../Object/Block.h"
#include <fstream>


void InGameScene::Initialize()
{
	objm = GameObjectManager::GetInstance();
	objm->CreateGameObject<Player>(Vector2D(320, 240));
	LoadStageMapCSV();
}

eSceneType InGameScene::Update(float delta_second)
{

	__super::Update(delta_second);

	objm->HitCheck();

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
			objm->CreateGameObject<Block>(generate_location);
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