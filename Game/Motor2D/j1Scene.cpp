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

//#include "MAP.h"

j1Scene::j1Scene() : j1Module() {
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene() {}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config) {
	LOG("Loading Scene");

	//pugi::xml_node map;

	//for (map = config.child("map"); map; map = map.next_sibling("map")) {
	//	p2SString* level=new p2SString();
	//		level->create(map.attribute("name").as_string());
	//		maps.add(level->GetString());
	//}

	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start() {

	App->map->Load("NUTO-Level1-0_v2_col.tmx");
	

	//if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) App->map->Load("NUTO-Level1-0_v2_col.tmx");

	//if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN) App->map->Load("NUTO-Level1-5_v1_coll.tmx");

	//if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) App->map->Load("NUTO-Level2-0_v1_col.tmx");


	//current_map = maps.start->data;
	//App->map->Load(current_map.GetString());



	//App->collisions->AddCollider({ 0, 200, 3930, 16 }, COLLIDER_WALL);
	//App->collisions->AddCollider({ 200, 64, 50, 16 }, COLLIDER_WALL);

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate() {
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt) {
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) App->LoadRequest = true;

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) App->SaveRequest = true;

	if (keys_enabled) {
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) App->render->camera.y -= 100;
		
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) App->render->camera.y += 100;
		
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) App->render->camera.x -= 100;
		
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) App->render->camera.x += 100;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_DOWN && App->audio->volume < 128) App->audio->volume += 2;
	
	if (App->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_DOWN && App->audio->volume > 0) App->audio->volume -= 2;




	//p2List_item<p2SString>* i = maps.start;
	//i = i->next;


	//App->render->Blit(img, 0, 0);
	//App->map->Draw();
	//p2SString title("Ninja_Frog_Against_Gravity");

	App->map->Draw();
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

	//if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) {
	//	//current_scene scene="true" intro="false" l1="false" l2="false"
	//	current_scene = config.child("current_scene").attribute("scene").as_int();
	//	//following_scene = config.child("current_scene").attribute("l1").as_bool(true);
	//	App->intro;
	//}	
	
	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp() {
	LOG("Freeing scene");

	return true;
}
