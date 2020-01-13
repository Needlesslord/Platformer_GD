#include <math.h>
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Collisions.h"
#include "j1Particles.h"
#include "j1Player.h"
#include "j1UI.h"
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
	onCooldown = false;
	shurikensUsed = 0;
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

	BROFILER_CATEGORY("ParticlesUpdate", Profiler::Color::Orange)

	return true;
}

bool j1Particles::Update(float dt) {
	BROFILER_CATEGORY("ParticlesUpdate", Profiler::Color::OrangeRed)
	if (App->player->godMode) shurikensUsed = 0;
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		p->particleRect.x += p->speed.x * dt; //TODO: Initialize all variables from .XML
		p->anim.speed = 20 * dt;

		if (p->Update() == false) {
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born) {
			App->render->Blit(graphics, p->particleRect.x, p->particleRect.y, &(p->anim.GetCurrentFrame()));
		}
	}
	if (shurikensUsed == 0)	App->UI->shurikens = 3;
	else if (shurikensUsed == 1) {
		App->UI->shurikens = 2;
		if (partialCooldown.ReadSec() >= 3) {
			partialCooldown.Stop();
			shurikensUsed = 0;
		}
	}
	else if (shurikensUsed == 2) {
		App->UI->shurikens = 1;
		if (partialCooldown.ReadSec() >= 5) {
			partialCooldown.Stop();
			shurikensUsed = 0;
		}
	}
	if (onCooldown) {
		App->UI->shurikens = 0;
		if (cooldown.ReadSec() >= 10) {
			cooldown.Stop();
			onCooldown = false;
			shurikensUsed = 0;
		}
	}
	if (App->player->godMode) shurikensUsed = 0;
	return true;
}

bool j1Particles::PostUpdate() {

	BROFILER_CATEGORY("ParticlesUpdate", Profiler::Color::DarkOrange)

	return true;
}

void j1Particles::AddParticle(Particle& particle, int x, int y, COLLIDER_TYPE type, Uint32 delay) {
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)	{
		if (active[i] == nullptr) {
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->particleRect.x = x - App->player->AnimationOffstet.x;
			p->particleRect.y = y;
			p->particleRect.w = 14;
			p->particleRect.h = 14;
			if (App->player->mirror) {
				p->speed.x = -320;
				p->particleRect.x -= App->player->playerWidth + App->player->AnimationOffstet.x;
			}
			else p->speed.x = 320;

			p->collider = App->collisions->AddCollider(p->particleRect, type, App->particles);

			active[i] = p;
			break;
		}
	}
}


void j1Particles::OnCollision(Collider* c1, Collider* c2) {
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)	{
		if (active[i] != nullptr && active[i]->collider == c1) {
			if (c2->type == COLLIDER_ENEMY || c2->type == COLLIDER_WALL) {
				delete active[i];
				active[i] = nullptr;
				break;
			}
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	particleRect.x = 0;
	particleRect.y = 0;
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), particleRect(p.particleRect), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle() {
	if (collider != nullptr) collider->to_delete = true;
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

	if (collider != nullptr)
		collider->SetPos(particleRect.x, particleRect.y);

	return ret;
}

