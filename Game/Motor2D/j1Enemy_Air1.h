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

public:

	Enemy_Air1(float x, float y);

	void Move();
};

#endif 
// __j1ENEMY_AIR1_H__