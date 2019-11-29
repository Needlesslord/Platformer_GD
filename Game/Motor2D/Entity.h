#ifndef __j1ENTITY_H__
#define __j1ENTITY_H__

#include "EntityManager.h"
#include "p2Point.h"
#include "j1Animation.h"

struct SDL_Texture;
struct Collider;
class j1Animation;

enum ENTITY_TYPE;

class j1Entity
{
public:
	j1Entity(int x, int y, ENTITY_TYPE type);

	virtual bool Start();
	virtual bool PreUpdate();
	virtual bool Update(float dt);
	virtual bool PostUpdate();
	virtual bool CleanUp();

	virtual bool Load(pugi::xml_node&);
	virtual bool Save(pugi::xml_node&);

	virtual void OnCollision(Collider* c1, Collider* c2) {};
	virtual void BlitEntitySprites(SDL_Rect r, bool flip = false, float x = 0, float y = 0);

public:

	ENTITY_TYPE type;

	fPoint position;

	Collider* collider = nullptr;
	j1Animation* animation = nullptr;
	SDL_Texture* entity_sprites = nullptr;
};

#endif // __j1ENTITY_H__
