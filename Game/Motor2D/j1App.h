#ifndef __j1APP_H__
#define __j1APP_H__
#include "p2List.h"
#include "j1Module.h"
#include "PugiXml\src\pugixml.hpp"

// Modules
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1Audio;
class j1Scene;
class j1SceneIntro;
class j1Colliders;
class j1Player;
class j1SceneLevel1;
class j1Map1;

//Missing other classes

class j1App {
public:
	// Constructor
	j1App(int argc, char* args[]);
	// Destructor
	virtual ~j1App();
	// Called before render is available
	bool Awake();
	// Called before the first frame
	bool Start();
	// Called each loop iteration
	bool Update();
	// Called before quitting
	bool CleanUp();
	// Add a new module to handle
	void AddModule(j1Module* module);
	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	int currentScene;

private:
	// Load config file
	bool LoadConfig();
	// Call modules before each loop iteration
	void PrepareUpdate();
	// Call modules before each loop iteration
	void FinishUpdate();
	// Call modules before each loop iteration
	bool PreUpdate();
	// Call modules on each loop iteration
	bool DoUpdate();
	// Call modules after each loop iteration
	bool PostUpdate();
	// TODO 2: Create the functions for Loading / Saving the game state (leave those empty for now)
	bool Save();
	bool Load();

public:
	// Modules
	j1Window*			win;
	j1Input*			input;
	j1Render*			render;
	j1Textures*			tex;
	j1Audio*			audio;
	j1Scene*			scene;
	j1SceneIntro*		sceneintro;
	j1SceneLevel1*		scenelevel1;
	j1Map*				map;
	//j1Collisions*		collisions;
	//j1Animation*		animation;
	//j1FadeToBlack*		fade;
	//j1SceneLevel1*			l1;
	//j1SceneLevel2*			l2;
	//j1Particles*		particle;
	j1Player*			player;
	bool SaveRequest = false;
	bool LoadRequest = false;

private:
	p2List<j1Module*>	modules;
	uint				frames;
	float				dt;
	pugi::xml_document	config_file;
	pugi::xml_node		config;
	pugi::xml_node		app_config;
	int					argc;
	char**				args;
	p2SString			title;
	p2SString			organization;
};

extern j1App* App;

#endif