#include "EntityManager.h"
#include "j1Player.h"
#include "Enemy_Air_1.h"

j1EntityManager::j1EntityManager() {
		name.create("entity_manager");
	
		//for (uint i = 0; i < MAX_ENTITIES; ++i)
		//	entity_list[i] = nullptr;
}

j1EntityManager::~j1EntityManager() {}

bool j1EntityManager::Awake(pugi::xml_node&)
{
	return true;
}

bool j1EntityManager::Start()
{
	//for (p2List_item<j1Entity*>* it = entity_list.start; it != nullptr; it = it->next)
	//{
	//	it->data->Start();
	//}

	return true;
}

bool j1EntityManager::PreUpdate()
{

	for (int i = 0; i < MAX_ENTITIES; ++i)
	{
		if (queue[i].type != ENTITY_TYPE::ENTITY_TYPE_NONE)
		{
			SpawnEntity(queue[i]);
			queue[i].type = ENTITY_TYPE::ENTITY_TYPE_NONE;
		}
	}

	return true;
}

bool j1EntityManager::Update(float dt)
{
	//for (p2List_item<j1Entity*>* it = entity_list.start; it != nullptr; it = it->next)
	//{
	//	it->data->Update(dt);
	//}
	return true;
}

bool j1EntityManager::PostUpdate()
{
	//for (p2List_item<j1Entity*>* it = entity_list.start; it != nullptr; it = it->next)
	//{
	//	it->data->PostUpdate();
	//}

	return true;
}

bool j1EntityManager::CleanUp()
{
	bool ret = true;

	//for (p2List_item<j1Entity*>* it = entity_list.end; it != NULL; it = it->prev)
	//{
	//	ret = it->data->CleanUp();
	//}

	//entity_list.clear();
	//player = nullptr;

	return ret;
}

void j1EntityManager::OnCollision(Collider* c1, Collider* c2)
{
	//for (p2List_item<j1Entity*>* it = entity_list.start; it != nullptr; it = it->next)
	//{
	//	if (it->data->collider == c1)
	//	{
	//		it->data->OnCollision(c1, c2);
	//		it->data->OnCollision(c2, c1);
	//		break;
	//	}
	//}
}


void j1EntityManager::CreateEntity(ENTITY_TYPE type, float x, float y)
{
	//switch (type)
	//{
	////case ENTITY_TYPE::ENTITY_TYPE_PLAYER:
	////	next_entity = new j1Player(x, y, type);
	////	if (next_entity != nullptr) entity_list.add(next_entity);
	////	player = (j1Player*)next_entity;
	////	break;

	//case ENTITY_TYPE::ENTITY_TYPE_ENEMY_AIR_1:
	//	next_entity = new j1Enemy_Air_1(x, y, type);
	//	if (next_entity != nullptr) entity_list.add(next_entity);
	//	enemy_air_1 = (j1Enemy_Air_1*)next_entity;
	//	break;
	//}
}

void j1EntityManager::AddEntity(float x, float y, ENTITY_TYPE type)
{
	for (int i = 0; i < MAX_ENTITIES; ++i)
	{
		if (queue[i].type == ENTITY_TYPE::ENTITY_TYPE_NONE)
		{
			queue[i].type = type;
			queue[i].entity_position.x = x;
			queue[i].entity_position.y = y;
			break;
		}
	}
}

void j1EntityManager::SpawnEntity(const EntityInfo& info)
{
	//for (uint i = 0; i < MAX_ENTITIES; ++i)
	//{
	//	if (queue[i].type != ENTITY_TYPE::ENTITY_TYPE_NONE)
	//	{
	//		j1Entity* next_entity_spawn = nullptr;

	//		//switch (info.type) {
	//		//case ENTITY_TYPE::ENTITY_TYPE_ENEMY_AIR_1:
	//		//	next_entity_spawn = new j1Enemy_Air_1(info.entity_position.x, info.entity_position.y, info.type);
	//		//	if (next_entity_spawn != nullptr)
	//		//		entity_list.add(next_entity_spawn);
	//		//	break;
	//		//}

	//		next_entity_spawn->Start();

	//		break;
	//	}
	//}
}

bool j1EntityManager::Load(pugi::xml_node&)
{
	return true;
}

bool j1EntityManager::Save(pugi::xml_node&)
{
	return true;
}
