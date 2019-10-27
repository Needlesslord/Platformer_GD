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
	bool keys_enabled = true;

	Collider* colliders[50];

	p2List<p2SString> maps;
	//p2SString current_map;
	bool cullingView = false;
	bool cameraMoving = true;
	bool lateralMove = false;
	SDL_Texture* imgwin = nullptr;

private:
	SDL_Texture* img;

	int cameraLimitX;
	int cameraLimitY;
};

#endif // __j1SCENE_H__