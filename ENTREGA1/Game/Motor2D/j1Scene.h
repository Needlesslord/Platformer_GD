#ifndef __j1SCENE_H__
#define __j1SCENE_H__
#include "j1Module.h"

struct SDL_Texture;

class j1Scene : public j1Module {
public:
	j1Scene();
	virtual ~j1Scene();
	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool Load();
	bool Save();
	bool CleanUp();
	bool keys_enabled = false;

	Collider* colliders[50];

	SDL_Texture* imgwin = nullptr;
	SDL_Texture* intro;
	SDL_Texture* fondo1_small;
	int current_scene;

private:
	SDL_Texture* img;

	int cameraLimitX;
	int cameraLimitY;
};

#endif // __j1SCENE_H__