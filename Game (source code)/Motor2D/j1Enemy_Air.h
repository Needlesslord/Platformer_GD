#ifndef __j1ENEMY_AIR_H__
#define __j1ENEMY_AIR_H__

#include "j1Entity.h"
#include "PugiXml/src/pugixml.hpp"
#include "j1PathFinding.h"
#include "p2List.h"
#include "p2Point.h"


struct SDL_Texture;
struct Collider;
enum ENTITY_TYPE;

class j1Enemy_Air : public j1Entity {
public:

	j1Enemy_Air(ENTITY_TYPE type, float x, float y);
	virtual ~j1Enemy_Air();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void Move(p2DynArray<iPoint>& path, float dt);
	void OnCollision(Collider* c1, Collider* c2);

	void MoveIdle(iPoint position);
	void AttackPlayer(iPoint initial_position_enemy_air);
	bool HasToAttack();

	//void Move();
	fPoint speed;
	fPoint speed_following;

	int distance_air = 0;
	float move_direction_air;
	bool attacking = false;
	iPoint initial_position_enemy_air;

private:
	
	float attack_radar_distance = 150;

	bool flip;
	//j1Animation idle;
	
	// PATHFINDING
	bool has_path = false;
	p2DynArray<iPoint>* path;
	MOVE_TO direction;
	iPoint rePathing;


};

#endif 
// __j1ENEMY_AIR_H__