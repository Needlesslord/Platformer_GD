#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"

#include "j1Collisions.h"
#include "j1Particles.h"
#include "j1Player.h"
#include "j1Level1.h"
#include "j1Level2.h"


j1Player::j1Player() : j1Module()
{
	/*
	// idle j1Animation (just the ship)
	idle.PushBack({ 66, 1, 32, 14 });

	// move upwards
	up.PushBack({ 100, 1, 32, 14 });
	up.PushBack({ 132, 0, 32, 14 });
	up.loop = false;
	up.speed = 0.1f;

	// Move down
	down.PushBack({ 33, 1, 32, 14 });
	down.PushBack({ 0, 1, 32, 14 });
	down.loop = false;
	down.speed = 0.1f;
	*/
}

j1Player::~j1Player()
{}

bool j1Player::Awake(pugi::xml_node& config){
	return true;
}


bool j1Player::Start()
{
	LOG("Loading player");

	img = App->tex->Load("rtype\ship.png");

	destroyed = false;
	positionX = 50;
	positionY = -100;
	velocityX = 0;
	velocityY = 0;

	/*
	colup = App->collisions->AddCollider({ 150, 120, 14, 10 }, COLLIDER_PLAYER, this);
	coldown = App->collisions->AddCollider({ 150, 120, 14, 10 }, COLLIDER_PLAYER, this);
	colleft = App->collisions->AddCollider({ 150, 120, 1, 18 }, COLLIDER_PLAYER, this);
	colright = App->collisions->AddCollider({ 150, 120, 1, 18 }, COLLIDER_PLAYER, this);
	*/

	//col2 = App->collision->AddCollider({ 0, 120, 16, 16 }, COLLIDER_PLAYER, this);

	jumping = false;

	return true;
}

// Unload assets
bool j1Player::CleanUp()
{
	LOG("Unloading player");

	/*App->tex->UnLoad(img);
	if (colup != nullptr)
		colup->to_delete = true;
	if (coldown != nullptr)
		coldown->to_delete = true;
	if (colleft != nullptr)
		colleft->to_delete = true;
	if (colright != nullptr)
		colright->to_delete = true;*/

	return true;
}

bool j1Player::PreUpdate() {
	return true;
}

// Update: draw background
bool j1Player::Update(float dt)
{
	float speed = 1;
	float t = 1;


	positionX -= velocityX;
	positionY -= velocityY;

	if (App->intro)
	{
		App->render->camera.y = positionY - 250;
	}

	velocityY -= 0.1;


	//if (velocityY < 0) col2->rect.x++;



	if (positionX > 0)
	{
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) velocityX = 2 * speed;
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP) velocityX = 0;
	}


	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) velocityX = (-2) * speed;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP) velocityX = 0;


	if (App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN) positionY = 0;

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && !jumping && velocityY > -1) {
		jumping = true;
		velocityY = 4 * speed;
	}



	/*			------------------------------------PARTICLES--------------------------------------------------

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laser, positionX + 20, positionY, COLLIDER_PLAYER_SHOT);
	}
	*/




	/*colup->SetPos(positionX + 1, positionY);
	coldown->SetPos(positionX + 1, positionY + 22);
	colleft->SetPos(positionX, positionY + 5);
	colright->SetPos(positionX + 15, positionY + 5);*/

	// Draw everything --------------------------------------
	if (destroyed == false)
		App->render->Blit(img, positionX, positionY/*, &(current_j1Animation->GetCurrentFrame())*/);

	return true;
}

bool j1Player::PostUpdate() {
	return true;
}


void j1Player::OnCollision(Collider* c1, Collider* c2)
{
	//if (c1 == coldown && destroyed == false /*&& App->fade->IsFading() == false*/ && velocityY < 0 && c2->type == COLLIDER_WALL && c1->rect.x > c2->rect.x)
	//{
	//	/*

	//	App->fade->FadeToBlack((Module*)App->scene_space, (Module*)App->scene_intro);

	//	App->particles->AddParticle(App->particles->explosion, position.x, position.y, COLLIDER_NONE, 150);
	//	App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, COLLIDER_NONE, 220);
	//	App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, COLLIDER_NONE, 670);
	//	App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, COLLIDER_NONE, 480);
	//	App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, COLLIDER_NONE, 350);

	//	destroyed = true;

	//	*/
	//	positionY = c2->rect.y - 31;
	//	velocityY = 0;
	//	jumping = false;
	//}

	//if (c1 == colup && destroyed == false /*&& App->fade->IsFading() == false*/ && c2->type == COLLIDER_WALL)
	//{
	//	positionY = c2->rect.y + 16;
	//	velocityY = -1;
	//}

	//if (c1 == colright && destroyed == false /*&& App->fade->IsFading() == false*/ && c2->type == COLLIDER_WALL)
	//{
	//	positionX = c2->rect.x - 16;
	//}

	//if (c1 == colleft && destroyed == false /*&& App->fade->IsFading() == false*/ && c2->type == COLLIDER_WALL)
	//{
	//	positionX = c2->rect.x + c2->rect.w;
	//}
}
