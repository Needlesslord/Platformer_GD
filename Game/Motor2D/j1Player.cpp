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
#include "j1Animation.h"
#include "j1Timer.h"


j1Player::j1Player() : j1Module() {
	name.create("player");
	//idle
	player_idle.PushBack({  0, 0, 23, 28 });
	player_idle.PushBack({ 23, 0, 23, 28 });
	player_idle.PushBack({ 46, 0, 23, 28 });
	player_idle.PushBack({ 69, 0, 23, 28 });
	player_idle.speed = 0.125f;

	player_idle_mirror.PushBack({ 417, 0, 23, 28 });
	player_idle_mirror.PushBack({ 394, 0, 23, 28 });	
	player_idle_mirror.PushBack({ 371, 0, 23, 28 });
	player_idle_mirror.PushBack({ 348, 0, 23, 28 });
	player_idle_mirror.speed = 0.125f;

	player_idle_gravitySwapped.PushBack({  0, 416, 23, 32 });
	player_idle_gravitySwapped.PushBack({ 23, 416, 23, 32 });
	player_idle_gravitySwapped.PushBack({ 46, 416, 23, 32 });
	player_idle_gravitySwapped.PushBack({ 69, 416, 23, 32 });
	player_idle_gravitySwapped.speed = 0.125f;

	player_idle_mirror_gravitySwapped.PushBack({ 417, 416, 23, 32 });
	player_idle_mirror_gravitySwapped.PushBack({ 394, 416, 23, 32 });
	player_idle_mirror_gravitySwapped.PushBack({ 371, 416, 23, 32 });
	player_idle_mirror_gravitySwapped.PushBack({ 348, 416, 23, 32 });
	player_idle_mirror_gravitySwapped.speed = 0.125f;

	//jumping
	player_jumping.PushBack({ 92, 0, 23, 28 });
	player_jumping_mirror.PushBack({ 325, 0, 23, 28 });
	player_jumping_gravitySwapped.PushBack({ 92, 416, 23, 32 });
	player_jumping_mirror_gravitySwapped.PushBack({ 325, 416, 23, 32 });

	//walking
	player_walking.PushBack({  92,  37,  23, 28 });
	player_walking.PushBack({ 115,  37,  23, 28 });
	player_walking.PushBack({ 138,  37,  23, 28 });
	player_walking.PushBack({ 161,  37,  23, 28 });
	player_walking.PushBack({ 184,  37,  25, 28 });
	player_walking.PushBack({ 171,  65,  25, 28 });
	player_walking.PushBack({ 196,  65,  24, 28 });
	player_walking.speed = 0.3f;

	player_walking_mirror.PushBack({ 325,  37,  23, 28 });
	player_walking_mirror.PushBack({ 302,  37,  23, 28 });
	player_walking_mirror.PushBack({ 279,  37,  23, 28 });
	player_walking_mirror.PushBack({ 256,  37,  23, 28 });
	player_walking_mirror.PushBack({ 231,  37,  25, 28 });
	player_walking_mirror.PushBack({ 244,  65,  25, 28 });
	player_walking_mirror.PushBack({ 220,  65,  24, 28 });
	player_walking_mirror.speed = 0.3f;

	player_walking_gravitySwapped.PushBack({  92,  377,  23, 32 });
	player_walking_gravitySwapped.PushBack({ 115,  377,  23, 32 });
	player_walking_gravitySwapped.PushBack({ 138,  377,  23, 32 });
	player_walking_gravitySwapped.PushBack({ 161,  377,  23, 32 });
	player_walking_gravitySwapped.PushBack({ 184,  377,  25, 32 });
	player_walking_gravitySwapped.PushBack({   0,  349,  25, 32 });
	player_walking_gravitySwapped.PushBack({  25,  349,  25, 32 });
	player_walking_gravitySwapped.speed = 0.3f;

	player_walking_mirror_gravitySwapped.PushBack({ 325,  377,  23, 32 });
	player_walking_mirror_gravitySwapped.PushBack({ 302,  377,  23, 32 });
	player_walking_mirror_gravitySwapped.PushBack({ 279,  377,  23, 32 });
	player_walking_mirror_gravitySwapped.PushBack({ 256,  377,  23, 32 });
	player_walking_mirror_gravitySwapped.PushBack({ 231,  377,  25, 32 });
	player_walking_mirror_gravitySwapped.PushBack({ 415,  349,  25, 32 });
	player_walking_mirror_gravitySwapped.PushBack({ 390,  349,  25, 32 });
	player_walking_mirror_gravitySwapped.speed = 0.3f;

	//falling
	player_falling.PushBack({ 192,  96,  32, 32 });
}

j1Player::~j1Player() {}

