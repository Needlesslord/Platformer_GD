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
#include "j1UI.h"
#include "Brofiler.h"


j1Player::j1Player() : j1Module() {
	name.create("player");
	//idle
	player_idle.PushBack({  0, 0, 23, 28 });
	player_idle.PushBack({ 23, 0, 23, 28 });
	player_idle.PushBack({ 46, 0, 23, 28 });
	player_idle.PushBack({ 69, 0, 23, 28 });

	player_idle_mirror.PushBack({ 417, 0, 23, 28 });
	player_idle_mirror.PushBack({ 394, 0, 23, 28 });	
	player_idle_mirror.PushBack({ 371, 0, 23, 28 });
	player_idle_mirror.PushBack({ 348, 0, 23, 28 });

	player_idle_gravitySwapped.PushBack({  0, 416, 23, 32 });
	player_idle_gravitySwapped.PushBack({ 23, 416, 23, 32 });
	player_idle_gravitySwapped.PushBack({ 46, 416, 23, 32 });
	player_idle_gravitySwapped.PushBack({ 69, 416, 23, 32 });

	player_idle_mirror_gravitySwapped.PushBack({ 417, 416, 23, 32 });
	player_idle_mirror_gravitySwapped.PushBack({ 394, 416, 23, 32 });
	player_idle_mirror_gravitySwapped.PushBack({ 371, 416, 23, 32 });
	player_idle_mirror_gravitySwapped.PushBack({ 348, 416, 23, 32 });

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

	player_walking_mirror.PushBack({ 325,  37,  23, 28 });
	player_walking_mirror.PushBack({ 302,  37,  23, 28 });
	player_walking_mirror.PushBack({ 279,  37,  23, 28 });
	player_walking_mirror.PushBack({ 256,  37,  23, 28 });
	player_walking_mirror.PushBack({ 231,  37,  25, 28 });
	player_walking_mirror.PushBack({ 244,  65,  25, 28 });
	player_walking_mirror.PushBack({ 220,  65,  24, 28 });

	player_walking_gravitySwapped.PushBack({  92,  377,  23, 32 });
	player_walking_gravitySwapped.PushBack({ 115,  377,  23, 32 });
	player_walking_gravitySwapped.PushBack({ 138,  377,  23, 32 });
	player_walking_gravitySwapped.PushBack({ 161,  377,  23, 32 });
	player_walking_gravitySwapped.PushBack({ 184,  377,  25, 32 });
	player_walking_gravitySwapped.PushBack({   0,  349,  25, 32 });
	player_walking_gravitySwapped.PushBack({  25,  349,  25, 32 });

	player_walking_mirror_gravitySwapped.PushBack({ 325,  377,  23, 32 });
	player_walking_mirror_gravitySwapped.PushBack({ 302,  377,  23, 32 });
	player_walking_mirror_gravitySwapped.PushBack({ 279,  377,  23, 32 });
	player_walking_mirror_gravitySwapped.PushBack({ 256,  377,  23, 32 });
	player_walking_mirror_gravitySwapped.PushBack({ 231,  377,  25, 32 });
	player_walking_mirror_gravitySwapped.PushBack({ 415,  349,  25, 32 });
	player_walking_mirror_gravitySwapped.PushBack({ 390,  349,  25, 32 });

	//falling
	player_falling.PushBack({ 192,  96,  32, 32 });

	////CHECKPOINTS
	//// need coordinates!!!
	//checkpoint_saved_1.PushBack({ 256,  377,  23, 32 });
	//checkpoint_saved_1.PushBack({ 231,  377,  25, 32 });
	//checkpoint_saved_1.PushBack({ 415,  349,  25, 32 });
	//checkpoint_saved_1.PushBack({ 390,  349,  25, 32 });
	//checkpoint_saved_1.speed = 0.3f;
	//checkpoint_unsaved_1.PushBack({ 256,  377,  23, 32 });
	//checkpoint_unsaved_1.PushBack({ 231,  377,  25, 32 });
	//checkpoint_unsaved_1.PushBack({ 415,  349,  25, 32 });
	//checkpoint_unsaved_1.PushBack({ 390,  349,  25, 32 });
	//checkpoint_unsaved_1.speed = 0.3f;

}

j1Player::~j1Player() {}

