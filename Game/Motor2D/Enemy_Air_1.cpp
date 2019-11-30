//#include "p2Defs.h"
//#include "p2Log.h"
//#include "j1App.h"
//#include "Enemy_Air_1.h"
//#include "j1Textures.h"
//#include "j1Render.h"
//#include "j1Input.h"
//#include "j1Collisions.h"
//#include "j1Window.h"
//#include "j1Player.h"
//#include "j1Audio.h"
//#include "j1Scene.h"
//#include "j1Map.h"
//
//j1Enemy_Air_1::j1Enemy_Air_1(int x, int y, ENTITY_TYPE type) : j1Entity(x, y, ENTITY_TYPE::ENTITY_TYPE_ENEMY_AIR_1)
//{
//	animation = nullptr;
//
//	//flying enemy idle
//	enemy_air_1_idle.PushBack({ 0, 0, 32, 32 });
//	enemy_air_1_idle.PushBack({ 32, 0, 32, 32 });
//	enemy_air_1_idle.PushBack({ 64, 0, 32, 32 });
//	enemy_air_1_idle.PushBack({ 32, 0, 32, 32 });
//	enemy_air_1_idle.PushBack({ 64, 0, 32, 32 });
//	enemy_air_1_idle.speed = 0.125f;
//
//}
//
//j1Enemy_Air_1::~j1Enemy_Air_1() {}
//
//bool j1Enemy_Air_1::Start()
//{
//	entity_sprites = App->tex->Load("textures/Enemy_Air1_Pink_Man.png");
//
//	animation = &enemy_air_1_idle;
//
//	collider = App->collisions->AddCollider({ (int)position.x, (int)position.y, 32, 32 }, COLLIDER_ENEMY, App->entity_manager);
//
//	return true;
//}
//
//bool j1Enemy_Air_1::Update(float dt)
//{
//	if (collider != nullptr)
//		collider->SetPos(position.x, position.y);
//
//	if (dead)
//	{
//		speed.y = 0;
//		//CleanUp();
//	}
//
//
//	else if (!dead)
//	{
//		Move(dt);
//	}
//
//	return true;
//}
//
//bool j1Enemy_Air_1::PostUpdate()
//{
//	return true;
//}
//
//bool j1Enemy_Air_1::CleanUp()
//{
//	App->tex->UnLoad(entity_sprites);
//
//	if (collider != nullptr) {
//		collider->to_delete = true;
//		collider = nullptr;
//	}
//
//	return true;
//}
//
//void j1Enemy_Air_1::Move(float dt) {
//	if (distance_x < 200) position.x--;
//	else if (distance_x>0) position.x++;
//}
//
//void j1Enemy_Air_1::OnCollision(Collider* c1, Collider* c2)
//{
//	if (c1->type == COLLIDER_ENEMY) {
//		if (c2->type == COLLIDER_PLAYER) {
//			dead = true;
//		}
//	}
//
//}