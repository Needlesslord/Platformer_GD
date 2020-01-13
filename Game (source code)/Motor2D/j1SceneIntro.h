#ifndef __j1SCENEIntro_H__
#define __j1SCENEIntro_H__
#include "j1Module.h"

struct SDL_Texture;

class j1SceneIntro : public j1Module {
public:
	j1SceneIntro();
	virtual ~j1SceneIntro();
	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool Load(pugi::xml_node& node);
	bool Save(pugi::xml_node& node);
	bool CleanUp();
	bool changeSceneTo(int scene);
	bool keys_enabled = false;

	SDL_Texture* imgwin = nullptr;

	int current_scene;

private:
	SDL_Texture* menu_base;

};

#endif // __j1SCENEIntro_H__