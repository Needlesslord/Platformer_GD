#ifndef __j1ENEMY_LAND_H__
#define __j1ENEMY_LAND_H__

#include "j1Entity.h"
#include "PugiXml/src/pugixml.hpp"
#include "j1PathFinding.h"
#include "p2List.h"
#include "p2Point.h"


struct SDL_Texture;
struct Collider;
enum ENTITY_TYPE;

class j1Enemy_Land : public j1Entity {
public:

	j1Enemy_Land(ENTITY_TYPE type, float x, float y);
	virtual ~j1Enemy_Land();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void Move(p2DynArray<iPoint>& path, float dt);
	void OnCollision(Collider* c1, Collider* c2);

private:

	j1Animation* current_animation;

	/*j1Animation idle;
	j1Animation idle_gravity_Swapped;
	j1Animation run;
	j1Animation runM;
	j1Animation run_gravity_Swapped;
	j1Animation runM_gravity_Swapped;
	j1Animation jump;
	j1Animation jumpM;
	j1Animation jump_gravity_Swapped;
	j1Animation jumpM_gravity_Swapped;
	j1Animation fall;
	j1Animation fallM;
	j1Animation fall_gravity_Swapped;
	j1Animation fallM_gravity_Swapped;
	j1Animation hit;
	j1Animation hitM;
	j1Animation hit_gravity_Swapped;
	j1Animation hitM_gravity_Swapped;*/

	int distance; 
	float move_direction;

	// PATHFINDING
	bool has_path = false;
	p2DynArray<iPoint>* path;
	MOVE_TO direction;
	iPoint rePathing;

public:

	void MoveIdle(iPoint position);
	void AttackPlayer(iPoint initial_position_enemy_air);
	bool HasToAttack(float attack_radar_distance);

	//void Move();
	fPoint speed;
	fPoint speed_following;

	int distance_land;
	float move_direction_land;
	bool attacking = false;
	iPoint initial_position_enemy_land;

private:

	float attack_radar_distance = 30;
	bool flip;
	bool jumping = false;

};

#endif 
// __j1ENEMY_LAND_H__