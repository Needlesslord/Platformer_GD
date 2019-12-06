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
	shuriken_tex = App->tex->Load("textures/UI/shurikens_normal.png");
	shuriken_tex_transparent = App->tex->Load("textures/UI/shurikens_transparent.png");
	lives_tex = App->tex->Load("textures/UI/hearts.png");
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
		App->render->Blit(shuriken_tex_transparent, App->player->position.x - 234, App->player->position.y - 130);
		App->render->Blit(shuriken_tex_transparent, App->player->position.x - 199, App->player->position.y - 130);
		App->render->Blit(shuriken_tex_transparent, App->player->position.x - 164, App->player->position.y - 130);
	}
	else if (shurikens == 1) {
		App->render->Blit(shuriken_tex, App->player->position.x - 234, App->player->position.y - 130);
		App->render->Blit(shuriken_tex_transparent, App->player->position.x - 199, App->player->position.y - 130);
		App->render->Blit(shuriken_tex_transparent, App->player->position.x - 164, App->player->position.y - 130);
	}
	else if (shurikens == 2) {
		App->render->Blit(shuriken_tex, App->player->position.x - 234, App->player->position.y - 130);
		App->render->Blit(shuriken_tex, App->player->position.x - 199, App->player->position.y - 130);
		App->render->Blit(shuriken_tex_transparent, App->player->position.x - 164, App->player->position.y - 130);
	}
	else if (shurikens == 3) {
		App->render->Blit(shuriken_tex, App->player->position.x - 234, App->player->position.y - 130);
		App->render->Blit(shuriken_tex, App->player->position.x - 199, App->player->position.y - 130);
		App->render->Blit(shuriken_tex, App->player->position.x - 164, App->player->position.y - 130);
	}

	App->render->Blit(lives_tex, App->player->col->rect.x - 235, App->player->col->rect.y - 160);
	App->render->Blit(lives_tex, App->player->col->rect.x - 200, App->player->col->rect.y - 160);
	App->render->Blit(lives_tex, App->player->col->rect.x - 165, App->player->col->rect.y - 160);
	return true;
}

bool j1UI::PostUpdate() {
	return true;
}

