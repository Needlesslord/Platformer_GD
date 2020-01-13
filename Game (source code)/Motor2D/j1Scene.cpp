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
#include "j1UI.h"
#include "Brofiler.h"

j1Scene::j1Scene() : j1Module() {
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene() {}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config) {
	bool ret = true;
	LOG("Loading Scene");
	current_scene = config.attribute("current_scene").as_int();

	return ret;
}

// Called before the first frame
bool j1Scene::Start() {

	BROFILER_CATEGORY("Scene_Start", Profiler::Color::Salmon)

	

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate() {

	BROFILER_CATEGORY("Scene_PreUpdate", Profiler::Color::PaleVioletRed)

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt) {

	BROFILER_CATEGORY("Scene_Update", Profiler::Color::HotPink)
	if (App->UI->mainMenu) {

	}
	else if (App->UI->scene) {
		//DEBUG KEYS
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
		if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) { //CHANGE TO PAUSE MENU
			if (current_scene != 99) {
				changeSceneTo(99);
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

		if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) App->SaveRequest = true; //SAVE

		if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) App->LoadRequest = true; //LOAD

		if (App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN) keys_enabled = !keys_enabled; //ENABLE/DISABLE FREE CAMERA MOVEMENT

		if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN) { //GO TO VICTORY POSITION
			if (App->player->current_map == 1) {
				App->player->velocity.y = 0;
				App->player->position.x = App->player->directWin_1.x;
				App->player->position.y = App->player->directWin_1.y;
			}
			if (App->player->current_map == 2) {
				App->player->velocity.y = 0;
				App->player->position.x = App->player->directWin_2.x;
				App->player->position.y = App->player->directWin_2.y;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) { //ENABLE/DISABLE GODMODE
			App->player->velocity.y = 0;
			App->player->godMode = !App->player->godMode;
		}

		if (keys_enabled) { //IF ENABLED, FREE MOVE CAMERA
			if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) App->render->camera.y += 100;

			if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) App->render->camera.y -= 100;

			if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) App->render->camera.x += 100;

			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) App->render->camera.x -= 100;
		}

		if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN && App->audio->volume < 128) App->audio->volume += 4; //INCRESE VOLUME

		if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN && App->audio->volume > 0) App->audio->volume -= 4; //DECREASE VOLUME


		if (current_scene == 1) App->render->Blit(background1_small, 0, 0, NULL, 0.00f);
		else if (current_scene == 2) App->render->Blit(background2_small, 0, 0, NULL, 0.00f);

		App->map->Draw(-App->render->camera.x);
	}

	if (!App->UI->mainMenu) {
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
			if (!App->player->paused && App->UI->gameTime.counting) 
				App->UI->gameTime.Stop();
			else
				App->UI->gameTime.Resume();
			App->player->paused = !App->player->paused;

		}
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate() {

	BROFILER_CATEGORY("Scene_PostUpdate", Profiler::Color::DeepPink)

	bool ret = true;
	
	if(App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) ret = false; //QUIT

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp() {
	LOG("Freeing scene");
	if (current_scene == 1) App->tex->UnLoad(background1_small);
	if (current_scene == 2) App->tex->UnLoad(background2_small);
	App->tex->UnLoad(imgwin);
	App->map->CleanUp();
	// WE NEED TO CLEAN UP THE ENEMIES
	return true;
}

bool j1Scene::changeSceneTo(int scene) {
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

bool j1Scene::Save(pugi::xml_node& node) {
	node.append_child("current_scene").append_attribute("value") = current_scene;
	return true;
}

bool j1Scene::Load(pugi::xml_node& node) {
	if (node.child("current_scene").attribute("value").as_int() != current_scene) {
		current_scene = node.child("current_scene").attribute("value").as_int();
		changeSceneTo(current_scene);
	}
	return true;
}

bool j1Scene::SetUpScene() {
	bool ret = true;
	if (current_scene == 0) {
		background1_small = App->tex->Load("maps/fondo0_big.png");
		App->map->Load("00 Tutorial.tmx");
		//App->audio->PlayMusic("audio/music/intro.ogg");
	}
	else if (current_scene == 1) {
		background1_small = App->tex->Load("maps/fondo1_big.png");
		App->map->Load("01 Level1.tmx");
		App->player->past2Sec.Start();
		App->player->velocity.y = 0;
		App->player->position.y = App->player->originalPosition_1.y;
		//App->audio->PlayMusic("audio/music/Scene1.ogg");
	}
	else if (current_scene == 2) {
		background2_small = App->tex->Load("maps/fondo2_big.png");
		App->map->Load("02 Level2v2.tmx");
		App->player->past2Sec.Start();
		App->player->velocity.y = 0;
		App->player->position.y = App->player->originalPosition_2.y - 10;
		//App->audio->PlayMusic("audio/music/intro.ogg");
	}

	// ENEMIES
	if (current_scene == 1) {
		//AIR
		App->entity_manager->CreateEntity(ENEMY_AIR, 1300, 1000);
		App->entity_manager->CreateEntity(ENEMY_AIR, 2100, 740);
		App->entity_manager->CreateEntity(ENEMY_AIR, 2100, 740);
		App->entity_manager->CreateEntity(ENEMY_AIR, 2363, 1660);
		App->entity_manager->CreateEntity(ENEMY_AIR, 2810, 512);
		App->entity_manager->CreateEntity(ENEMY_AIR, 3160, 1290);
		App->entity_manager->CreateEntity(ENEMY_AIR, 680, 1560);
		//LAND
		App->entity_manager->CreateEntity(ENEMY_LAND, 895, 1145);
		App->entity_manager->CreateEntity(ENEMY_LAND, 1160, 1712);
		App->entity_manager->CreateEntity(ENEMY_LAND, 1800, 1135);
		App->entity_manager->CreateEntity(ENEMY_LAND, 2620, 1365);
		App->entity_manager->CreateEntity(ENEMY_LAND, 2445, 940);
		App->entity_manager->CreateEntity(ENEMY_LAND, 3540, 645);
		App->entity_manager->CreateEntity(ENEMY_LAND, 4000, 1020);
	}
	if (current_scene == 2) {
		//AIR
		App->entity_manager->CreateEntity(ENEMY_AIR, 1800, 2800);
		App->entity_manager->CreateEntity(ENEMY_AIR, 3270, 3130);
		App->entity_manager->CreateEntity(ENEMY_AIR, 740, 3800);
		App->entity_manager->CreateEntity(ENEMY_AIR, 1940, 4700);
		App->entity_manager->CreateEntity(ENEMY_AIR, 1530, 5600);
		App->entity_manager->CreateEntity(ENEMY_AIR, 4245, 3775);
		App->entity_manager->CreateEntity(ENEMY_AIR, 3625, 4900);
		//LAND
		App->entity_manager->CreateEntity(ENEMY_LAND, 4232, 5215);
		App->entity_manager->CreateEntity(ENEMY_LAND, 3780, 3970);
		App->entity_manager->CreateEntity(ENEMY_LAND, 2900, 5270);
		App->entity_manager->CreateEntity(ENEMY_LAND, 3090, 5900);
		App->entity_manager->CreateEntity(ENEMY_LAND, 2200, 3900);
		App->entity_manager->CreateEntity(ENEMY_LAND, 645, 3260);
		App->entity_manager->CreateEntity(ENEMY_LAND, 500, 4730);
	}

	App->UI->gameTime.Start();

	return ret;
}