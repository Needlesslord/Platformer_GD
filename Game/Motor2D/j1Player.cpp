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
	player_idle.speed = 0.2f;
	//jumping
	player_jumping.PushBack({ 92, 0, 23, 28 });
	//walking
	player_walking.PushBack({ 0,    64,  32, 32 });
	player_walking.PushBack({ 32,   64,  32, 32 });
	player_walking.PushBack({ 64,   64,  32, 32 });
	player_walking.PushBack({ 96,   64,  32, 32 });
	player_walking.PushBack({ 128,  64,  32, 32 });
	player_walking.PushBack({ 160,  64,  32, 32 });
	player_walking.PushBack({ 192,  64,  32, 32 });
	player_walking.PushBack({ 0,    96,  32, 32 });
	player_walking.PushBack({ 32,   96,  32, 32 });
	player_walking.PushBack({ 64,   96,  32, 32 });
	player_walking.PushBack({ 96,   96,  32, 32 });
	player_walking.PushBack({ 128,  96,  32, 32 });
	player_walking.speed = 0.05f;
	//jumping
	player_falling.PushBack({ 192,  96,  32, 32 });

}

j1Player::~j1Player() {}

bool j1Player::Awake(pugi::xml_node& config) {
	folder.create(config.child("folder").child_value());
	texture				= config.child("texture").attribute("source").as_string();
	position.x			= config.child("position").attribute("x").as_float();
	position.y			= config.child("position").attribute("y").as_float();
	desiredPosition.x	= config.child("desired_position").attribute("x").as_float();
	desiredPosition.y	= config.child("desired_position").attribute("y").as_float();
	playerWidth			= config.child("size").attribute("w").as_int();
	playerHeight		= config.child("size").attribute("h").as_int();
	velocity.x			= config.child("velocity").attribute("x").as_float();
	velocity.y			= config.child("velocity").attribute("y").as_float();
	gravity				= config.child("gravity").attribute("value").as_float();
	feet.x				= config.child("position").attribute("x").as_float();
	feet.y				= config.child("position").attribute("y").as_float() + config.child("size").attribute("h").as_int();	//PLAYER H + PLAYER Y
	feet.w				= config.child("size").attribute("w").as_int();	//SAME AS PLAYER
	feet.h				= config.child("feet").attribute("h").as_int();
	rightside.x			= config.child("position").attribute("x").as_float() + config.child("size").attribute("w").as_int();
	rightside.y			= config.child("position").attribute("y").as_float();
	rightside.w			= config.child("right_side").attribute("w").as_int();
	rightside.h			= config.child("size").attribute("h").as_int();
	leftside.x			= config.child("position").attribute("x").as_float() - config.child("left_side").attribute("w").as_int();
	leftside.y			= config.child("position").attribute("y").as_float();
	leftside.w			= config.child("left_side").attribute("w").as_int();
	leftside.h			= config.child("size").attribute("h").as_int();
	S_Down				= config.child("s_down").attribute("value").as_bool();
	grounded			= config.child("grounded").attribute("value").as_bool();
	hasDoubleJumped		= config.child("has_doublejumped").attribute("value").as_bool();
	mirror				= config.child("mirror").attribute("value").as_bool();
	alive				= config.child("alive").attribute("value").as_bool();

	return true;
}


bool j1Player::Start() {
	LOG("Loading player");
	current_state = PLAYER_ST_IDLE;
	current_animation = &player_falling;
	originalPosition.x = position.x;
	originalPosition.y = position.y;
	col				= App->collisions->AddCollider({ originalPosition.x, originalPosition.y, playerWidth, playerHeight }, COLLIDER_PLAYER, this);
	colFeet			= App->collisions->AddCollider(feet, COLLIDER_PLAYER, this);
	colRightside	= App->collisions->AddCollider(rightside, COLLIDER_PLAYER, this);
	colLeftside		= App->collisions->AddCollider(leftside, COLLIDER_PLAYER, this);
	AnimationOffstet.x = 4;
	AnimationOffstet.y = 3;
	img = App->tex->Load("textures/Ninja_Frog.png");
	return true;
}

