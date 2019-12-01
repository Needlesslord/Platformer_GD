#include <math.h>
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Collisions.h"
#include "j1Particles.h"
#include "j1Player.h"
#include "Brofiler.h"
#include "SDL/include/SDL_timer.h"

j1Particles::j1Particles() {
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	shuriken.anim.PushBack({ 115,  0, 14, 14 });
	shuriken.anim.PushBack({ 115, 14, 14, 14 });
	shuriken.anim.speed = 0.3f;
	shuriken.life = 1500;
}

j1Particles::~j1Particles()
{}

// Load assets
bool j1Particles::Start() {
	graphics = App->tex->Load("textures/Ninja_Frog.png");
	return true;
}

// Unload assets
bool j1Particles::CleanUp() {
	App->tex->UnLoad(graphics);
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}
	return true;
}

bool j1Particles::PreUpdate() {
	return true;
}

bool j1Particles::Update(float dt) {
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false) {
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born) {
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
		}
	}

	return true;
}

bool j1Particles::PostUpdate() {
	return true;
}

void j1Particles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay) {
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)	{
		if (active[i] == nullptr) {
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x - App->player->AnimationOffstet.x;
			p->position.y = y;
			if (App->player->mirror) {
				p->speed.x = -5;
				p->position.x -= App->player->playerWidth + App->player->AnimationOffstet.x;
			}
			else p->speed.x = 5;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

void j1Particles::OnCollision(Collider* c1, Collider* c2) {
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1) {
			//AddParticle(explosion, active[i]->position.x, active[i]->position.y);
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished()) ret = false;

	position.x += speed.x;


	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}

