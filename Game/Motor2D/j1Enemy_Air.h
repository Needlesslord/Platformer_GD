#ifndef __j1ENEMY_AIR_H__
#define __j1ENEMY_AIR_H__

#include "j1Entity.h"
#include "p2Point.h"
#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"

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

	void Move();

};

#endif 
// __j1ENEMY_AIR_H__