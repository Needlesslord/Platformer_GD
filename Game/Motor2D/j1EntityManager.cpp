#include "j1EntityManager.h"
#include "j1Player.h"
#include "j1AirEnemy.h"
#include "j1LandEnemy.h"
#include "j1Exit.h"
#include "j1SceneEntity.h"
#include "j1NPC.h"

j1EntityManager::j1EntityManager()
{
}

j1EntityManager::~j1EntityManager()
{
}

bool j1EntityManager::Awake(pugi::xml_node&)
{
	return true;
}

bool j1EntityManager::Start()
{	
	return true;
}

bool j1EntityManager::PreUpdate()
{
	return true;
}

bool j1EntityManager::Update()
{
	return true;
}

bool j1EntityManager::PostUpdate()
{
	return true;
}

bool j1EntityManager::CleanUp()
{
	bool ret = true;

	return ret;
}

void j1EntityManager::OnCollision(Collider* c1, Collider* c2)
{
}

j1Entity* j1EntityManager::EntityCreator(ENTITY_TYPE type, float x, float y)
{
	j1Entity* ret = nullptr;

	return ret;
}

void j1EntityManager::AddEnemy(float x, float y, ENTITY_TYPE type)
{
}

bool j1EntityManager::Load()
{
	return true;
}

bool j1EntityManager::Save()
{
	return true;
}
