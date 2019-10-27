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
	void Mirror();
	//void RestartPlayer();
	//bool CameraOnPlayer();

private:
	SDL_Texture* img = nullptr;

public:
	SDL_Texture* graphics = nullptr;
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
	iPoint originalPosition;
	int playerHeight;
	int playerWidth;
	fPoint desiredPosition;
	fPoint velocity;
	float gravity;
	Collider* col;
	SDL_Rect feet;
	Collider* colFeet;
	SDL_Rect rightside;
	Collider* colRightside;
	SDL_Rect leftside;
	Collider* colLeftside;

	bool S_Down = false;
	bool grounded;
	bool hasDoubleJumped;
	bool alive;
	player_states current_state;
	p2SString			folder;
	p2SString			texture;
	bool mirror = false;
};

#endif