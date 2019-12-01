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
	collider = App->collisions->AddCollider({ position.x, position.y, 20, /*TODO: INITIALIZE IPoint for these*/ 20 }, COLLIDER_ENEMY, App->entity_manager);

	initial_position_enemy_air = position;

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
	BROFILER_CATEGORY("EnemyAir_Update", Profiler::Color::ForestGreen)

	if (position.x > App->player->position.x) flip = true;
	else flip = false;

	if (isAlive) Draw({0, 0, 25 /*20*/, 23 /*20*/}, position.x, position.y, flip);	
	
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (!HasToAttack()) {
		distance_air = 0;
		move_direction_air = 1;
		if (distance_air > 50) {
			move_direction_air = -1;
		}
		else if (distance_air < 0) {
			move_direction_air = +1;
		}
		else {
			position.x += move_direction_air;
			if (move_direction_air > 0) distance_air--;
			else distance_air++;
		}
	}
	else AttackPlayer(App->entity_manager->enemy_air->initial_position_enemy_air);
	return true;
}

bool j1Enemy_Air::PostUpdate() {
	return true;
}

void j1Enemy_Air::Move(){}

void j1Enemy_Air::MoveIdle(iPoint position) {
	
	//int distance = 0;
	//float move_direction = 1;


	//if (distance > 100) {
	//	move_direction = -1;
	//}
	//else if (distance < 0) {
	//	move_direction = +1;
	//}
	//else {
	//	position.x += move_direction;
	//	if (move_direction > 0) distance--;
	//	else distance++;
	//}

}

void j1Enemy_Air::AttackPlayer(iPoint initial_position_enemy_air) {

	if ((App->player->position.x == position.x) && (App->player->position.y == position.y)) position = initial_position_enemy_air;

	if (App->player->position.x < position.x) position.x--;
	if (App->player->position.y < position.y) position.y--;
	if (App->player->position.x > position.x) position.x++;
	if (App->player->position.y > position.y) position.y++;
}

bool j1Enemy_Air::HasToAttack() {
	bool ret = false;

	if ((App->player->position.x > position.x) && ((App->player->position.x - position.x) < 20)) ret = true;
	if ((App->player->position.x < position.x) && ((App->player->position.x - position.x) > -20)) ret = true;
	if ((App->player->position.y > position.y) && ((App->player->position.y - position.y) < 20)) ret = true;
	if ((App->player->position.y < position.y) && ((App->player->position.y - position.y) > -20)) ret = true;

	return ret;
}

