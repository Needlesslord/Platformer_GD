#pragma once
#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__
#include "j1Module.h"
#include "j1Animation.h"
struct SDL_Texture;
struct Collider;

enum player_states {
	PLAYER_ST_UNKNOWN = 0,
	//right
	PLAYER_ST_IDLE_R,
	PLAYER_ST_WALKING_R,
	PLAYER_ST_JUMPING_R,
	PLAYER_ST_DUBLEJUMPING_R,
	PLAYER_ST_FALLING_R,
	PLAYER_ST_APPERING_R,
	PLAYER_ST_DISAPPEARING_R,
	PLAYER_ST_HIT_R,
	PLAYER_ST_DASHING_R,
	PLAYER_ST_DEATH_R,
	//right
	PLAYER_ST_IDLE_L,
	PLAYER_ST_WALKING_L,
	PLAYER_ST_JUMPING_L,
	PLAYER_ST_DUBLEJUMPING_L,
	PLAYER_ST_FALLING_L,
	PLAYER_ST_APPERING_L,
	PLAYER_ST_DISAPPEARING_L,
	PLAYER_ST_HIT_L,
	PLAYER_ST_DASHING_L,
	PLAYER_ST_DEATH_L,
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
	bool Loading();
	bool Save();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	void DoubleJump();
	void MirrorSprite();
	void RestartPlayer();
	bool CameraOnPlayer();

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
	/*
	j1Animation* current_j1Animation = nullptr;
	j1Animation idle;
	j1Animation up;
	j1Animation down;
	*/
	float positionX;
	float positionY;
	float desiredPositionX;
	float desiredPositionY;
	float velocityX;
	float velocityY;
	Collider* colup;
	Collider* coldown;
	Collider* colright;
	Collider* colleft;
	//Collider* col2;
	bool destroyed = false;
	bool jumping;
	bool Alive;
	player_states current_state;
};

#endif