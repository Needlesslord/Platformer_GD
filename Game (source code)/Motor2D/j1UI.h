#include "j1Module.h"
#include "p2Point.h"

struct SDL_Texture;

enum UIButton_state {
	IDLE,
	HOVERING,
	SELECTED,
	ACTING
};

enum UIButton_type {
	PLAY,
	CONTINUE,
	SETTINGS,
	CREDITS,
	EXIT,
	BACK,
	NO_TYPE
};

class UIButton {
public:
	UIButton();
	virtual ~UIButton();
	void Draw();

public:
	UIButton_state state = IDLE;
	UIButton_type type = NO_TYPE;
	bool locked = false;
	bool hasToBeRendered;
	void UpdateMouse();
	iPoint position;
	uint width = 90;
	uint height = 30;
	SDL_Texture* hovering_tex = nullptr;
	SDL_Texture* selected_tex = nullptr;
	SDL_Texture* idle_tex = nullptr;
	SDL_Texture* locked_tex = nullptr;
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

	SDL_Texture* resume_button_hovering_tex;
	SDL_Texture* resume_button_selected_tex;
	SDL_Texture* resume_button_idle_tex;

	SDL_Texture* back_button_hovering_tex;
	SDL_Texture* back_button_selected_tex;
	SDL_Texture* back_button_idle_tex;

	void AddButton(int x, int y, UIButton_type type, bool locked, SDL_Texture* idle_tex, SDL_Texture* selected_tex, SDL_Texture* hovering_tex, SDL_Texture* locked_tex, bool hasToBeRendered);
	p2List<UIButton*> buttons;

	SDL_Texture* title1_tex;
	SDL_Texture* background_tex;
	SDL_Texture* terrain_tex;

	SDL_Texture* credits;
	bool showCredits = false;
};
