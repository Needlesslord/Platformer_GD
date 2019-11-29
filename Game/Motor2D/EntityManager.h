#ifndef __j1ENTITYMANAGER_H__
#define __j1ENTITYMANAGER_H__

#include "j1Module.h"
#include "Entity.h"
#include "p2Defs.h"
#include "p2List.h"
#include "p2Point.h"

#define MAX_ENTITIES 50

class Entity;
class Enemy_Air_1;
class j1Player;

struct SDL_Texture;

enum ENTITY_TYPE
{
	ENTITY_TYPE_NONE,

	ENTITY_TYPE_PLAYER,
	ENTITY_TYPE_ENEMY_AIR_1,

};

struct EntityInfo
{
	ENTITY_TYPE type = ENTITY_TYPE::ENTITY_TYPE_NONE;
	fPoint entity_position;
};

class j1EntityManager : public j1Module
{
public:

	j1EntityManager();
	~j1EntityManager();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&);

	//j1Entity* EntityFactory(ENTITY_TYPE type, float x = 0, float y = 0);
	void CreateEntity(ENTITY_TYPE type, float x = 0, float y = 0);
	//void AddEnemy(float x, float y, ENTITY_TYPE type);
	void AddEntity(float x, float y, ENTITY_TYPE type);
	//void SpawnEnemy(const EntityInfo& info);
	void SpawnEntity(const EntityInfo& info);
	//void DestroyAllEntities();

	void OnCollision(Collider* c1, Collider* c2);

public:

	//p2List<j1Entity*>		entity_list;
	//j1Player*				player = nullptr;
	//j1Enemy_Air_1*		enemy_air_1 = nullptr;
	//j1Entity*				next_entity = nullptr;

private:

	EntityInfo			queue[MAX_ENTITIES];

};

#endif __j1ENTITYMANAGER_H__