bool j1Player::Awake(pugi::xml_node& config) {
	folder.create(config.child("folder").child_value());
	texture						= config.child("texture").attribute("source").as_string();
	playerWidth					= config.child("size").attribute("w").as_int();
	playerHeight				= config.child("size").attribute("h").as_int();
	velocity.x					= config.child("velocity").attribute("x").as_float();
	velocity.y					= config.child("velocity").attribute("y").as_float();
	impulse						= config.child("jump_impulse").attribute("y").as_float();
	gravity						= config.child("gravity").attribute("value").as_float();
	feet.x						= config.child("position_scene_1").attribute("x").as_float();
	feet.y						= config.child("position_scene_1").attribute("y").as_float() + config.child("size").attribute("h").as_int();	//PLAYER H + PLAYER Y
	feet.w						= config.child("size").attribute("w").as_int();	//SAME AS PLAYER
	feet.h						= config.child("feet").attribute("h").as_int();
	head.x						= config.child("position_scene_1").attribute("x").as_float();
	head.y						= config.child("position_scene_1").attribute("y").as_float() - 1;
	head.w						= config.child("size").attribute("w").as_int();;
	head.h						= config.child("head").attribute("h").as_int();;
	S_Down						= config.child("s_down").attribute("value").as_bool();
	grounded					= config.child("grounded").attribute("value").as_bool();
	hasDoubleJumped				= config.child("has_doublejumped").attribute("value").as_bool();
	mirror						= config.child("mirror").attribute("value").as_bool();
	alive						= config.child("alive").attribute("value").as_bool();
	AnimationOffstet.x			= config.child("animation_offset").attribute("x").as_int();
	AnimationOffstet.y			= config.child("animation_offset").attribute("y").as_int(); 
	originalPosition_1.x		= config.child("position_scene_1").attribute("x").as_int();
	originalPosition_1.y		= config.child("position_scene_1").attribute("y").as_int();
	originalPosition_2.x		= config.child("position_scene_2").attribute("x").as_int();
	originalPosition_2.y		= config.child("position_scene_2").attribute("y").as_int();
	originalPosition_tutorial.x = config.child("position_scene_tutorial").attribute("x").as_int();
	originalPosition_tutorial.y = config.child("position_scene_tutorial").attribute("y").as_int();
	directWin_1.x				= config.child("win_position_1").attribute("x").as_int();
	directWin_1.y				= config.child("win_position_1").attribute("y").as_int();
	directWin_2.x				= config.child("win_position_2").attribute("x").as_int();
	directWin_2.y				= config.child("win_position_2").attribute("y").as_int();
	return true;
}


bool j1Player::Start() {
	LOG("Loading player");
	current_state = PLAYER_ST_IDLE;
	current_animation = &player_idle;
	colFeet			= App->collisions->AddCollider(feet, COLLIDER_PLAYER, this);
	colHead			= App->collisions->AddCollider(head, COLLIDER_PLAYER, this);
	colRightside	= App->collisions->AddCollider(rightside, COLLIDER_PLAYER, this);
	colLeftside		= App->collisions->AddCollider(leftside, COLLIDER_PLAYER, this);
	col				= App->collisions->AddCollider({ originalPosition_1.x, originalPosition_1.y, playerWidth, playerHeight }, COLLIDER_PLAYER, this);
	gravitySwapped = false;

	player_textures = App->tex->Load("textures/Ninja_Frog.png");
	imgwin = App->tex->Load("textures/imgwin.png");
	lockedDoor = App->tex->Load("textures/candado.png");
	key_tex = App->tex->Load("textures/llave.png");
	key = App->collisions->AddCollider({ 700, 1405, 12, 48 }, COLLIDER_KEY, this);

	if (App->scene->current_scene == 0) {
		position.x = originalPosition_1.x;
		position.y = originalPosition_1.y;
	}
	else if (App->scene->current_scene == 1) {
		position.x = originalPosition_1.x;
		position.y = originalPosition_1.y;
	}
	else if (App->scene->current_scene == 2) {
		position.x = originalPosition_2.x;
		position.y = originalPosition_2.y;
	}
	return true;
}

// Unload assets
bool j1Player::CleanUp() {
	LOG("Unloading player");

	App->tex->UnLoad(player_textures);
	App->tex->UnLoad(imgwin);
	App->tex->UnLoad(lockedDoor);
	App->tex->UnLoad(key_tex);

	if (col != nullptr)col->to_delete = true;
	if (colFeet != nullptr)colFeet->to_delete = true;
	if (colHead != nullptr)colHead->to_delete = true;
	if (colRightside != nullptr) colRightside->to_delete = true;
	if (colLeftside != nullptr) colLeftside->to_delete = true;

	return true;
}

bool j1Player::PreUpdate() {
	return true;
}

