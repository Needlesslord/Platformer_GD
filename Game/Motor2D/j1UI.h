#include "j1Module.h"
#include "p2Point.h"

struct SDL_Texture;

enum UIElement_type {
	UI_BUTTON,
	UI_TEXT,
	UI_BOX,
	UI_NO_TYPE
};
class UIElement {
public:
	UIElement(UIElement_type type, int x, int y, SDL_Texture* sprites = nullptr) : type(type), position(x, y), initialPosition(x, y), sprites(sprites) {}
	~UIElement() {}

	virtual void Draw(int x = 0, int y = 0) {}

public:
	UIElement_type type;
	bool visible = true;

	iPoint initialPosition;
	iPoint position;

	SDL_Texture* sprites = nullptr;
};

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

	bool renderKey;
	SDL_Texture* key_small;

	uint lives;
	iPoint heart1;
	iPoint heart2;
	iPoint heart3;
	SDL_Texture* lives_tex;

	bool renderTimer;
	int numbers = 0;
	SDL_Texture* twoDots;
	uint seconds;
	char seconds_string[10];
	uint minutes;
	char minutes_string[10];
	j1Timer gameTime;
	
	char score_string[10];

	bool mainMenu = true;
	bool scene = false;
};
