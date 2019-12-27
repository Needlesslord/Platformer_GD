#include "j1Module.h"
#include "p2Point.h"

struct SDL_Texture;

class j1UI : public j1Module {
public:
	j1UI();
	virtual ~j1UI();
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	bool Load(pugi::xml_node& node);
	bool Save(pugi::xml_node& node);

public:
	uint shurikens;
	SDL_Texture* shuriken_tex;
	SDL_Texture* shuriken_tex_transparent;

	uint lives;
	SDL_Texture* lives_tex;

	bool renderKey;
	bool renderTimer;

	int numbers = 0;

	uint seconds;
	char seconds_string[10];
	uint minutes;
	char minutes_string[10];
	j1Timer gameTime;
	
};
