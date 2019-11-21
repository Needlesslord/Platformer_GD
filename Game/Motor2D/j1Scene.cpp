#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "j1Collisions.h"
#include "j1Player.h"
#include "j1EntityManager.h"
#include "j1Enemy_Air1.h"
#include "j1Enemy_Land.h"
#include "j1Exit.h"
#include "j1SceneEntity.h"
#include "j1NPC.h"


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
	if (current_scene == 0) {
		intro = App->tex->Load("textures/Start.png");
		App->audio->PlayMusic("audio/music/intro.ogg");
	}
	if (current_scene == 1) {
		background1_small = App->tex->Load("maps/fondo1_small.png");
		App->map->Load("Level1-0_v3 - Tomás.tmx");
		//App->audio->PlayMusic("audio/music/Scene1.ogg");
	}
	if (current_scene == 2) {
		background2_small = App->tex->Load("maps/fondo2_small.png");
		App->map->Load("Level2-0_v2.tmx");
		//App->audio->PlayMusic("audio/music/intro.ogg");
	}

	App->entity_manager->AddEntity(ENTITY_TYPE::ENTITY_TYPE_ENEMY_AIR1, 600, 600);


	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate() {
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt) {	
	{//DEBUG KEYS
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
			if (current_scene == 1) {
				App->player->position.x = App->player->originalPosition_1.x;
				App->player->position.y = App->player->originalPosition_1.y;
			}
			if (current_scene == 2) {
				App->player->position.x = App->player->originalPosition_2.x;
				App->player->position.y = App->player->originalPosition_2.y;
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
	}
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN && App->audio->volume < 128) App->audio->volume += 4; //INCRESE VOLUME
	
	if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN && App->audio->volume > 0) App->audio->volume -= 4; //DECREASE VOLUME


	if (current_scene == 1) App->render->Blit(background1_small, App->player->position.x - 250, App->player->position.y - 200);
	else if (current_scene == 2) App->render->Blit(background2_small, App->player->position.x - 250, App->player->position.y - 200);

	App->map->Draw(-App->render->camera.x);
	App->map->CollidersMap();
	
	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count(),
					map_coordinates.x, map_coordinates.y);

	App->win->SetTitle(title.GetString());

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate() {
	bool ret = true;
	
	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) ret = false; //QUIT

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp() {
	LOG("Freeing scene");
	if (current_scene == 1) App->tex->UnLoad(background1_small);
	if (current_scene == 2) App->tex->UnLoad(background2_small);
	App->tex->UnLoad(imgwin);
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
		App->player->win = false;
		App->player->position.x = App->player->originalPosition_1.x;
		App->player->position.y = App->player->originalPosition_1.y;
		App->player->velocity.y = 0;
		App->player->current_map = 1;

		App->scene->CleanUp();
		App->scene->Start();
	}

	else if (scene == 2) { //CHANGE TO SCENE 2		(F2)
		App->collisions->CleanUp();
		App->map->CleanUp();
		current_scene = scene;

		App->player->CleanUp();
		App->player->Start();
		App->player->win = false;
		App->player->position.x = App->player->originalPosition_2.x;
		App->player->position.y = App->player->originalPosition_2.y;
		App->player->velocity.y = 0;
		App->player->current_map = 2;

		App->scene->CleanUp();
		App->scene->Start();
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