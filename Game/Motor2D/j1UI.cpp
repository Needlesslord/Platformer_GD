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


	//Play Button
	AddButton(550, 122, PLAY, false, play_button_idle_tex, play_button_selected_tex, play_button_hovering_tex, nullptr, true);
	AddButton(550, 170, CONTINUE, true, continue_button_idle_tex, continue_button_selected_tex, continue_button_hovering_tex, continue_button_locked_tex, true);
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

		for (p2List_item<UIButton*>* item = buttons.start; item != nullptr; item = item->next) {
			if (item->data->hasToBeRendered) item->data->Draw();
		}

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

UIButton::UIButton(){}
UIButton::~UIButton() {}

void UIButton::Draw() {
	if(locked) App->render->Blit(locked_tex, position.x, position.y, NULL, 0.00f);
	else if(state==HOVERING) App->render->Blit(hovering_tex, position.x, position.y, NULL, 0.00f);
	else if(state==SELECTED) App->render->Blit(selected_tex, position.x, position.y, NULL, 0.00f);
	else App->render->Blit(idle_tex, position.x, position.y, NULL, 0.00f);
}

void j1UI::AddButton(int x, int y, UIButton_type type, bool locked, SDL_Texture* idle_tex, SDL_Texture* selected_tex, SDL_Texture* hovering_tex, SDL_Texture* locked_tex, bool hasToBeRendered) {
	UIButton* button;
	button = new UIButton();
	button->position.x = x;
	button->position.y = y;
	button->type = type;
	button->locked = locked;
	button->idle_tex = idle_tex;
	button->selected_tex = selected_tex;
	button->hovering_tex = hovering_tex;
	button->locked_tex = locked_tex;
	button->hasToBeRendered = hasToBeRendered;
	buttons.add(button);
}