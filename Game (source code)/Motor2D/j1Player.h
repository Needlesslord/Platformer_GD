#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__
#include "j1Module.h"
#include "PugiXml/src/pugixml.hpp"
#include "j1Animation.h"
#include "p2Point.h"
#include "j1Timer.h"
struct SDL_Texture;
struct Collider;

enum player_states {
	PLAYER_ST_UNKNOWN = 0,
	//right
	PLAYER_ST_IDLE,
	PLAYER_ST_WALKING,
	PLAYER_ST_JUMPING,
	PLAYER_ST_DUBLEJUMPING,
	PLAYER_ST_FALLING,
	PLAYER_ST_APPERING,
	PLAYER_ST_DISAPPEARING,
	PLAYER_ST_HIT,
	PLAYER_ST_DASHING,
	PLAYER_ST_DEATH,
};

class j1Player : public j1Module {
public:
	j1Player();
	virtual ~j1Player();
	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool Load(pugi::xml_node& node);
	bool Save(pugi::xml_node& node);
	void MoveEverything(bool swapped, float dt);
	bool ChangeGravity(bool withImpulse);
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	void GameOver();
public:
	SDL_Texture* player_textures = nullptr;
	SDL_Texture* player_textures_godmode = nullptr;
	SDL_Texture* img_m = nullptr; SDL_Texture* imgwin = nullptr;
	j1Animation* current_animation;

	j1Animation player_idle;
	j1Animation player_idle_mirror;
	j1Animation player_idle_gravitySwapped;
	j1Animation player_idle_mirror_gravitySwapped;

	j1Animation player_walking;
	j1Animation player_walking_mirror;
	j1Animation player_walking_gravitySwapped;
	j1Animation player_walking_mirror_gravitySwapped;

	j1Animation player_jumping;
	j1Animation player_jumping_mirror;
	j1Animation player_jumping_gravitySwapped;
	j1Animation player_jumping_mirror_gravitySwapped;

	j1Animation player_doublejumping;
	j1Animation player_falling;
	j1Animation player_appearing;
	j1Animation player_disappearing;
	j1Animation player_hit;
	j1Animation player_dashing;
	j1Animation player_death;
	
	fPoint position;
	iPoint originalPosition_1;
	iPoint originalPosition_2;
	iPoint originalPosition_tutorial;

	int playerHeight;
	int playerWidth;
	fPoint velocity;
	fPoint maxSpeed;
	float impulse;
	float gravity;
		Collider* col;
	SDL_Rect feet;
		Collider* colFeet;
	SDL_Rect rightside;
		Collider* colRightside;
	SDL_Rect leftside;
		Collider* colLeftside;
	SDL_Rect head;
		Collider* colHead;
	iPoint AnimationOffstet;
	iPoint directWin_1;
	iPoint directWin_2;

	bool grounded;
	bool againstRightSide;
	bool againstLeftSide;
	bool againstRoof;

	bool hasDoubleJumped;
	bool godMode = false;

	bool doorLocked = true;
	SDL_Texture* lockedDoor;
	Collider* key;
	SDL_Texture* key_tex;
	SDL_Texture* key_tex_not;

	SDL_Texture* subMenu_tex;
	SDL_Texture* subMenuBackground_tex;

	// CHECKPOINTS
	j1Animation checkpoint_saved_1;
	j1Animation checkpoint_unsaved_1;
	Collider* checkpoint_1;
	SDL_Texture* checkpoint_1_tex;		//has to be made an animation
	bool autosave_1 = false;

	bool gravitySwapped;

	bool justSwapped = false;
	j1Timer swapTimer;

	bool justDied = false;
	j1Timer dieTimer;

	j1Timer past2Sec;

	p2SString			folder;
	p2SString			texture;
	bool mirror = false;
	int current_map = 1;

	Collider* col_particle;

	uint numLives;
	uint initialLives;

	bool isDead;
	bool paused = false;

	uint score;
};

#endif