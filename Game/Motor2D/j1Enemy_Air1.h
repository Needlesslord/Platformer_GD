#ifndef __j1ENEMY_AIR1_H__
#define __j1ENEMY_AIR1_H__

#include "j1Enemy.h"

class Enemy_Air1 : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	float original_y = 0;
	j1Animation fly;
	j1Animation flyM;
	float distance;

public:

	Enemy_Air1(float x, float y);

	void Move();
	//void Draw(SDL_Texture* sprites);

};

#endif 
// __j1ENEMY_AIR1_H__