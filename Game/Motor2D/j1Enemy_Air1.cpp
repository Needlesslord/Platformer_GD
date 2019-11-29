//#include "j1App.h"
//#include "j1Enemy_Air1.h"
//#include "j1Collisions.h"
//#include <cmath>
//
//
//Enemy_Air1::Enemy_Air1(float x, float y) : Enemy(x, y)
//{
//	fly.PushBack({ 0, 0, 32, 32 });
//	fly.speed = 0.2f;
//	animation = &fly;
//
//	flyM.PushBack({ 0, 32, 32, 32 });
//	flyM.speed = 0.2f;
//	animation = &flyM;
//
//	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY);
//
//	original_y = y;
//}
//
//void Enemy_Air1::Move()
//{
//	//if (distance < 100) {}
//	//else if (going_up)
//	//{
//	//	if (wave > 1.0f)
//	//		going_up = false;
//	//	else
//	//		wave += 0.05f;
//	//}
//	//else
//	//{
//	//	if (wave < -1.0f)
//	//		going_up = true;
//	//	else
//	//		wave -= 0.05f;
//	//}
//	//position.y = original_y + (25.0f * sin(wave));
//	//position.x -= 1;
//}
//
////void Draw(SDL_Texture* sprites) {
////
////	if (collider != nullptr)
////		collider->SetPos(position.x, position.y);
////
////	if (animation != nullptr)
////		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
////
////}