// Unload assets
bool j1Player::CleanUp() {
	LOG("Unloading player");
	App->tex->UnLoad(graphics);
	App->tex->UnLoad(img);

	if (col != nullptr)col->to_delete = true;
	if (colFeet != nullptr)colFeet->to_delete = true;

	return true;
}

void j1Player::Mirror() {
	if (velocity.x < 0) mirror = true;
	else if (velocity.x > 0) mirror = false;

	if (!mirror) App->render->Blit(img, position.x, position.y, &(current_animation->GetCurrentFrame()), SDL_FLIP_NONE);
	else App->render->Blit(img, position.x, position.y, &(current_animation->GetCurrentFrame()), SDL_FLIP_HORIZONTAL);
}

bool j1Player::PreUpdate() {
	return true;
}

// Update: draw background
bool j1Player::Update(float dt) {
	if (velocity.x < 0) mirror = true;
	else if (velocity.x > 0) mirror = false;

	float speed = 1;
	float t = 1;

	//POSITION
	if (position.x > 30) position.x -= velocity.x;
	else if (velocity.x < 0) position.x -= velocity.x;

	position.y -= velocity.y;

	velocity.y -= gravity;

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) velocity.x = 0.5;
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP) velocity.x = 0;
	
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) velocity.x = -0.5;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP) velocity.x = 0;

	//DOUBLE JUMP
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && !hasDoubleJumped && velocity.y > 0 && !grounded) {
		velocity.y = 1.5 * speed;
		hasDoubleJumped = true;
	}

	//JUMP
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && grounded && velocity.y > -1) {
		grounded = false;
		velocity.y = 1.5 * speed;
		hasDoubleJumped = false;
	} 
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) {
		S_Down = true;
		grounded = false;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_UP) S_Down = false;

	//Mirror();

	if (velocity.x == 0 && grounded) current_animation = &player_idle;
	else if (!grounded) current_animation = &player_jumping;
	else current_animation = &player_walking;

	/*			------------------------------------PARTICLES--------------------------------------------------

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laser, positionX + 20, positionY, COLLIDER_PLAYER_SHOT);
	}
	*/
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
	
	//----------------------------------------- Draw everything --------------------------------------
	if (alive == true) App->render->Blit(img, position.x - AnimationOffstet.x, position.y - AnimationOffstet.y, &(current_animation->GetCurrentFrame()), SDL_FLIP_NONE, -1.0);

	return true;
}

bool j1Player::PostUpdate() {
	return true;
}

bool j1Player::Load(pugi::xml_node& node) {
	position.x = node.child("position_x").attribute("value").as_float();
	position.y = node.child("position_y").attribute("value").as_float();
	velocity.x = node.child("velocity_x").attribute("value").as_float();
	velocity.y = node.child("velocity_Y").attribute("value").as_float();

	return true;
}

bool j1Player::Save(pugi::xml_node& node) {
	node.append_child("position_x").append_attribute("value") = position.x;
	node.append_child("position_y").append_attribute("value") = position.y;

	node.append_child("velocity_x").append_attribute("value") = velocity.x;
	node.append_child("velocity_Y").append_attribute("value") = velocity.y;

	return true;
}


void j1Player::OnCollision(Collider* c1, Collider* c2) {
	if (c1->type == COLLIDER_PLAYER && (c2->type ==	COLLIDER_PLATFORM || c2->type == COLLIDER_WALL) && c1 != colLeftside && c1 != colRightside && velocity.y < 0 && !S_Down &&		(position.y + playerHeight) < c2->rect.y + 5) {
		velocity.y = 0;
		position.y = c2->rect.y - playerHeight;
		grounded = true;
	}
	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_WALL && velocity.x < 0 && (position.x + playerWidth) < c2->rect.x + 5) {//PLAYER'S RIGHTSIDE COLLISION
		velocity.x = 0;
		position.x = c2->rect.x - playerWidth;
	}
	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_WALL && velocity.x > 0 && position.x - 5 > c2->rect.x + c1->rect.w) {//PLAYER'S LEFTSIDE COLLISION
		velocity.x = 0;
		position.x = c2->rect.x + c2->rect.w;
	}
}
