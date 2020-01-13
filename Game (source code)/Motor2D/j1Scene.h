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
	bool Load(pugi::xml_node& node);
	bool Save(pugi::xml_node& node);
	bool CleanUp();
	bool SetUpScene();
	bool changeSceneTo(int scene);
	bool keys_enabled = false;

	SDL_Texture* imgwin = nullptr;
	SDL_Texture* intro;
	SDL_Texture* background1_small;
	SDL_Texture* background2_small;

	int current_scene;

private:
	SDL_Texture* img;
};

#endif // __j1SCENE_H__