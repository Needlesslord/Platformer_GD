//#ifndef __j1ENTITY_H__
//#define __j1ENTITY_H__
//
//#include "p2Point.h"
//#include "j1Animation.h"
//#include "j1Collisions.h"
////#include "j1EntityManager.h"
//
//struct SDL_Texture;
//struct j1Colliders;
//class j1Animation;
//
//enum ENTITY_TYPE;
//
//class j1Entity
//{
//protected:
//	j1Animation* animation = nullptr;
//	Collider* collider = nullptr;
//
//public:
//
//	j1Entity(ENTITY_TYPE type, float x, float y);
//	virtual ~j1Entity();
//
//	bool Awake(pugi::xml_node& config);
//	virtual bool Start();
//	virtual bool PreUpdate();
//	virtual bool Update(float dt);
//	virtual bool PostUpdate();
//	virtual bool CleanUp();
//
//	virtual bool Save();
//	virtual bool Load();
//
//	virtual void Move() {};
//
//	virtual void Draw(SDL_Texture* sprites);
//	virtual void OnCollision(Collider* c1, Collider* c2);
//	const Collider* GetCollider() const;
//
//
//
//
//public:
//
//	ENTITY_TYPE type;
//
//	fPoint position;
//	SDL_Texture* entity_sprites = nullptr;
//};
//
//#endif 
//// __j1ENTITY_H__
