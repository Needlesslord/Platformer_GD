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
#include "j1Animation.h"


j1Player::j1Player() : j1Module() {
	name.create("player");
	//idle
	player_idle.PushBack({  0, 0, 23, 28 });
	player_idle.PushBack({ 23, 0, 23, 28 });
	player_idle.PushBack({ 46, 0, 23, 28 });
	player_idle.PushBack({ 69, 0, 23, 28 });
	player_idle.speed = 0.25f;

	//jumping
	player_jumping.PushBack({ 92, 0, 23, 28 });
	//walking
	player_walking.PushBack({   0,  37,  23, 28 });
	player_walking.PushBack({  23,  37,  23, 28 });
	player_walking.PushBack({  46,  37,  23, 28 });
	player_walking.PushBack({  69,  37,  23, 28 });
	player_walking.PushBack({  92,  37,  23, 28 });
	player_walking.PushBack({ 115,  37,  23, 28 });
	player_walking.PushBack({ 138,  37,  23, 28 });
	player_walking.PushBack({ 161,  37,  23, 28 });
	player_walking.PushBack({ 184,  37,  25, 28 });
	player_walking.PushBack({ 171,  65,  25, 28 });
	player_walking.PushBack({ 196,  65,  25, 28 });
	player_walking.speed = 0.5f;
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
	gravity						= config.child("gravity").attribute("value").as_float();
	feet.x						= config.child("position_scene_1").attribute("x").as_float();
	feet.y						= config.child("position_scene_1").attribute("y").as_float() + config.child("size").attribute("h").as_int();	//PLAYER H + PLAYER Y
	feet.w						= config.child("size").attribute("w").as_int();	//SAME AS PLAYER
	feet.h						= config.child("feet").attribute("h").as_int();
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
	current_animation = &player_jumping;
	colFeet			= App->collisions->AddCollider(feet, COLLIDER_PLAYER, this);
	colRightside	= App->collisions->AddCollider(rightside, COLLIDER_PLAYER, this);
	colLeftside		= App->collisions->AddCollider(leftside, COLLIDER_PLAYER, this);
	player_textures = App->tex->Load("textures/Ninja_Frog.png");
	//img_m = App->tex->Load("textures/Ninja_Frog_m.png");
	imgwin = App->tex->Load("textures/imgwin.png");
	if (App->scene->current_scene == 1) {
		position.x = originalPosition_1.x;
		position.y = originalPosition_1.y;
		col = App->collisions->AddCollider({ originalPosition_1.x, originalPosition_1.y, playerWidth, playerHeight }, COLLIDER_PLAYER, this);
	}
	else if (App->scene->current_scene == 2) {
		position.x = originalPosition_2.x;
		position.y = originalPosition_2.y;
		col = App->collisions->AddCollider({ originalPosition_2.x, originalPosition_2.y, playerWidth, playerHeight }, COLLIDER_PLAYER, this);
	}
	return true;
}

// Unload assets
bool j1Player::CleanUp() {
	LOG("Unloading player");

	App->tex->UnLoad(graphics);
	App->tex->UnLoad(player_textures);
	App->tex->UnLoad(imgwin);

	if (col != nullptr)col->to_delete = true;
	if (colFeet != nullptr)colFeet->to_delete = true;
	if (colRightside != nullptr) colRightside->to_delete = true;
	if (colLeftside != nullptr) colLeftside->to_delete = true;

	return true;
}

bool j1Player::Mirror() {
	
	return mirror;
}

bool j1Player::PreUpdate() {
	return true;
}

