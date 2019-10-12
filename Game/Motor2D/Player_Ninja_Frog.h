#pragma once
#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

private:
	SDL_Texture* graphics = nullptr;

public:

	Animation* current_animation = nullptr;
	Animation idle;
	Animation up;
	Animation down;


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
};

#endif