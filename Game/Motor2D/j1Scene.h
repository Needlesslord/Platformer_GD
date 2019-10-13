#ifndef __j1SCENE_H__
#define __j1SCENE_H__
#include "j1Module.h"

struct SDL_Texture;

class j1Scene : public j1Module {
public:
	j1Scene();
	virtual ~j1Scene();
	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

private:
	SDL_Texture* img;
	bool current_scene;
	bool following_scene;
	bool change_scene;
};

#endif // __j1SCENE_H__