// Update: draw background
bool j1Player::Update(float dt) {
	float speed = 2;
	float t = 1;

	if(grounded) current_animation = &player_idle;
	else current_animation = &player_jumping;

	if (!godMode) velocity.y -= gravity;
	if (againstRoof)velocity.y = 0;

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && !againstLeftSide) {
		position.x -= velocity.x;
		if(grounded) current_animation = &player_walking;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP) player_walking.Reset();

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && !againstRightSide) {
		position.x += velocity.x;
		if (grounded) current_animation = &player_walking;

	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP) player_walking.Reset();

	position.y -= velocity.y;
	feet.x = position.x;
	feet.y = position.y + playerHeight;
	rightside.x = position.x + playerWidth;
	rightside.y = position.y;
	leftside.x = position.x - leftside.w;
	leftside.y = position.y;
	col->SetPos(position.x, position.y);
	colFeet->SetPos(feet.x, feet.y);
	colRightside->SetPos(rightside.x, rightside.y);
	colLeftside->SetPos(leftside.x, leftside.y);


	//DOUBLE JUMP
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && !hasDoubleJumped && velocity.y > 0 && !grounded && !godMode) {
		velocity.y = 1.5 * speed;
		hasDoubleJumped = true;
	}

	//JUMP
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && grounded && velocity.y > -1 && !godMode) {
		grounded = false;
		velocity.y = 1.5 * speed;
		hasDoubleJumped = false;
	} 
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && godMode) {
		position.y -= 3 * speed;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && godMode) {
		position.y += 3 * speed;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) {
		S_Down = true;
		grounded = false;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_UP) S_Down = false;

	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN) {
		if (current_map == 1) {
			velocity.y = 0;
			position.x = directWin_1.x;
			position.y = directWin_1.y;
		}
		if (current_map == 2) {
			velocity.y = 0;
			position.x = directWin_2.x;
			position.y = directWin_2.y;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) {
		velocity.y = 0;
		godMode = !godMode;
	}

	

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		if (App->scene->current_scene == 1) {
			position.x = originalPosition_1.x;
			position.y = originalPosition_1.y;
		}
		if (App->scene->current_scene == 2) {
			position.x = originalPosition_2.x;
			position.y = originalPosition_2.y;
		}
	}

	//----------------------------------------- Draw everything --------------------------------------
	//SDL_RenderCopyEx(App->render->renderer, player_textures, &(current_animation->GetCurrentFrame()), &playerRect, NULL, NULL, SDL_FLIP_HORIZONTAL);
	App->render->Blit(player_textures, position.x - AnimationOffstet.x, position.y - AnimationOffstet.y, &(current_animation->GetCurrentFrame()));
	if (win)
		App->render->Blit(imgwin, originalPosition_1.x - 175, originalPosition_1.y - 150);

	return true;
}

bool j1Player::PostUpdate() {
	againstLeftSide		= false;
	againstRightSide	= false;
	againstRoof			= false;
	return true;
}

bool j1Player::Load(pugi::xml_node& node) {
	position.x = node.child("position_x").attribute("value").as_float();
	position.y = node.child("position_y").attribute("value").as_float();
	return true;
}

bool j1Player::Save(pugi::xml_node& node) {
	node.append_child("position_x").append_attribute("value") = position.x;
	node.append_child("position_y").append_attribute("value") = position.y;
	return true;
}


void j1Player::OnCollision(Collider* c1, Collider* c2) {
	if (c1->type == COLLIDER_PLAYER && !godMode) {
		if ((c2->type == COLLIDER_PLATFORM || c2->type == COLLIDER_WALL) && c1 != colRightside && c1 != colLeftside && velocity.y < 0 && !S_Down && position.y + playerHeight < c2->rect.y + 6) {
			velocity.y = 0;
			position.y = c2->rect.y - playerHeight;
			grounded = true;
		}
	
		if (c2->type == COLLIDER_WALL && c1->rect.y <= c2->rect.y + c2->rect.h && c1->rect.y + playerHeight >= c2->rect.y && c1->rect.x + playerWidth >= c2->rect.x && c1->rect.x <= c2->rect.x) {
			againstRightSide = true;
			againstLeftSide = false;
		}

		if (c2->type == COLLIDER_WALL && c1->rect.y <= c2->rect.y + c2->rect.h && c1->rect.y + playerHeight >= c2->rect.y && c1->rect.x <= c2->rect.x + c2->rect.w && c1->rect.x + playerWidth >= c2->rect.x + c2->rect.w) {
			againstLeftSide = true;
			againstRightSide = false;
		}

		if (c2->type == COLLIDER_WALL && c1 != colRightside && c1 != colLeftside && velocity.y > 0 && position.y + 6 > c2->rect.y + c2->rect.h) {
			position.y = c2->rect.y + c2->rect.h;
			againstRoof = true;
		}

		if (c2->type == COLLIDER_WIN) {
			if (App->scene->current_scene == 1) {
				position.x = originalPosition_1.x;
				position.y = originalPosition_1.y;
			}
			if (App->scene->current_scene == 2) {
				position.x = originalPosition_2.x;
				position.y = originalPosition_2.y;
			}
			win = true;
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
			againstLeftSide = false;
			againstRightSide = false;
		}
	}
}
