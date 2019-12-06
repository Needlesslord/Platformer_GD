#include "j1App.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1UI.h"
#include "j1Textures.h"
#include "j1Scene.h"
#include "j1Render.h"
#include "j1Fonts.h"

j1UI::j1UI() : j1Module()
{}

j1UI::~j1UI()
{}

// Load assets
bool j1UI::Start() {
	LOG("Loading UI");
	numbers = App->fonts->Load("textures/UI/", "0123", 1);

	return true;
}

bool j1UI::CleanUp() {
	LOG("Unloading UI");
	App->fonts->UnLoad(numbers);

	return true;
}

bool j1UI::PreUpdate() {
	return true;
}

bool j1UI::Update() {
	sprintf_s(numbers_string, 10, "%1d", numbers);
	App->fonts->BlitText(200, 200, numbers, numbers_string);
	return true;
}

bool j1UI::PostUpdate() {
	return true;
}

