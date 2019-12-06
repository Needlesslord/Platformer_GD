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

public:
	uint shurikens;
	SDL_Texture* shuriken_tex;
	SDL_Texture* shuriken_tex_transparent;

	uint lives;
	SDL_Texture* lives_tex;

	int numbers = 0;
};
