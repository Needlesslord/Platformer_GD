#pragma once
#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "j1Module.h"
struct SDL_Texture;
struct Collider;

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
private:
	SDL_Texture* img = nullptr;

public:
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
};

#endif