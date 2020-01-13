#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "j1Module.h"
#include "j1Animation.h"
#include "p2Point.h"
#include "j1Collisions.h"
#include "j1Timer.h"

#define MAX_ACTIVE_PARTICLES 30

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle
{
	Collider* collider;
	j1Animation anim;
	uint fx = 0;
	SDL_Rect particleRect;
	fPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;
	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class j1Particles : public j1Module
{
public:
	j1Particles();
	~j1Particles();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay = 0);

private:

	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];

public:
	Particle shuriken;
	j1Timer partialCooldown;
	uint shurikensUsed;
	bool onCooldown;
	j1Timer cooldown;
};

#endif // __MODULEPARTICLES_H__
