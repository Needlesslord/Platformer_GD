#include "j1Module.h"
#include "p2Point.h"

struct SDL_Texture;

class j1UI : public j1Module {
public:
	j1UI();
	virtual ~j1UI();

	bool Start();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool CleanUp();

public:
	SDL_Texture* game_over = nullptr;

	int numbers = 0;
	char numbers_string[10];
};
