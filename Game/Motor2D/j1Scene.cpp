#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	img = App->tex->Load("textures/test.png");
	App->audio->PlayMusic("audio/music/music_sadpiano.ogg");
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	// TODO 1: Request Load / Save on application when pressing L/S
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->load = true;

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->save = true;

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y -= 1;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y += 1;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x -= 1;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x += 1;

	if (App->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_DOWN && App->audio->volume < 128)
		App->audio->volume += 2;

	if (App->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_DOWN && App->audio->volume > 0)
		App->audio->volume -= 2;

	App->render->Blit(img, 0, 0);
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
