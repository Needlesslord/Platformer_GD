#include "j1EntityManager.h"
#include "j1Player.h"
#include "j1Enemy_Air.h"
#include "j1Enemy_Land.h"
#include "j1NPC.h"
#include "j1App.h"

j1EntityManager::j1EntityManager() {
}

j1EntityManager::~j1EntityManager() {
}

bool j1EntityManager::Awake(pugi::xml_node&) {
	return true;
}

bool j1EntityManager::Start() {	
	for (p2List_item<j1Entity*>* it = entity_list.start; it != nullptr; it = it->next) {
		it->data->Start();
	}
	return true;
}

bool j1EntityManager::PreUpdate() {
	return true;
}

bool j1EntityManager::Update(float dt) {
	for (p2List_item<j1Entity*>* it = entity_list.start; it != nullptr; it = it->next) {
		it->data->Update(dt);
	}
	return true;
}

bool j1EntityManager::PostUpdate() {
	for (p2List_item<j1Entity*>* it = entity_list.start; it != nullptr; it = it->next) {
		it->data->PostUpdate();
	}
	return true;
}

bool j1EntityManager::CleanUp() {
	bool ret = true;

	for (p2List_item<j1Entity*>* it = entity_list.end; it != NULL; it = it->prev) {
		ret = it->data->CleanUp();
	}
	entity_list.clear();
	return ret;
}

bool j1EntityManager::CreateEntity(ENTITY_TYPE type, float x, float y) {
	if (type == PLAYER) {
		//player = (j1Player*)EntityFactory(ENTITY_TYPE::PLAYER, x, y);
		return true;
	}
	else if (type == ENEMY_AIR) {
		enemy_air = (j1Enemy_Air*) EntityFactory(ENTITY_TYPE::ENEMY_AIR, x, y);
		return true;
	}
	else if (type == ENEMY_LAND) {
		enemy_land = (j1Enemy_Land*)EntityFactory(ENTITY_TYPE::ENEMY_LAND, x, y);
		return true;
	}
	else if (type == ENEMY_LAND_INV_GRAV) {
		enemy_land_inv_grav = (j1Enemy_Land*)EntityFactory(ENTITY_TYPE::ENEMY_LAND_INV_GRAV, x, y);
		return true;
	}
	else if (type == NPC) {
		npc = (j1NPC*)EntityFactory(ENTITY_TYPE::NPC, x, y);
		return true;
	}
	else return false;
}

j1Entity* j1EntityManager::EntityFactory(ENTITY_TYPE type, float x, float y) {
	j1Entity* ret = nullptr;

	if (type == PLAYER) {
		/*ret = new j1Player(type, x, y);

		if (ret != nullptr)
			entityList.add(ret);
		break;*/
	}
	else if (type == ENEMY_AIR) {
		ret = new j1Enemy_Air(type, x, y);
		if (ret != nullptr)	entity_list.add(ret);
	}
	else if (type == ENEMY_LAND) {
		ret = new j1Enemy_Land(type, x, y);
		if (ret != nullptr)entity_list.add(ret);
	}
	else if (type == ENEMY_LAND_INV_GRAV) {
		ret = new j1Enemy_Land(type, x, y);
		if (ret != nullptr)entity_list.add(ret);
	}
	else if (type == NPC) {

	}

	return ret;
}

void j1EntityManager::DestroyAllEntities() {
	for (p2List_item<j1Entity*>* it = entity_list.start; it != nullptr; it = it->next) {
		if (it->data->type != PLAYER) {
			it->data->CleanUp();
			entity_list.del(it);
			RELEASE(it->data);
		}
	}
}

void j1EntityManager::OnCollision(Collider* c1, Collider* c2) {
	for (p2List_item<j1Entity*>* it = entity_list.start; it != nullptr; it = it->next) {
		if (it->data->collider == c1) {
			it->data->OnCollision(c1, c2);
			it->data->OnCollision(c2, c1);
		}
	}
}

bool j1EntityManager::Load(pugi::xml_node&) {
	return true;
}

bool j1EntityManager::Save(pugi::xml_node&) {
	return true;
}
