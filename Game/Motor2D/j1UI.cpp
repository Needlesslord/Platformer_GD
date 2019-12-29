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
#include "j1Input.h"

j1UI::j1UI() : j1Module() {
	name.create("UI");
}

j1UI::~j1UI() {}

bool j1UI::Awake(pugi::xml_node&) {
	return true;
}

bool j1UI::Start() {
	LOG("Loading UI");
	mainMenu_tex = App->tex->Load("ui/menu.png");
	numbers = App->fonts->Load("textures/UI/Numbers.png", "0123456789", 1);
	twoDots = App->tex->Load("textures/UI/2dots.png");
	shuriken_tex = App->tex->Load("textures/UI/shurikens_normal.png");
	shuriken_tex_transparent = App->tex->Load("textures/UI/shurikens_transparent_normal.png");
	lives_tex = App->tex->Load("textures/UI/heart_normal.png");
	key_small = App->tex->Load("textures/key_normal.png");
	key_small_toGet = App->tex->Load("textures/key_small_locked.png");
	renderKey = false;
	renderTimer = false;

	heart1.x = 10;
	heart1.y = 10;

	heart2.x = 45;
	heart2.y = 10;

	heart3.x = 80;
	heart3.y = 10;

	minutes = 0;

	//init blit buttons
								//play
	play_button_hovering_tex = App->tex->Load("textures/UI/buttons/main_menu/play_hover.png");
	play_button_selected_tex = App->tex->Load("textures/UI/buttons/main_menu/play_selected.png");
	play_button_idle_tex = App->tex->Load("textures/UI/buttons/main_menu/play_base.png");
								//continue
	continue_button_hovering_tex = App->tex->Load("textures/UI/buttons/main_menu/continue_hover.png");
	continue_button_selected_tex = App->tex->Load("textures/UI/buttons/main_menu/continue_selected.png");
	continue_button_idle_tex = App->tex->Load("textures/UI/buttons/main_menu/continue_base.png");
	continue_button_locked_tex = App->tex->Load("textures/UI/buttons/main_menu/continue_locked.png");
								//settings
	settings_button_hovering_tex = App->tex->Load("textures/UI/buttons/main_menu/settings_hover.png");
	settings_button_selected_tex = App->tex->Load("textures/UI/buttons/main_menu/settings_selected.png");
	settings_button_idle_tex = App->tex->Load("textures/UI/buttons/main_menu/settings_base.png");
								//credits
	credits_button_hovering_tex = App->tex->Load("textures/UI/buttons/main_menu/credits_hover.png");
	credits_button_selected_tex = App->tex->Load("textures/UI/buttons/main_menu/credits_selected.png");
	creditsbutton_idle_tex = App->tex->Load("textures/UI/buttons/main_menu/credits_base.png");
								//exit
	exit_button_hovering_tex = App->tex->Load("textures/UI/buttons/main_menu/exit_hover.png");
	exit_button_selected_tex = App->tex->Load("textures/UI/buttons/main_menu/exit_selected.png");
	exit_button_idle_tex = App->tex->Load("textures/UI/buttons/main_menu/exit_base.png");



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
	if (mainMenu) { // UI ELEMENTS

		//buttons
		//play
		if (play_button_hovering){}
		if (play_button_selected){}
		if (play_button_idle) App->render->Blit(play_button_idle_tex, 11, 50, NULL, 0.00f);

		//continue
		if (continue_button_hovering){}
		if (continue_button_selected){}
		if (continue_button_idle){}
		if (continue_button_locked){}
		//settings
		if (settings_button_hovering){}
		if (settings_button_selected){}
		if (settings_button_idle){}
		//credits
		if (credits_button_hovering){}
		if (credits_button_selected){}
		if (creditsbutton_idle){}
		//exit
		if (exit_button_hovering){}
		if (exit_button_selected){}
		if (exit_button_idle){}

		//to lvl1

		App->render->Blit(mainMenu_tex, 0, 0, NULL, 0.00f);
		App->player->current_animation = &App->player->player_idle;
		App->player->current_animation->speed = dt * 10;
		App->render->Blit(App->player->player_textures, 300, 300, &(App->player->current_animation->GetCurrentFrame()), 0.00f);

		App->player->current_animation = &App->player->player_idle_gravitySwapped;
		App->player->current_animation->speed = dt * 10;
		App->render->Blit(App->player->player_textures, 400, 350, &(App->player->current_animation->GetCurrentFrame()), 0.00f);

		if (App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN) {
			scene = true;
			mainMenu = false;
			App->scene->SetUpScene();
		}
	}
	else if (scene) { // HUD
		if (shurikens == 0) {
			App->render->Blit(shuriken_tex_transparent, 11, 50, NULL, 0.00f);
			App->render->Blit(shuriken_tex_transparent, 46, 50, NULL, 0.00f);
			App->render->Blit(shuriken_tex_transparent, 81, 50, NULL, 0.00f);
		}
		else if (shurikens == 1) {
			App->render->Blit(shuriken_tex, 11, 50, NULL, 0.00f);
			App->render->Blit(shuriken_tex_transparent, 46, 50, NULL, 0.00f);
			App->render->Blit(shuriken_tex_transparent, 81, 50, NULL, 0.00f);
		}
		else if (shurikens == 2) {
			App->render->Blit(shuriken_tex, 11, 50, NULL, 0.00f);
			App->render->Blit(shuriken_tex, 46, 50, NULL, 0.00f);
			App->render->Blit(shuriken_tex_transparent, 81, 50, NULL, 0.00f);
		}
		else if (shurikens == 3) {
			App->render->Blit(shuriken_tex, 11, 50, NULL, 0.00f);
			App->render->Blit(shuriken_tex, 46, 50, NULL, 0.00f);
			App->render->Blit(shuriken_tex, 81, 50, NULL, 0.00f);
		}


		lives = App->player->numLives;
		if (lives > 0) {
			App->render->Blit(lives_tex, 10, 10, NULL, 0.00f);
			if (lives > 1) {
				App->render->Blit(lives_tex, 45, 10, NULL, 0.00f);
				if (lives > 2) App->render->Blit(lives_tex, 80, 10, NULL, 0.00f);
				else {
					heart3.y += dt * 500;
					App->render->Blit(lives_tex, 80, heart3.y, NULL, 0.00f);
				}
			}
			else {
				heart2.y += dt * 500;
				App->render->Blit(lives_tex, 45, heart2.y, NULL, 0.00f);
			}
		}


		if (renderKey) App->render->Blit(key_small, 485, 330, NULL, 0.00f);
		else App->render->Blit(key_small_toGet, 485, 330, NULL, 0.00f);

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
		if (App->player->score < 10000) sprintf_s(score_string, 10, "%1d", App->player->score);
		if (App->player->score < 1000) sprintf_s(score_string, 10, "0%1d", App->player->score);
		if (App->player->score < 100) sprintf_s(score_string, 10, "00%1d", App->player->score);
		if (App->player->score < 10) sprintf_s(score_string, 10, "000%1d", App->player->score);
		App->fonts->BlitText(385, 10, numbers, score_string);
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