// Update: draw background
bool j1Player::Update(float dt) {
	if(mirror && gravitySwapped)		current_animation = &player_idle_mirror_gravitySwapped;
	else if (mirror && !gravitySwapped)	current_animation = &player_idle_mirror;
	else if(!mirror && gravitySwapped)	current_animation = &player_idle_gravitySwapped;
	else								current_animation = &player_idle;

	if (!grounded && !againstRoof) {
		if (mirror && gravitySwapped)		current_animation = &player_jumping_mirror_gravitySwapped;
		else if (mirror && !gravitySwapped)	current_animation = &player_jumping_mirror;
		else if (!mirror && gravitySwapped)	current_animation = &player_jumping_gravitySwapped;
		else								current_animation = &player_jumping;
	}

	if (!godMode) velocity.y -= gravity * dt;

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && !againstLeftSide) {
		position.x -= velocity.x * dt;
		if (gravitySwapped && againstRoof)current_animation = &player_walking_mirror_gravitySwapped;
		else if (!gravitySwapped && grounded)current_animation = &player_walking_mirror;
		mirror = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP) /*RESET*/ { player_walking_mirror_gravitySwapped.Reset(); player_walking_mirror.Reset(); }

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && !againstRightSide) {
		position.x += velocity.x * dt;
		if (gravitySwapped && againstRoof) current_animation = &player_walking_gravitySwapped;
		else if (!gravitySwapped && grounded)current_animation = &player_walking;
		mirror = false;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP) /*RESET*/ { player_walking_gravitySwapped.Reset(); player_walking.Reset(); }

	

	if (justSwapped && swapTimer.ReadSec() > 1) {
		justSwapped = false;
		swapTimer.Stop();
	}

	//DOUBLE JUMP
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && !hasDoubleJumped && !godMode) {
		if (gravitySwapped) { //INVERTED GRAVITY
			if (velocity.y < 0 && !againstRoof) {
				velocity.y = -impulse;
				hasDoubleJumped = true;
			}
		}
		else { 
			if (velocity.y > 0 && !grounded) {
				velocity.y = impulse;
				hasDoubleJumped = true;
			}
		}
	}

	//JUMP
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		if (gravitySwapped) { //INVERTED GRAVITY
			if (againstRoof && !godMode) {
				againstRoof = false;
				velocity.y = -impulse;
				hasDoubleJumped = false;
				//TODO: Play an Fx for jumping
			}
		}
		else {
			if (grounded && !godMode) {
				grounded = false;
				velocity.y = impulse;
				hasDoubleJumped = false;
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && godMode) {
		position.y -= impulse * dt;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && godMode) {
		position.y += impulse * dt;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) { // TODO: TURN OFF
		S_Down = true;
		grounded = false;
	}
	MoveEverything(gravitySwapped, dt);
	if (App->scene->current_scene == 1 && doorLocked)
	{
		App->render->Blit(lockedDoor, directWin_1.x + 18, directWin_1.y - 35);
		App->render->Blit(key_tex, key->rect.x, key->rect.y);
	}
	App->render->Blit(player_textures, position.x - AnimationOffstet.x, position.y - AnimationOffstet.y, &(current_animation->GetCurrentFrame()));
	return true;
}

bool j1Player::PostUpdate() {
	grounded			= false;
	againstLeftSide		= false;
	againstRightSide	= false;
	againstRoof			= false;
	S_Down				= false;
	return true;
}

bool j1Player::Save(pugi::xml_node& node) {
	node.append_child("position_x").append_attribute("value") = position.x;
	node.append_child("position_y").append_attribute("value") = position.y;
	if(gravitySwapped) node.append_child("gravity_swapped").append_attribute("value") = 1;
	else node.append_child("gravity_swapped").append_attribute("value") = 0;
	return true;
}
bool j1Player::Load(pugi::xml_node& node) {
	position.x = node.child("position_x").attribute("value").as_float();
	position.y = node.child("position_y").attribute("value").as_float();
	int gravity = node.child("gravity_swapped").attribute("value").as_int();
	if (gravity == 0) {
		if (gravitySwapped) {
			gravitySwapped = false;
			gravity = 10;
		}
	}
	else if (gravity == 1) {
		if (!gravitySwapped) {
			gravitySwapped = true;
			gravity = -10;
		}
	}
	return true;
}

void j1Player::MoveEverything(bool swapped, float dt) {
	position.y -= velocity.y * dt;
	feet.x = position.x;
	feet.y = position.y + playerHeight;
	head.x = position.x;
	head.y = position.y - head.h;
	rightside.x = position.x + playerWidth;
	rightside.y = position.y;
	leftside.x = position.x - leftside.w;
	leftside.y = position.y;
	col->SetPos(position.x, position.y);
	colFeet->SetPos(feet.x, feet.y);
	colHead->SetPos(head.x, head.y);
	colRightside->SetPos(rightside.x, rightside.y);
	colLeftside->SetPos(leftside.x, leftside.y);
}

