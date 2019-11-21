#include "j1App.h"
#include "j1Enemy_Air1.h"
#include "j1Collisions.h"
#include <cmath>


Enemy_Air1::Enemy_Air1(float x, float y) : Enemy(x, y)
{
	fly.PushBack({ 5,6,24,24 });
	fly.PushBack({ 38, 6, 24, 24 });
	fly.speed = 0.2f;

	animation = &fly;

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY);

	original_y = y;
}

void Enemy_Air1::Move()
{
	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.05f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.05f;
	}

	position.y = original_y + (25.0f * sin(wave));
	position.x -= 1;
}
