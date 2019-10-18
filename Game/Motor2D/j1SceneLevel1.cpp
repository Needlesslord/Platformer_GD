#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1SceneLevel1.h"
#include "j1Map1.h"

j1SceneLevel1::j1SceneLevel1() : j1Module() {
	name.create("scenelevel1");
}

// Destructor
j1SceneLevel1::~j1SceneLevel1() {}

// Called before render is available
bool j1SceneLevel1::Awake() {
	LOG("Loading SceneLevel1");  //LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1SceneLevel1::Start() {

	App->map->Load("level1.tmx")

	return true;
}

// Called each loop iteration
bool j1SceneLevel1::PreUpdate() {
	return true;
}

// Called each loop iteration
bool j1SceneLevel1::Update(float dt) {
	// TODO 1: Request Load / Save on application when pressing L/S
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) App->LoadRequest = true;

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) App->SaveRequest = true;

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) App->render->camera.y -= 1;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) App->render->camera.y += 1;

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) App->render->camera.x -= 1;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) App->render->camera.x += 1;

	if (App->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_DOWN && App->audio->volume < 128) App->audio->volume += 2;

	if (App->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_DOWN && App->audio->volume > 0) App->audio->volume -= 2;

	App->render->Blit(img, 0, 0);

	return true;
}

// Called each loop iteration
bool j1SceneLevel1::PostUpdate() {
	bool ret = true;
	pugi::xml_node config;

	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) {







		//current_scene scene="true" intro="false" l1="false" l2="false"
		current_scene = config.child("current_scene").attribute("scene").as_bool(false);
		following_scene = config.child("current_scene").attribute("l1").as_bool(true);
		App->sceneintro;
	}

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) ret = false;

	return ret;
}

// Called before quitting
bool j1SceneLevel1::CleanUp() {
	LOG("Freeing scene");

	return true;
}
