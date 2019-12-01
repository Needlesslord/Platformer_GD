#include "j1App.h"
#include "j1Enemy_Air.h"
#include "j1Collisions.h"
#include "j1Textures.h"
#include <cmath>


j1Enemy_Air::j1Enemy_Air(ENTITY_TYPE type, float x, float y) : j1Entity(ENTITY_TYPE::ENEMY_AIR, x, y)
{
}

j1Enemy_Air::~j1Enemy_Air() {};

bool j1Enemy_Air::Start() {
	img = App->tex->Load("textures/enemy_ghost_angry.png");
	collider = App->collisions->AddCollider({ position.x, position.y, 25, /*TODO: INITIALIZE IPoint for these*/ 23 }, COLLIDER_ENEMY, App->entity_manager);

	return true;
}
bool j1Enemy_Air::CleanUp() {
	App->tex->UnLoad(img);
	return true;
}
bool j1Enemy_Air::PreUpdate() {
	return true;
}

bool j1Enemy_Air::Update(float dt) {
	Draw({0, 0, 25, 23}, position.x, position.y, flip);
	return true;
}

bool j1Enemy_Air::PostUpdate() {
	return true;
}



void j1Enemy_Air::Move(){}

