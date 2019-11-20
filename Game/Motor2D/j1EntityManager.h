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
class j1AirEnemy;
class j1LandEnemy;
class j1NPC;
class j1Exit;
class j1SceneEntity;

struct SDL_Texture;

enum ENTITY_TYPE
{
	ENTITY_TYPE_PLAYER,
	ENTITY_TYPE_AIR_ENEMY,
	ENTITY_TYPE_LAND_ENEMY,
	ENTITY_TYPE_NPC,
	ENTITY_TYPE_EXIT,
	ENTITY_TYPE_SCENE_ENTITY,

	ENTITY_TYPE_NONE
};

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
	void AddEnemy(float x, float y, ENTITY_TYPE type);

	void OnCollision(Collider* c1, Collider* c2);

public:

	p2List<j1Entity*>	entityList;
	j1Player*			player = nullptr;
	j1AirEnemy*			air_enemy = nullptr;
	j1LandEnemy*		land_enemy = nullptr;
	j1NPC*				npc = nullptr;
	j1Exit*				exit = nullptr;
	j1SceneEntity*		scene_entity = nullptr;


private:

	EntityInfo			queue[MAX_ENTITIES];

};

#endif 
