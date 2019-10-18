#ifndef __j1INTRO_H__
#define __j1INTRO_H__
#include "j1Module.h"

struct SDL_Texture;

class j1Intro : public j1Module {
public:
	j1Intro();
	virtual ~j1Intro();
	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

private:
	SDL_Texture* img;
};

#endif // __j1SCENE_H__





















//#ifndef __j1INTRO_H__
//#define __MODULESCENEINTRO_H__
//
//#include "j1Module.h"
//#include "j1Animation.h"
//#include "j1ModuleAudio.h"
////#include "j1Globals.h"
//
//struct SDL_Texture;
//
//enum update_status {
//	UPDATE_CONTINUE = 1,
//	UPDATE_STOP,
//	UPDATE_ERROR
//};
//
//class ModuleSceneIntro : public j1Module {
//public:
//	ModuleSceneIntro();
//	~ModuleSceneIntro();
//	bool Start();
//	update_status Update();
//	bool CleanUp();
//
//public:
//	SDL_Texture* graphics = nullptr;
//	SDL_Rect background;
//	j1Animation water;
//	Mix_Music* music = nullptr;
//};
//
//#endif // __MODULESCENEINTRO_H__