#pragma once
#include "../Utility/Singleton.h"
#include "GameObject.h"
#include <vector>
#include "../Utility/Vector2D.h"
#include "../Utility/Application.h"


class GameObjectManager : public Singleton <GameObjectManager>
{
private:
	std::vector<GameObject*> create_object;
	std::vector<GameObject*> destroy_object;
	std::vector<GameObject*> game_object_list;

public:

	void CheckCreateObject()
	{
		if (!create_object.empty())
		{
			for (GameObject* obj : create_object)
			{
				//�I�u�W�F�N�g��Z���C���[��������
				int z_layer = obj->GetZLayer();
				std::vector<GameObject*>::iterator itr = game_object_list.begin();
				
				//�I�u�W�F�N�g��Z���C���[�̒l���r���A�}������ꏊ�����߂�B
				for (; itr != game_object_list.end(); itr++)
				{
					if (z_layer < (*itr)->GetZLayer())
					{
						break;
					}
				}
				//�I�u�W�F�N�g���X�g�ɑ}������
				game_object_list.insert(itr, obj);
			}
			//�I�u�W�F�N�g�������X�g���������
			create_object.clear();

		}
	}

void CheckDstroyObject()
{
	// �j�����X�g������łȂ��ꍇ�A���X�g���̃I�u�W�F�N�g��j������
	if (!destroy_object.empty())
	{
		for (GameObject* obj : destroy_object)
		{
			std::vector<GameObject*>::iterator itr = game_object_list.begin();	// �I�u�W�F�N�g���X�g�̐擪
			// ���X�g�̖����ɂȂ�܂ő�������
			for (; itr != game_object_list.end(); itr++)
			{
					// ���X�g���ɂ���΁A�폜����
				if ((*itr) == obj)
				{
					game_object_list.erase(itr);
					obj->Finalize();
					delete obj;
					break;
				}
			}
		}
		// ���I�z��̊J��
		destroy_object.clear();

		// ���X�g����Ȃ珈�����I������
		if (destroy_object.empty())
		{
			return;
		}
		// ���X�g���̃I�u�W�F�N�g���폜����
		for (GameObject* obj : destroy_object)
		{
			obj->Finalize();
			delete obj;
		}
		// ���X�g�̉��
		destroy_object.clear();
	}
}
const std::vector<GameObject*>& GetObjectsList() const
{
	return game_object_list;
}
	
template <class OBJECT>
OBJECT* CreateGameObject(const Vector2D & generate_location)
{
	OBJECT* new_instance = new OBJECT();

	GameObjectManager* new_object = dynamic_cast<GameObjectManager*>(new_instance);

	if (new_object == nullptr)
	{
		delete new_instance;

		throw ("�Q�[���I�u�W�F�N�g�������ł��܂���ł���\n");
		return nullptr;
	}

	new_object->Initialize();

	new_object->SetLocation(generate_location);

	game_object_list.push_back(new_object);

	return new_instance;
}

void DestroyGameObject(GameObject* target)
{
	if (target == nullptr)
	{
		return;
	}

	for (GameObject* obj : destroy_object)
	{
		if (obj == target)
		{
			return;
		}
	}

	destroy_object.push_back(target);
}

};
