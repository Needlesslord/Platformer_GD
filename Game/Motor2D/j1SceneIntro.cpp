#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "j1SceneIntro.h"
#include "j1Map.h"
#include "j1Collisions.h"
#include "j1Player.h"
#include "j1EntityManager.h"
#include "Brofiler.h"

j1SceneIntro::j1SceneIntro() : j1Module() {
	name.create("scene_intro");
}

// Destructor
j1SceneIntro::~j1SceneIntro() {}

// Called before render is available
bool j1SceneIntro::Awake(pugi::xml_node& config) {
	bool ret = true;
	LOG("Loading Scene");
	current_scene = config.attribute("current_scene").as_int();

	//TODO IMPORTANT!!! change scale to 1 and others to 2.5

	return ret;
}

// Called before the first frame
bool j1SceneIntro::Start() {

	BROFILER_CATEGORY("Scene_intro_Start", Profiler::Color::Salmon)

	menu_base = App->tex->Load("ui/menu.png");

	return true;
}

// Called each loop iteration
bool j1SceneIntro::PreUpdate() {

	BROFILER_CATEGORY("Scene_intro_PreUpdate", Profiler::Color::PaleVioletRed)

		return true;
}

// Called each loop iteration
bool j1SceneIntro::Update(float dt) {

	BROFILER_CATEGORY("Scene_intro_Update", Profiler::Color::HotPink)

	{//DEBUG KEYS
		if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN) { //CHANGE TO Tutorial
			if (current_scene != 0) {
				changeSceneTo(0);
				//TODO Insert sound in an else to say you can't load lvl1
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) { //CHANGE TO SCENE 1
			if (current_scene != 1) {
				changeSceneTo(1);
				//TODO Insert sound in an else to say you can't load lvl1
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) { //CHANGE TO SCENE 2
			if (current_scene != 2) {
				changeSceneTo(2);
				//TODO Insert sound in an else to say you can't load lvl1
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) { //BACK TO BEGINING
			if (current_scene == 0) {
				App->player->position.x = App->player->originalPosition_1.x;
				App->player->position.y = App->player->originalPosition_1.y;
			}
			if (current_scene == 1) {
				App->player->position.x = App->player->originalPosition_1.x;
				App->player->position.y = App->player->originalPosition_1.y;
				if (App->player->gravitySwapped) {
					App->player->gravitySwapped = false;
				}
			}
			if (current_scene == 2) {
				App->player->position.x = App->player->originalPosition_2.x;
				App->player->position.y = App->player->originalPosition_2.y;
				if (App->player->gravitySwapped) {
					App->player->gravitySwapped = false;
				}
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) App->LoadRequest = true; //LOAD

	}

	//volume
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN && App->audio->volume < 128) App->audio->volume += 4; //INCRESE VOLUME
	if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN && App->audio->volume > 0) App->audio->volume -= 4; //DECREASE VOLUME

	App->render->Blit(menu_base, App->player->position.x - 250, App->player->position.y - 200);

	App->map->Draw(-App->render->camera.x);


	return true;
}

// Called each loop iteration
bool j1SceneIntro::PostUpdate() {

	BROFILER_CATEGORY("Scene_intro_PostUpdate", Profiler::Color::DeepPink)

		bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) ret = false; //QUIT

	return ret;
}

// Called before quitting
bool j1SceneIntro::CleanUp() {
	LOG("Freeing scene");
	App->tex->UnLoad(menu_base);
	// WE NEED TO CLEAN UP THE ENEMIES
	return true;
}

bool j1SceneIntro::changeSceneTo(int scene) {
	if (scene == 0) { //CHANGE TO TUTORIAL			(  )

	}

	else if (scene == 1) { //CHANGE TO SCENE 1		(F1)
		App->collisions->CleanUp();
		App->map->CleanUp();
		current_scene = scene;

		App->player->CleanUp();
		App->player->Start();
		App->player->position.x = App->player->originalPosition_1.x;
		App->player->position.y = App->player->originalPosition_1.y;
		App->player->velocity.y = 0;
		App->player->current_map = 1;
		App->player->doorLocked = true;

		App->scene->CleanUp();
		App->scene->Start();
	}

	else if (scene == 2) { //CHANGE TO SCENE 2		(F2)
		App->collisions->CleanUp();
		App->map->CleanUp();
		current_scene = scene;

		App->player->CleanUp();
		App->player->Start();
		App->player->position.x = App->player->originalPosition_2.x;
		App->player->position.y = App->player->originalPosition_2.y;
		App->player->velocity.y = 0;
		App->player->current_map = 2;
		App->player->doorLocked = true;

		App->scene->CleanUp();
		App->scene->Start();
	}
	else if (scene == 99) {
		App->collisions->CleanUp();
		App->map->CleanUp();
		current_scene = scene;

		App->player->CleanUp();
		App->player->Start();
		App->player->position.x = App->player->originalPosition_1.x;		//change to 99, add variable
		App->player->position.y = App->player->originalPosition_1.y;		//change to 99, add variable
		App->player->velocity.y = 0;
		App->player->current_map = 1;										//change to 99, with no map
		App->player->doorLocked = true;

		App->scene->CleanUp();

		App->scene_intro->Start();

	}
	else return false;
	//TODO:		IMPORTANT!!		 UNLOAD COLLIDERS
	return true;
}

bool j1SceneIntro::Save(pugi::xml_node& node) {
	node.append_child("current_scene").append_attribute("value") = current_scene;
	return true;
}

bool j1SceneIntro::Load(pugi::xml_node& node) {
	if (node.child("current_scene").attribute("value").as_int() != current_scene) {
		current_scene = node.child("current_scene").attribute("value").as_int();
		changeSceneTo(current_scene);
	}
	return true;
}