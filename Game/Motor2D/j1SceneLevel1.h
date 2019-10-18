#ifndef __j1SCENELEVEL1_H__
#define __j1SCENELEVEL1_H__
#include "j1Module.h"

struct SDL_Texture;

class j1SceneLevel1 : public j1Module {
public:
	j1SceneLevel1();
	virtual ~j1SceneLevel1();
	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool Loading();
	bool Saving();
	bool CleanUp();

private:
	SDL_Texture* img;
	int		current_scene;
	bool	following_scene;
	bool	change_scene;
};

#endif // __j1SCENELEVEL1_H__