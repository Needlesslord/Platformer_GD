#include "j1Entity.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "j1Collisions.h"
#include "j1Particles.h"
#include "j1Player.h"
#include "j1Level1.h"
#include "j1Level2.h"
#include "j1Animation.h"

j1Entity::j1Entity(float x, float y) : position(x, y)
{
	//name.create("entity");

}

j1Entity::~j1Entity() {}

//bool j1Entity::Awake(pugi::xml_node& config);
//{
//	return true;
//}

bool j1Entity::Start()
{
	return true;
}

void j1Entity::Draw(SDL_Texture* sprites)
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (animation != nullptr)
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}

bool j1Entity::PreUpdate() {
	return true;
}

bool j1Entity::Update(float dt)
{
	return true;
}

bool j1Entity::PostUpdate()
{
	return true;
}

bool j1Entity::CleanUp()
{
	return true;
}

bool j1Entity::Save()
{
	return true;
}

bool j1Entity::Load()
{
	return true;
}

void j1Entity::OnCollision(Collider* c1, Collider* c2) {};

const Collider* j1Entity::GetCollider() const
{
	return collider;
}
