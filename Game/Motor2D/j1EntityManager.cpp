//#include "j1App.h"
//#include "j1Input.h"
//#include "j1Render.h"
//#include "j1Textures.h"
//#include "j1Entity.h"
//#include "j1EntityManager.h"
//#include "j1Player.h"
//#include "j1Enemy.h"
//#include "j1Enemy_Air1.h"
//#include "j1Enemy_Air2.h"
//#include "j1Enemy_Land.h"
//#include "j1NPC.h"
//
//#define SPAWN_MARGIN 50
//#define MAX_ENEMIES 50
//
//
//j1EntityManager::j1EntityManager()
//{
//	name.create("entity_manager");
//
//	for (uint i = 0; i < MAX_ENTITIES; ++i)
//		entities[i] = nullptr;
//
//}
//
//j1EntityManager::~j1EntityManager()
//{
//}
//
//bool j1EntityManager::Awake(pugi::xml_node&)
//{
//	return true;
//}
//
//bool j1EntityManager::Start()
//{	
//	sprites_Enemy_Air1 = App->tex->Load("Enemy_Air1_Pink_Man.png");
//
//	//for (p2List_item<j1Entity*>* it = entityList.start; it != nullptr; it = it->next)
//	//{
//	//	it->data->Start();
//	//}
//
//
//	return true;
//}
//
//bool j1EntityManager::PreUpdate()
//{
//	for (uint i = 0; i < MAX_ENTITIES; ++i)
//	{
//		if (queue[i].type != ENTITY_TYPE::ENTITY_TYPE_NONE)
//		{
//			SpawnEnemy(queue[i]);
//			queue[i].type = ENTITY_TYPE::ENTITY_TYPE_NONE;
//			//LOG("Spawning enemy at %d", queue[i].position.x);
//
//		}
//	}
//
//	return true;
//}
//
//bool j1EntityManager::Update()
//{
//	for (uint i = 0; i < MAX_ENTITIES; ++i)
//		if (entities[i] != nullptr) entities[i]->Move();
//
//	for (uint i = 0; i < MAX_ENTITIES; ++i)
//		if (entities[i] != nullptr) entities[i]->Draw(sprites_Enemy_Air1);
//
//	//for (p2List_item<j1Entity*>* it = entityList.start; it != nullptr; it = it->next)
//	//{
//	//	it->data->Update(dt);
//	//}
//
//
//	return true;
//}
//
//bool j1EntityManager::PostUpdate()
//{
//	// check camera position to decide what to spawn
//	for (uint i = 0; i < MAX_ENTITIES; ++i)
//	{
//		if (entities[i] != nullptr)
//		{
//			if (entities[i]->position.x < (App->render->camera.x))
//			{
//				//LOG("DeSpawning enemy at %d", entities[i]->position.x);
//				delete entities[i];
//				entities[i] = nullptr;
//			}
//		}
//	}
//
//	//for (p2List_item<j1Entity*>* it = entityList.start; it != nullptr; it = it->next)
//	//{
//	//	it->data->PostUpdate();
//	//}
//
//	return true;
//}
//
//bool j1EntityManager::CleanUp()
//{
//	bool ret = true;
//
//	App->tex->UnLoad(sprites_Enemy_Air1);
//
//	for (uint i = 0; i < MAX_ENTITIES; ++i)
//	{
//		if (entities[i] != nullptr)
//		{
//			delete entities[i];
//			entities[i] = nullptr;
//		}
//	}
//
//	//for (p2List_item<j1Entity*>* it = entityList.end; it != NULL; it = it->prev)
//	//{
//	//	ret = it->data->CleanUp();
//	//}
//
//	//entityList.clear();
//	//player = nullptr;
//
//
//	return ret;
//}
//
//
//j1Entity* j1EntityManager::EntityCreator(ENTITY_TYPE type, float x, float y)
//{
//	j1Entity* ret = nullptr;
//
//	//switch (type)
//	//{
//	//case ENTITY_TYPE::ENTITY_TYPE_PLAYER:
//	//	ret = new j1Player(type, x, y);
//	//	if (ret != nullptr) {
//	//		entityList.add(ret);
//	//		player = (j1Player*)ret;
//	//	}
//	//	break;
//
//	//case ENTITY_TYPE::ENTITY_TYPE_ENEMY_AIR1:
//	//	ret = new j1Enemy_Air1(type, x, y);
//	//	if (ret != nullptr) {
//	//		entityList.add(ret);
//	//		enemy_air1 = (j1Enemy_Air1*)ret;
//	//	}
//	//	break;
//
//	//case ENTITY_TYPE::ENTITY_TYPE_ENEMY_AIR2:
//	//	ret = new j1Enemy_Air2(type, x, y);
//	//	if (ret != nullptr) {
//	//		entityList.add(ret);
//	//		enemy_air2 = (j1Enemy_Air2*)ret;
//	//	}
//	//	break;
//
//	//case ENTITY_TYPE::ENTITY_TYPE_ENEMY_LAND:
//	//	ret = new j1Enemy_Land(type, x, y);
//	//	if (ret != nullptr) {
//	//		entityList.add(ret);
//	//		enemy_land = (j1Enemy_Land*)ret;
//	//	}
//	//	break;
//
//	//case ENTITY_TYPE::ENTITY_TYPE_NPC:
//	//	ret = new j1NPC(type, x, y);
//	//	if (ret != nullptr) {
//	//		entityList.add(ret);
//	//		npc = (j1NPC*)ret;
//	//	}
//	//	break;
//	//}
//
//
//	return ret;
//}
//
//bool j1EntityManager::AddEntity(ENTITY_TYPE type, float x, float y)
//{
//	bool ret = false;
//
//	for (uint i = 0; i < MAX_ENTITIES; ++i)
//	{
//		if (queue[i].type == ENTITY_TYPE::ENTITY_TYPE_NONE)
//		{
//			queue[i].type = type;
//			queue[i].position.x = x;
//			queue[i].position.y = y;
//			ret = true;
//			break;
//		}
//	}
//
//	return ret;
//}
//
//void j1EntityManager::SpawnEnemy(const EntityInfo& info)
//{
//	//// find room for the new enemy
//	//uint i = 0;
//	//for (; entities[i] != nullptr && i < MAX_ENEMIES; ++i);
//
//	//if (i != MAX_ENEMIES)
//	//{
//	//	switch (info.type)
//	//	{
//	//	case ENTITY_TYPE::ENTITY_TYPE_ENEMY_AIR1:
//	//		entities[i] = new Enemy_Air1(info.position.x, info.position.y);
//	//		break;
//	//	}
//	//}
//
//	for (uint i = 0; i < MAX_ENTITIES; ++i)
//	{
//		if (queue[i].type != ENTITY_TYPE::ENTITY_TYPE_NONE)
//		{
//			j1Entity* ret = nullptr;
//
//			//switch (info.type) {
//			//case ENTITY_TYPE::ENTITY_TYPE_ENEMY_AIR1:
//			//	ret = new j1Enemy_Air1 (info.position.x, info.position.y, info.type);
//
//			//	if (ret != nullptr)
//			//		entityList.add(ret);
//			//	break;
//
//			//case ENTITY_TYPE::ENTITY_TYPE_ENEMY_AIR2:
//			//	ret = new j1Enemy_Air2(info.position.x, info.position.y, info.type);
//
//			//	if (ret != nullptr)
//			//		entityList.add(ret);
//			//	break;
//
//			//case ENTITY_TYPE::ENTITY_TYPE_ENEMY_LAND:
//			//	ret = new j1Enemy_Land(info.position.x, info.position.y, info.type);
//
//			//	if (ret != nullptr)
//			//		entityList.add(ret);
//			//	break;
//			//}
//
//			//ret->Start();
//
//			break;
//		}
//	}
//
//}
//
//void j1EntityManager::OnCollision(Collider* c1, Collider* c2)
//{
//	//for (uint i = 0; i < MAX_ENTITIES; ++i)
//	//{
//	//	if (entities[i] != nullptr && entities[i]->GetCollider() == c1)
//	//	{
//	//		entities[i]->OnCollision(c2);
//	//		delete entities[i];
//	//		entities[i] = nullptr;
//	//		break;
//	//	}
//	//}
//
//	//for (p2List_item<j1Entity*>* it = entityList.start; it != nullptr; it = it->next)
//	//{
//	//	if (it->data->colliders == c1)
//	//	{
//	//		it->data->OnCollision(c1, c2);
//	//		it->data->OnCollision(c2, c1);
//	//		break;
//	//	}
//	//}
//
//}
//
//bool j1EntityManager::Load()
//{
//	return true;
//}
//
//bool j1EntityManager::Save()
//{
//	return true;
//}
