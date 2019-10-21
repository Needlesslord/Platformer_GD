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
	bool Load();
	bool Save();
	bool CleanUp();
	bool level1_active = true;
	bool level2_active = false;
	bool intro_active = false;
	bool keys_enabled = true;

private:
	SDL_Texture* img;
	//int	current_scene;
	//bool	following_scene;
	//bool	change_scene;
};

#endif // __j1SCENE_H__