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


j1Scene::j1Scene() : j1Module() {
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene() {}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config) {
	LOG("Loading Scene");
	current_scene = config.attribute("current_scene").as_int();
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start() {

	fondo1_small = App->tex->Load("maps/fondo1_small.png");
	fondo2_small = App->tex->Load("maps/fondo2_small.png");

	if (current_scene == 0) {
		intro = App->tex->Load("textures/Start.png");
		App->audio->PlayMusic("audio/music/intro.ogg");
	}
	if (current_scene == 1) {
		App->map->Load("Level1-0_v3.tmx");
		App->audio->PlayMusic("audio/music/Scene1.ogg");
	}
	if (current_scene == 2) {
		App->map->Load("Level2-0_v2.tmx");
		App->audio->PlayMusic("audio/music/intro.ogg");
	}
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate() {
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt) {


	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) App->LoadRequest = true;

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) App->SaveRequest = true;

	if (App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN) keys_enabled = !keys_enabled;

	if (keys_enabled) {
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) App->render->camera.y += 100;
		
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) App->render->camera.y -= 100;
		
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) App->render->camera.x += 100;
		
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) App->render->camera.x -= 100;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN && App->audio->volume < 128) App->audio->volume += 4;
	
	if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN && App->audio->volume > 0) App->audio->volume -= 4;

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {

		//App->render->Blit(fondo1_small, App->player->position.x - 250, App->player->position.y - 200);

		if (current_scene != 1) {
			current_scene = 1;
			App->player->current_map = 1;
			App->player->position.x = App->player->originalPosition_1.x;
			App->player->position.y = App->player->originalPosition_1.y;
			App->player->velocity.y = 0;
			App->map->Start();
			App->scene->Start();
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {

		//App->render->Blit(fondo2_small, App->player->position.x - 250, App->player->position.y - 200);

		if (current_scene != 2) {
			current_scene = 2;
			App->player->current_map = 2;
			App->player->position.x = App->player->originalPosition_2.x;
			App->player->position.y = App->player->originalPosition_2.y;
			App->player->velocity.y = 0;
			App->scene->Start();
			App->map->Start();
		}
	}


	if (current_scene == 1) App->render->Blit(fondo1_small, App->player->position.x - 250, App->player->position.y - 200);
	
	if (current_scene == 2) App->render->Blit(fondo2_small, App->player->position.x - 250, App->player->position.y - 200);



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
	pugi::xml_node config;
	
	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) ret = false;

	return ret;
}


// Called before quitting
bool j1Scene::CleanUp() {
	LOG("Freeing scene");
	App->tex->UnLoad(fondo1_small);
	App->tex->UnLoad(fondo2_small);
	App->map->CleanUp();
	App->collisions->CleanUp();
	if (App->player != nullptr)
		App->player->CleanUp();
	App->CleanUp();
	App->tex->UnLoad(imgwin);
	
	return true;
}
