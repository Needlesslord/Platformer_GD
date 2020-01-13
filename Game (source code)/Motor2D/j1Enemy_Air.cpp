#include "j1App.h"
#include "j1Player.h"
#include "j1Enemy_Air.h"
#include "j1Collisions.h"
#include "j1Textures.h"
#include "j1Scene.h"
#include "j1Map.h"
#include <cmath>


j1Enemy_Air::j1Enemy_Air(ENTITY_TYPE type, float x, float y) : j1Entity(ENTITY_TYPE::ENEMY_AIR, x, y)
{
}

j1Enemy_Air::~j1Enemy_Air() {};

bool j1Enemy_Air::Start() {
	img = App->tex->Load("textures/enemy_ghost_angry.png");
	imgM = App->tex->Load("textures/enemy_ghost_angry_mirror.png");

	collider = App->collisions->AddCollider({ position.x, position.y, 25, /*TODO: INITIALIZE IPoint for these*/ 23 }, COLLIDER_ENEMY, App->entity_manager);

	speed_following = { 0.5f, 0.5f };

	initial_position_enemy_air = position;

	return true;
}
bool j1Enemy_Air::CleanUp() {
	App->tex->UnLoad(img);
	App->tex->UnLoad(imgM);

	collider->to_delete = true;

	return true;
}
bool j1Enemy_Air::PreUpdate() {

	BROFILER_CATEGORY("EnemyAir_PreUpdate", Profiler::Color::GreenYellow)

	return true;
}

bool j1Enemy_Air::Update(float dt) {

	BROFILER_CATEGORY("EnemyAir_Update", Profiler::Color::ForestGreen)

	if (position.x > App->player->position.x) flip = true;
	else flip = false;

	if (isAlive) Draw({0, 0, 25 /*20*/, 23 /*20*/}, position.x, position.y, flip);	
	
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	//MoveIdle(position);


	if (!HasToAttack()) {
		//distance_air = 0;

		move_direction_air = 1;
		if (distance_air > 10) {
			move_direction_air = -1;
		}
		else if (distance_air < 0) {
			move_direction_air = +1;
		}
		
		position.x += move_direction_air;
		if (move_direction_air > 0) distance_air--;
		else distance_air++;
		

		if (distance_air > 30 && !initial_position_enemy_air.x) int i = 0;
		else if (position.x == initial_position_enemy_air.x)int i = 0;
	}


	if (HasToAttack()) AttackPlayer(App->entity_manager->enemy_air->initial_position_enemy_air);


	//if (App->player->col != nullptr) {
	//	if (abs(App->player->position.x - position.x) <= attack_radar_distance || abs(App->player->position.y - position.y) <= attack_radar_distance && App->player->col->type == COLLIDER_PLAYER)
	//	{
	//		iPoint origin = { App->map->WorldToMap((int)position.x + rePathing.x, (int)position.y + rePathing.y) };
	//		iPoint destination;

	//		if (position.x < App->player->position.x)
	//			destination = { App->map->WorldToMap((int)(App->player->position.x + App->player->col->rect.x), (int)(App->player->position.y + App->player->col->rect.y / 2)) };
	//		else
	//			destination = { App->map->WorldToMap((int)(App->player->position.x), (int)(App->player->position.y + App->player->col->rect.y)) };

	//		path = App->pathfinding->CreatePath(origin, destination);
	//		Move(*path, dt);
	//		has_path = true;

	//	}

	//	else if (has_path)
	//	{
	//		path->Clear();
	//		has_path = false;
	//	}
	//}

	return true;
}

bool j1Enemy_Air::PostUpdate() {

	BROFILER_CATEGORY("EnemyAir_PostUpdate", Profiler::Color::LawnGreen)

	return true;
}

void j1Enemy_Air::Move(p2DynArray<iPoint>& path, float dt)
{
	direction = App->pathfinding->WillMoveTo(path);

	if (direction == MOVE_TO::PATH_8)
	{
		position.y -= speed.y * dt;
	}
	if (direction == MOVE_TO::PATH_2)
	{
		position.y += speed.y * dt;
}
	if (direction == MOVE_TO::PATH_4)
	{
		position.x -= speed.x * dt;
	}
	if (direction == MOVE_TO::PATH_6)
	{
		position.x += speed.x * dt;
	}


}

void j1Enemy_Air::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == COLLIDER_ENEMY) {

		if (c2->type == COLLIDER_PLAYER_SHOT)
		{
			isAlive = false;
			c2->to_delete = true;
			c1->to_delete = true;
			App->player->score += 150;
		}
	}

	if (c1->type == COLLIDER_ENEMY) {
		if (c2->type == COLLIDER_PLAYER && !App->player->godMode) {
			position = initial_position_enemy_air;
		}
	}
}

void j1Enemy_Air::MoveIdle(iPoint position) {
	
	if (!HasToAttack()) {
		distance_air = 0;
		move_direction_air = 1;
		if (distance_air > 30) {
			move_direction_air = -1;
		}
		else if (distance_air < 0 && distance_air>initial_position_enemy_air.x + 200) {
			move_direction_air = +1;
		}
		else {
			position.x += move_direction_air;
			if (move_direction_air > 0) distance_air--;
			else distance_air++;
		}
	}
}

void j1Enemy_Air::AttackPlayer(iPoint initial_position_enemy_air) {

	//if ((App->player->position.x == position.x) && (App->player->position.y == position.y)) position = /*initial_position_enemy_air*/{ position.x + 100, position.y + 100 };

	if (App->player->position.x < position.x) position.x--;
	if (App->player->position.y < position.y) position.y--;
	if (App->player->position.x > position.x) position.x++;
	if (App->player->position.y > position.y) position.y++;
}

bool j1Enemy_Air::HasToAttack() {
	bool ret = false;

	if ((App->player->position.x > position.x) && ((App->player->position.x - position.x) < 20)) ret = true;
	else if ((App->player->position.x < position.x) && ((App->player->position.x - position.x) > -20)) ret = true;
	if ((App->player->position.y > position.y) && ((App->player->position.y - position.y) < 20)) ret = true;
	else if ((App->player->position.y < position.y) && ((App->player->position.y - position.y) > -20)) ret = true;

	return ret;
}
