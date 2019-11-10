#pragma once
#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__
#include "j1Module.h"
#include "PugiXml/src/pugixml.hpp"
#include "j1Animation.h"
#include "p2Point.h"
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
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
/*	void DoubleJump()*/;
	bool Mirror();
	//void RestartPlayer();
	//bool CameraOnPlayer();

private:
	SDL_Texture* img = nullptr;
	SDL_Texture* img_m = nullptr;


public:
	SDL_Texture* graphics = nullptr;
	SDL_Texture* imgwin = nullptr;
	j1Animation* current_animation;
	j1Animation player_idle;
	j1Animation player_walking;
	j1Animation player_jumping;
	j1Animation player_doublejumping;
	j1Animation player_falling;
	j1Animation player_appearing;
	j1Animation player_disappearing;
	j1Animation player_hit;
	j1Animation player_dashing;
	j1Animation player_daeth;
	
	fPoint position;
	iPoint originalPosition_1;
	iPoint originalPosition_2;
	int playerHeight;
	int playerWidth;
	fPoint velocity;
	float gravity;
	Collider* col;
	SDL_Rect feet;
	Collider* colFeet;
	SDL_Rect rightside;
	Collider* colRightside;
	SDL_Rect leftside;
	Collider* colLeftside;
	iPoint AnimationOffstet;
	iPoint directWin_1;
	iPoint directWin_2;

	bool playerCanMove = false;
	bool X_Down = false;
	bool grounded;
	bool hasDoubleJumped;
	bool alive;
	bool godMode = false;
	player_states current_state;
	p2SString			folder;
	p2SString			texture;
	bool mirror = false;
	int current_map = 1;
};

#endif