bool j1Player::ChangeGravity(bool withImpulse) {
	if (!gravitySwapped) { 
		gravity = gravity * (-1);
		if(withImpulse) velocity.y -= impulse;
		gravitySwapped = true;
		return true; 
	}
	else { 
		gravity = gravity * (-1);
		if (withImpulse) velocity.y += impulse;
		gravitySwapped = false;
		return false; 
	}
}

void j1Player::OnCollision(Collider* c1, Collider* c2) {
	if (c1->type == COLLIDER_PLAYER && !godMode) {
		if (!gravitySwapped) {
			if (c2->type == COLLIDER_PLATFORM && c1 != colRightside && c1 != colLeftside && velocity.y < 0 && 
				!S_Down && position.y + playerHeight < c2->rect.y + 6) {
				velocity.y = 0;
				position.y = c2->rect.y - playerHeight;
				grounded = true;
			}
			else if (c2->type == COLLIDER_WALL) {
				if (c1 != colRightside && c1 != colLeftside && velocity.y < 0 &&
					!S_Down && position.y + playerHeight < c2->rect.y + 15) {
					velocity.y = 0;
					position.y = c2->rect.y - playerHeight;
					grounded = true;
				}

				if (position.y < c2->rect.y + c2->rect.h && position.y + playerHeight > c2->rect.y &&
					position.x + playerWidth >= c2->rect.x && position.x <= c2->rect.x) {
					againstRightSide = true;
					againstLeftSide = false;
				}

				if (position.y < c2->rect.y + c2->rect.h && position.y + playerHeight > c2->rect.y &&
					position.x <= c2->rect.x + c2->rect.w && position.x + playerWidth >= c2->rect.x + c2->rect.w) {
					againstLeftSide = true;
					againstRightSide = false;
				}

				if (c1 != colRightside && c1 != colLeftside && velocity.y > 0 && position.y + 15 > c2->rect.y + c2->rect.h) {
					position.y = c2->rect.y + c2->rect.h;
					velocity.y = 0;
					againstRoof = true;
				}
			}
		}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		else {
			if (c2->type == COLLIDER_PLATFORM &&
				c1 != colRightside && c1 != colLeftside && velocity.y > 0 && 
				!S_Down && position.y + 6 > c2->rect.y + c2->rect.h) {
				velocity.y = 0;
				position.y = c2->rect.y + c2->rect.h - 1;
				againstRoof = true;
			}
			if (c2->type == COLLIDER_WALL) {
				if (c1 != colRightside && c1 != colLeftside && velocity.y > 0 &&
					!S_Down && position.y + 15 > c2->rect.y + c2->rect.h) {
					velocity.y = 0;
					position.y = c2->rect.y + c2->rect.h - 1;
					againstRoof = true;
				}
				if (position.y < c2->rect.y + c2->rect.h && position.y + playerHeight > c2->rect.y &&
					position.x + playerWidth >= c2->rect.x && position.x <= c2->rect.x &&
					c1 != colFeet && c1 != colHead) {
					againstRightSide = true;
					againstLeftSide = false;
				}

				if (position.y < c2->rect.y + c2->rect.h && position.y + playerHeight > c2->rect.y &&
					position.x <= c2->rect.x + c2->rect.w && position.x + playerWidth >= c2->rect.x + c2->rect.w &&
					c1 != colFeet && c1 != colHead) {
					againstLeftSide = true;
					againstRightSide = false;
				}

				if (c1 != colRightside && c1 != colLeftside && velocity.y < 0 && position.y + playerHeight < c2->rect.y + 15) {
					position.y = c2->rect.y - playerHeight;
					velocity.y = 0;
					grounded = true;
				}
			}
		}

		if (c2->type == COLLIDER_KEY) {
			key->to_delete;
			key = nullptr;
			doorLocked = false;
		}

		if (c2->type == COLLIDER_WIN && !doorLocked) {
			if (App->scene->current_scene == 1) {
				App->scene->changeSceneTo(2);
			}
			if (App->scene->current_scene == 2) {
				App->scene->changeSceneTo(1);
			}
		}

		if (c2->type == COLLIDER_DEATH) {
			if (App->scene->current_scene == 1) {
				position.x = originalPosition_1.x;
				position.y = originalPosition_1.y;
			}
			if (App->scene->current_scene == 2) {
				position.x = originalPosition_2.x;
				position.y = originalPosition_2.y;
			}		
           	velocity.y = 0;
			grounded = true;
			ChangeGravity(false);
		}

		if (c2->type == COLLIDER_GRAVITY && !justSwapped) {
			justSwapped = true;
			swapTimer.Start();
			ChangeGravity(true);
		}
	}
}