bool j1Player::Awake(pugi::xml_node& config) {
	folder.create(config.child("folder").child_value());
	texture						= config.child("texture").attribute("source").as_string();
	playerWidth					= config.child("size").attribute("w").as_int();
	playerHeight				= config.child("size").attribute("h").as_int();
	velocity.x					= config.child("velocity").attribute("x").as_float();
	velocity.y					= config.child("velocity").attribute("y").as_float();
	maxSpeed.x					= config.child("max_speed").attribute("x").as_float();
	maxSpeed.y					= config.child("max_speed").attribute("y").as_float();
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
	grounded					= config.child("grounded").attribute("value").as_bool();
	hasDoubleJumped				= config.child("has_doublejumped").attribute("value").as_bool();
	mirror						= config.child("mirror").attribute("value").as_bool();
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
	initialLives				= config.child("num_lives").attribute("value").as_uint();
	return true;
}


bool j1Player::Start() {
	LOG("Loading player");
	colFeet			= App->collisions->AddCollider(feet, COLLIDER_PLAYER, this);
	colHead			= App->collisions->AddCollider(head, COLLIDER_PLAYER, this);
	colRightside	= App->collisions->AddCollider(rightside, COLLIDER_PLAYER, this);
	colLeftside		= App->collisions->AddCollider(leftside, COLLIDER_PLAYER, this);
	col				= App->collisions->AddCollider({ originalPosition_1.x, originalPosition_1.y, playerWidth, playerHeight }, COLLIDER_PLAYER, this);
	gravitySwapped	= false;
	numLives = initialLives;
	player_textures = App->tex->Load("textures/Ninja_Frog.png");
	player_textures_godmode = App->tex->Load("textures/Ninja_Frog_GODMODE.png");
	imgwin = App->tex->Load("textures/imgwin.png");
	lockedDoor = App->tex->Load("textures/candado.png");
	key_tex = App->tex->Load("textures/key_normal.png");
	key_tex_not = App->tex->Load("textures/key_small_locked.png");

	score = 0;
	if (App->scene->current_scene == 0) {
		position.x = originalPosition_1.x;
		position.y = originalPosition_1.y;
		current_animation = &player_idle;
	}
	else if (App->scene->current_scene == 1) {
		position.x = originalPosition_1.x;
		position.y = originalPosition_1.y;
		current_animation = &player_idle;
		// KEY POSITION COLLIDER
		key = App->collisions->AddCollider({ 700, 1405, 12, 48 /*Should come from XML*/ }, COLLIDER_KEY, this);
		// CHECKPOINTS
		//if (autosave_1) checkpoint_1_tex = App->tex->Load("textures/checkpoint_activated_Swapped.png");
		//else if (!autosave_1) checkpoint_1_tex = App->tex->Load("textures/checkpoint_deactivated_Swapped.png");
		//checkpoint_1 = App->collisions->AddCollider({ 705, 1405, 32, 32 /*Should come from XML*/ }, COLLIDER_CHECKPOINT, this);
	
	}
	else if (App->scene->current_scene == 2) {
		position.x = originalPosition_2.x;
		position.y = originalPosition_2.y;
		current_animation = &player_falling;
		// KEY POSITION COLLIDER
		key = App->collisions->AddCollider({ 700, 1405, 12, 48 /*Should come from XML*/}, COLLIDER_KEY, this);
	}

	subMenu_tex = App->tex->Load("textures/UI/background/subm.png");
	subMenuBackground_tex = App->tex->Load("textures/UI/background/transp.png");

	return true;
}

// Unload assets
bool j1Player::CleanUp() {
	LOG("Unloading player");

	App->tex->UnLoad(player_textures);
	App->tex->UnLoad(player_textures_godmode);
	App->tex->UnLoad(imgwin);
	App->tex->UnLoad(lockedDoor);
	App->tex->UnLoad(key_tex);
	App->tex->UnLoad(checkpoint_1_tex);
	App->tex->UnLoad(key_tex_not);

	App->tex->UnLoad(subMenuBackground_tex);
	App->tex->UnLoad(subMenu_tex);

	if (col != nullptr)col->to_delete = true;
	if (colFeet != nullptr)colFeet->to_delete = true;
	if (colHead != nullptr)colHead->to_delete = true;
	if (colRightside != nullptr) colRightside->to_delete = true;
	if (colLeftside != nullptr) colLeftside->to_delete = true;

	return true;
}

bool j1Player::PreUpdate() {

	BROFILER_CATEGORY("Player_PreUpdate", Profiler::Color::DodgerBlue)

	if (velocity.x > maxSpeed.x) velocity.x = maxSpeed.x;
	if (velocity.x < -maxSpeed.x) velocity.x = -maxSpeed.x;
	if (velocity.y > maxSpeed.y) velocity.y = maxSpeed.y;
	if (velocity.y < -maxSpeed.y) velocity.y = -maxSpeed.y;
	return true;
}

