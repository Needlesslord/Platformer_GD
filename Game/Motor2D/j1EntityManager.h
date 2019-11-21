#ifndef __j1ENTITYMANAGER_H__
#define __j1ENTITYMANAGER_H__

#include "j1Module.h"
#include "p2Defs.h"
#include "p2List.h"
#include "p2Point.h"
#include "j1Entity.h"
#include "j1EntityManager.h"
#include "j1Player.h"
#include "j1Enemy.h"
#include "j1Enemy_Air1.h"
#include "j1Enemy_Land.h"
#include "j1Exit.h"
#include "j1SceneEntity.h"
#include "j1NPC.h"

#define MAX_ENTITIES 50

class j1Entity;
class j1Player;
class j1Enemy_Air1;
class j1Enemy_Land;
class j1NPC;
class j1Exit;
class j1SceneEntity;

enum ENTITY_TYPE
{
	ENTITY_TYPE_PLAYER,
	ENTITY_TYPE_ENEMY_AIR1,
	ENTITY_TYPE_ENEMY_LAND,
	ENTITY_TYPE_NPC,
	ENTITY_TYPE_EXIT,
	ENTITY_TYPE_SCENE_ENTITY,

	ENTITY_TYPE_NONE
};

struct SDL_Texture;

struct EntityInfo
{
	ENTITY_TYPE type = ENTITY_TYPE::ENTITY_TYPE_NONE;
	fPoint position;
};

class j1EntityManager : public j1Module
{
public:

	j1EntityManager();
	~j1EntityManager();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool CleanUp();

	bool Load();
	bool Save();

	j1Entity* EntityCreator(ENTITY_TYPE type, float x = 0, float y = 0);
	bool AddEntity(ENTITY_TYPE type, float x, float y);
	void SpawnEnemy(const EntityInfo& info);

	void OnCollision(Collider* c1, Collider* c2);

public:

	p2List<j1Entity*>	entityList;
	j1Player*			player = nullptr;
	j1Enemy_Air1*		enemy_air1 = nullptr;
	j1Enemy_Land*		enemy_land = nullptr;
	j1NPC*				npc = nullptr;
	j1Exit*				exit = nullptr;
	j1SceneEntity*		scene_entity = nullptr;


private:

	EntityInfo			queue[MAX_ENTITIES];
	j1Entity*			entities[MAX_ENTITIES];
	//j1Enemy*			enemies[MAX_ENEMIES];
	SDL_Texture*		sprites;

};

#endif 
