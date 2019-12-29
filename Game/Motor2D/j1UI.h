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
	SDL_Texture* mainMenu_tex;

	uint shurikens;
	SDL_Texture* shuriken_tex;
	SDL_Texture* shuriken_tex_transparent;

	bool renderKey;
	SDL_Texture* key_small;
	SDL_Texture* key_small_toGet;

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

	//buttons working
	//play
	bool play_button_hovering = false;
	bool play_button_selected = false;
	bool play_button_idle = true;
	//continue
	bool continue_button_hovering = false;
	bool continue_button_selected = false;
	bool continue_button_idle = false;
	bool continue_button_locked = true;
	//settings
	bool settings_button_hovering = false;
	bool settings_button_selected = false;
	bool settings_button_idle = true;
	//credits
	bool credits_button_hovering = false;
	bool credits_button_selected = false;
	bool creditsbutton_idle = true;
	//exit
	bool exit_button_hovering = false;
	bool exit_button_selected = false;
	bool exit_button_idle = true;
	//buttons img
	//play
	SDL_Texture* play_button_hovering_tex;
	SDL_Texture* play_button_selected_tex;
	SDL_Texture* play_button_idle_tex;
	//continue
	SDL_Texture* continue_button_hovering_tex;
	SDL_Texture* continue_button_selected_tex;
	SDL_Texture* continue_button_idle_tex;
	SDL_Texture* continue_button_locked_tex;
	//settings
	SDL_Texture* settings_button_hovering_tex;
	SDL_Texture* settings_button_selected_tex;
	SDL_Texture* settings_button_idle_tex;
	//credits
	SDL_Texture* credits_button_hovering_tex;
	SDL_Texture* credits_button_selected_tex;
	SDL_Texture* creditsbutton_idle_tex;
	//exit
	SDL_Texture* exit_button_hovering_tex;
	SDL_Texture* exit_button_selected_tex;
	SDL_Texture* exit_button_idle_tex;

	SDL_Texture* title1_tex;
	SDL_Texture* background_tex;
	SDL_Texture* terrain_tex;

};
