#include "j1App.h"
#include "j1Entity.h"
#include "j1Render.h"

j1Entity::j1Entity(ENTITY_TYPE type, float x, float y) : type(type), position(x, y) { }

j1Entity::~j1Entity() {}


bool j1Entity::Start() {
	return true;
}

bool j1Entity::CleanUp() {
	return true;
}

bool j1Entity::PreUpdate() {
	return true;
}

bool j1Entity::Update(float dt) {
	return true;
}

bool j1Entity::PostUpdate() {
	return true;
}

bool j1Entity::Save(pugi::xml_node&) {
	return true;
}

bool j1Entity::Load(pugi::xml_node&) {
	return true;
}

void j1Entity::Draw(SDL_Rect r, float x, float y, bool flip) {
	
	if (!flip) App->render->Blit(img, position.x, position.y);
	else App->render->Blit(imgM, position.x, position.y);

}

//float abs(float x) {
//	if (x < 0) return -x;
//	return x;
//}
