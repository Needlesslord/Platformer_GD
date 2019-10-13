

//
//Update = config.child("update_status").attribute("width").as_bool(false);
//
//
//
//
//#include <math.h>
//#include "j1App.h"
//#include "j1FadeToBlack.h"
//#include "j1Render.h"
//#include "SDL/include/SDL_render.h"
//#include "SDL/include/SDL_timer.h"
//#include "j1Module.h"
//
//FadeToBlack::FadeToBlack()
//{
//	screen = { 0, 0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE };
//}
//
//FadeToBlack::~FadeToBlack()
//{}
//
//// Load assets
//bool FadeToBlack::Start()
//{
//	LOG("Preparing Fade Screen");
//	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
//	return true;
//}
//
//// Update: draw background
//update_status FadeToBlack::Update()
//{
//	if (current_step == fade_step::none)
//		return UPDATE_CONTINUE;
//
//	Uint32 now = SDL_GetTicks() - start_time;
//	float normalized = MIN(1.0f, (float)now / (float)total_time);
//
//	switch (current_step)
//	{
//	case fade_step::fade_to_black:
//	{
//		if (now >= total_time)
//		{
//			// TODO 2: enable / disable the modules received when FadeToBlacks() gets called
//			to_disable->Disable();
//			to_enable->Enable();
//			// ---
//			total_time += total_time;
//			start_time = SDL_GetTicks();
//			current_step = fade_step::fade_from_black;
//		}
//	} break;
//
//	case fade_step::fade_from_black:
//	{
//		normalized = 1.0f - normalized;
//
//		if (now >= total_time)
//			current_step = fade_step::none;
//	} break;
//	}
//
//	// Finally render the black square with alpha on the screen
//	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(normalized * 255.0f));
//	SDL_RenderFillRect(App->render->renderer, &screen);
//
//	return UPDATE_CONTINUE;
//}
//
//// Fade to black. At mid point deactivate one module, then activate the other
//bool ModuleFadeToBlack::FadeToBlack(Module* module_off, Module* module_on, float time)
//{
//	bool ret = false;
//
//	if (current_step == fade_step::none)
//	{
//		current_step = fade_step::fade_to_black;
//		start_time = SDL_GetTicks();
//		total_time = (Uint32)(time * 0.5f * 1000.0f);
//		to_enable = module_on;
//		to_disable = module_off;
//		ret = true;
//	}
//
//	return ret;
//}