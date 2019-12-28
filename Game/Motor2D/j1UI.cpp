#include "j1App.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1UI.h"
#include "j1Textures.h"
#include "j1Scene.h"
#include "j1Render.h"
#include "j1Fonts.h"
#include "j1Player.h"
#include "j1Collisions.h"

j1UI::j1UI() : j1Module() {
	name.create("UI");
}

j1UI::~j1UI() {}

bool j1UI::Awake(pugi::xml_node&) {
	return true;
}

bool j1UI::Start() {
	LOG("Loading UI");
	numbers = App->fonts->Load("textures/UI/Numbers.png", "0123456789", 1);
	twoDots = App->tex->Load("textures/UI/2dots.png");
	shuriken_tex = App->tex->Load("textures/UI/shurikens_small.png");
	shuriken_tex_transparent = App->tex->Load("textures/UI/shurikens_transparent.png");
	lives_tex = App->tex->Load("textures/UI/Heart_Small.png");
	key_small = App->tex->Load("textures/key_small.png");
	renderKey = false;
	renderTimer = false;

	minutes = 0;
		
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

bool j1UI::Update(float dt) {
	if (shurikens == 0) {
		App->render->Blit(shuriken_tex_transparent,  6, 25, NULL, 0.00f);
		App->render->Blit(shuriken_tex_transparent, 26, 25, NULL, 0.00f);
		App->render->Blit(shuriken_tex_transparent, 46, 25, NULL, 0.00f);
	}
	else if (shurikens == 1) {
		App->render->Blit(shuriken_tex, 6, 25, NULL, 0.00f);
		App->render->Blit(shuriken_tex_transparent, 26, 25, NULL, 0.00f);
		App->render->Blit(shuriken_tex_transparent, 46, 25, NULL, 0.00f);
	}
	else if (shurikens == 2) {
		App->render->Blit(shuriken_tex,  6, 25, NULL, 0.00f);
		App->render->Blit(shuriken_tex, 26, 25, NULL, 0.00f);
		App->render->Blit(shuriken_tex_transparent, 46, 25, NULL, 0.00f);
	}
	else if (shurikens == 3) {
		App->render->Blit(shuriken_tex,  6, 25, NULL, 0.00f);
		App->render->Blit(shuriken_tex, 26, 25, NULL, 0.00f);
		App->render->Blit(shuriken_tex, 46, 25, NULL, 0.00f);
	}


	lives = App->player->numLives;
	if (lives > 0) App->render->Blit(lives_tex,  5, 5, NULL, 0.00f);
	if (lives > 1) App->render->Blit(lives_tex, 25, 5, NULL, 0.00f);
	if (lives > 2) App->render->Blit(lives_tex, 45, 5, NULL, 0.00f);


	if (!renderKey) App->render->Blit(key_small, 485, 330, NULL, 0.00f);


	seconds = gameTime.ReadSec();
	for (int i = 0; i < 9; i++) {
		if (seconds > 59) {
			seconds -= 60;
			if (minutes == i) minutes++;
		}
	}
	if (!/*TODO: change*/renderTimer) {
		sprintf_s(minutes_string, 10, "%1d", minutes);
		App->fonts->BlitText(185, 10, numbers, minutes_string);

		sprintf_s(seconds_string, 10, "%1d", seconds);
		App->fonts->BlitText(230, 10, numbers, seconds_string);

		App->render->Blit(twoDots, 239, 10, NULL, 0.00f);
	}

	return true;
}

bool j1UI::PostUpdate() {
	return true;
}

bool j1UI::Load(pugi::xml_node& node) {
	renderKey = node.child("render_key").attribute("value").as_bool();

	return true;
}
bool j1UI::Save(pugi::xml_node& node) {
	node.append_child("render_key").append_attribute("value") = renderKey;

	return true;
}

