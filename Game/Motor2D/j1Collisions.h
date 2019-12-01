#pragma once
#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 560

#include "j1Module.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_PLATFORM,
	COLLIDER_PLAYER,
	COLLIDER_ENEMY,
	COLLIDER_PLAYER_SHOT,
	COLLIDER_ENEMY_SHOT,
	COLLIDER_WIN,
	COLLIDER_DEATH,
	COLLIDER_NPC,
	COLLIDER_GRAVITY,
	COLLIDER_KEY,
	COLLIDER_CHECKPOINT,

	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	j1Module* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, j1Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x; 
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class j1Collisions : public j1Module {
public:
	j1Collisions();
	virtual ~j1Collisions();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool Load();
	bool Save();
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback = nullptr);

private:

	Collider* colliders[MAX_COLLIDERS] = { nullptr };
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	int getDebug;
	bool debug;		
};

#endif // __ModuleCollision_H__