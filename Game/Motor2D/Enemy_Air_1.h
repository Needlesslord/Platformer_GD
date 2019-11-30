//#ifndef __j1BATENEMY_H__
//#define __j1BATENEMY_H__
//
//#include "Entity.h"
//#include "p2Point.h"
//#include "p2List.h"
//#include "p2DynArray.h"
//#include "PugiXml/src/pugixml.hpp"
//
//struct SDL_Texture;
//struct Collider;
//
//enum ENTITY_TYPE;
//
//class j1Enemy_Air_1 : public j1Entity {
//
//public:
//
//	j1Enemy_Air_1(int x, int y, ENTITY_TYPE type);
//	virtual ~j1Enemy_Air_1();
//
//	bool Start();
//	bool Update(float dt);
//	bool PostUpdate();
//	bool CleanUp();
//
//	void OnCollision(Collider* c1, Collider* c2);
//
//	void Move(float dt);
//
//public:
//
//	fPoint speed;
//
//	bool dead = false;
//
//private:
//
//	j1Animation enemy_air_1_idle;
//	j1Animation enemy_air_1_idle_M;
//
//	float distance_x = 100;
//	bool mirror = false;
//
//};
//
//#endif