// Update: draw background
bool j1Player::Update(float dt) {

	BROFILER_CATEGORY("Player_Update", Profiler::Color::Blue)
	if (App->UI->scene) {
		current_animation->speed = dt * 10;

		if (mirror && gravitySwapped)		current_animation = &player_idle_mirror_gravitySwapped;
		else if (mirror && !gravitySwapped)	current_animation = &player_idle_mirror;
		else if (!mirror && gravitySwapped)	current_animation = &player_idle_gravitySwapped;
		else								current_animation = &player_idle;

		if (!grounded && !againstRoof) {
			if (mirror && gravitySwapped)		current_animation = &player_jumping_mirror_gravitySwapped;
			else if (mirror && !gravitySwapped)	current_animation = &player_jumping_mirror;
			else if (!mirror && gravitySwapped)	current_animation = &player_jumping_gravitySwapped;
			else								current_animation = &player_jumping;
		}
		if (!paused) {

			if (!godMode && past2Sec.ReadSec() > 1) {
				if (!gravitySwapped)	velocity.y -= gravity * dt;
				if (gravitySwapped) velocity.y += gravity * dt;
			}

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

			if (justSwapped && swapTimer.ReadSec() > 1) { // CAN ONLY SWAP GRAVITY ONCE PER SECOND
				justSwapped = false;
				swapTimer.Stop();
			}
			if (justDied && dieTimer.ReadSec() > 2) {
				justDied = false;
				dieTimer.Stop();
			}

			//DOUBLE JUMP
			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && !hasDoubleJumped && !godMode) {
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
			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && !godMode) {
				if (gravitySwapped) { //INVERTED GRAVITY
					if (againstRoof) {
						againstRoof = false;
						velocity.y = -impulse;
						hasDoubleJumped = false;
						//TODO: Play an Fx for jumping
					}
				}
				else {
					if (grounded) {
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

			if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && !App->particles->onCooldown && App->particles->shurikensUsed < 3) {
				App->particles->AddParticle(App->particles->shuriken, position.x + 20, position.y, COLLIDER_PLAYER_SHOT, 0);
				App->particles->shurikensUsed++;
				if (App->particles->shurikensUsed == 3) {
					App->particles->onCooldown = true;
					App->particles->cooldown.Start();
					App->particles->partialCooldown.Stop();
				}
				else App->particles->partialCooldown.Start();
			}

			MoveEverything(gravitySwapped, dt);

			if (App->scene->current_scene == 1 && doorLocked) {
				App->render->Blit(lockedDoor, directWin_1.x + 18, directWin_1.y - 35);
				App->render->Blit(key_tex, key->rect.x, key->rect.y);
			}
			else if (App->scene->current_scene == 2 && doorLocked) {
				App->render->Blit(lockedDoor, directWin_2.x - 90, directWin_2.y - 8);
				App->render->Blit(key_tex, 4517, 6298);
			}
		}
		if (gravitySwapped && godMode) App->render->Blit(player_textures_godmode, position.x - AnimationOffstet.x, position.y - 5/*TODO: initialize AnimationOffsetGravitySwapped so no magic number*/, &(current_animation->GetCurrentFrame()));
		else if (!gravitySwapped && godMode) App->render->Blit(player_textures_godmode, position.x - AnimationOffstet.x, position.y - AnimationOffstet.y, &(current_animation->GetCurrentFrame()));
		else if (gravitySwapped && !godMode) App->render->Blit(player_textures, position.x - AnimationOffstet.x, position.y - 5/*TODO: initialize AnimationOffsetGravitySwapped so no magic number*/, &(current_animation->GetCurrentFrame()));
		else App->render->Blit(player_textures, position.x - AnimationOffstet.x, position.y - AnimationOffstet.y, &(current_animation->GetCurrentFrame()));

		if (paused) {
			App->render->Blit(subMenuBackground_tex, 0, 0);
			App->render->Blit(subMenu_tex, 0, 0);

		}
	}
	return true;
}

bool j1Player::PostUpdate() {

	BROFILER_CATEGORY("Player_PostUpdate", Profiler::Color::DeepSkyBlue)

	grounded			= false;
	againstLeftSide		= false;
	againstRightSide	= false;
	againstRoof			= false;
	return true;
}

bool j1Player::Save(pugi::xml_node& node) {
	node.append_child("position_x").append_attribute("value")		= position.x;
	node.append_child("position_y").append_attribute("value")		= position.y;
	node.append_child("num_lives").append_attribute("value")		= numLives;
	node.append_child("gravity_swapped").append_attribute("value")	= gravitySwapped;
	//TODO: Make sure all the necessary data is taken into account
	return true;
}
bool j1Player::Load(pugi::xml_node& node) {
	position.x		= node.child("position_x").attribute("value").as_float();
	position.y		= node.child("position_y").attribute("value").as_float();
	numLives		= node.child("num_lives").attribute("value").as_uint();
	gravitySwapped	= node.child("gravity_swapped").attribute("value").as_bool();
	velocity.y = 0;
	return true;
}

void j1Player::MoveEverything(bool swapped, float dt) {

	BROFILER_CATEGORY("Player_MoveEverything", Profiler::Color::RoyalBlue)

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

	BROFILER_CATEGORY("Player_ChangeGravity", Profiler::Color::SteelBlue)

	if (!gravitySwapped) { 
		if(withImpulse) velocity.y -= impulse;
		gravitySwapped = true;
		return true; 
	}
	else { 
		if (withImpulse) velocity.y += impulse;
		gravitySwapped = false;
		return false; 
	}
}

void j1Player::GameOver() {
	if (numLives == 3) score += 1500;
	else if (numLives == 2) score += 750;
	else if (numLives == 1) score += 250;

	if (App->UI->gameTime.ReadSec() < 120) score += (120 - App->UI->gameTime.ReadSec()) * 20;
	else if (App->UI->gameTime.ReadSec() < 180) score += (180 - App->UI->gameTime.ReadSec()) * 10;
}

void j1Player::OnCollision(Collider* c1, Collider* c2) {

	BROFILER_CATEGORY("Player_OnCollision", Profiler::Color::CornflowerBlue)

	if (c1->type == COLLIDER_PLAYER && !godMode) {
		if (!gravitySwapped) {
			if (c2->type == COLLIDER_PLATFORM && c1 != colRightside && c1 != colLeftside && velocity.y < 0 && 
				position.y + playerHeight < c2->rect.y + 6) {
				velocity.y = 0;
				position.y = c2->rect.y - playerHeight;
				grounded = true;
			}
			else if (c2->type == COLLIDER_WALL) {
				if (c1 != colRightside && c1 != colLeftside && velocity.y < 0 &&
					position.y + playerHeight < c2->rect.y + 15) {
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
				position.y + 6 > c2->rect.y + c2->rect.h) {
				velocity.y = 0;
				position.y = c2->rect.y + c2->rect.h + 1;
				c1->rect.y = c2->rect.y + c2->rect.h + 1;
				againstRoof = true;
			}
			if (c2->type == COLLIDER_WALL) {
				if (c1 != colRightside && c1 != colLeftside && velocity.y > 0 &&
					position.y + 15 > c2->rect.y + c2->rect.h) {
					velocity.y = 0;
					position.y = c2->rect.y + c2->rect.h + 1;
					c1->rect.y = c2->rect.y + c2->rect.h + 1;
					againstRoof = true;
				}
				if (position.y < c2->rect.y + c2->rect.h && position.y + playerHeight + 7 > c2->rect.y &&
					position.x + playerWidth >= c2->rect.x && position.x <= c2->rect.x &&
					c1 != colFeet && c1 != colHead) {
					againstRightSide = true;
					againstLeftSide = false;
				}

				if (position.y - 7 < c2->rect.y + c2->rect.h && position.y + playerHeight > c2->rect.y &&
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

		if (c2->type == COLLIDER_KEY && doorLocked) {
			c2->to_delete = true;
			doorLocked = false;
			App->UI->renderKey = true;
			App->SaveRequest = true;
			score += 500;
		}

		else if (c2->type == COLLIDER_WIN && !doorLocked) {
			if (App->scene->current_scene == 1) {
				App->scene->changeSceneTo(2);
			}
			if (App->scene->current_scene == 2) {
				App->scene->changeSceneTo(1);
			}
			GameOver();
		}

		else if ((c2->type == COLLIDER_DEATH || c2->type == COLLIDER_ENEMY || c2->type == COLLIDER_ENEMY_SHOT) && !justDied) {
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
			gravitySwapped = false;
			numLives--;
			if (numLives < 0) isDead = true; //TODO: Make the restart function restart numLives to 3 as well (and isDead to false, duh)
			dieTimer.Start();
			justDied = true;
		}

		else if (c2->type == COLLIDER_GRAVITY && !justSwapped) {
			justSwapped = true;
			swapTimer.Start();
			ChangeGravity(true);
		}
	}
}
