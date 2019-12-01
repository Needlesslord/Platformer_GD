#ifndef __j1ENTITY_H__
#define __j1ENTITY_H__

#include "j1EntityManager.h"
#include "p2Point.h"
#include "j1Animation.h"

struct SDL_Texture;
struct Collider;
class j1Animation;

enum ENTITY_TYPE;

class j1Entity
{
public:

	j1Entity(ENTITY_TYPE type, float x, float y);
	virtual ~j1Entity();

	virtual bool Start();
	virtual bool PreUpdate();
	virtual bool Update(float dt);
	virtual bool PostUpdate();
	virtual bool CleanUp();
	virtual bool Save(pugi::xml_node&);
	virtual bool Load(pugi::xml_node&);
	virtual void OnCollision(Collider* c1, Collider* c2) {};
	virtual void Draw(SDL_Rect r, float x, float y, bool flip);

	//float abs(float x);


public:

	ENTITY_TYPE type;
	iPoint position;
	Collider* collider = nullptr;
	j1Animation* animation = nullptr;
	SDL_Texture* img = nullptr;
	SDL_Texture* imgM = nullptr;
	bool isAlive = true;

};

#endif 
// __j1ENTITY_H__
