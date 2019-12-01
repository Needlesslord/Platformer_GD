#ifndef __j1ENTITYMANAGER_H__
#define __j1ENTITYMANAGER_H__

#include "j1Module.h"
#include "p2Defs.h"
#include "p2List.h"
#include "p2Point.h"
#include "j1Entity.h"

#define MAX_ENTITIES 50

class j1Entity;
class j1Player;
class j1Enemy_Air;
class j1Enemy_Land;
class j1NPC;

enum ENTITY_TYPE
{
	PLAYER,
	ENEMY_AIR,
	ENEMY_LAND,
	ENEMY_LAND_INV_GRAV,
	NPC,

	NONE
};

struct SDL_Texture;

struct EntityInfo
{
	ENTITY_TYPE type = ENTITY_TYPE::NONE;
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
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&);
	bool CreateEntity(ENTITY_TYPE type, float x, float y);
	j1Entity* EntityFactory(ENTITY_TYPE type, float x, float y);
	void DestroyAllEntities();

	void OnCollision(Collider* c1, Collider* c2);

public:

	p2List<j1Entity*>	entity_list;
	j1Player*			player = nullptr;
	j1Enemy_Air*		enemy_air = nullptr;
	j1Enemy_Land*		enemy_land = nullptr;
	j1Enemy_Land*		enemy_land_inv_grav = nullptr;
	j1NPC*				npc = nullptr;


private:

	EntityInfo			queue[MAX_ENTITIES];
};

#endif 
