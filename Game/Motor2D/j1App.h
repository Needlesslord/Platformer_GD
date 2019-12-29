#ifndef __j1APP_H__
#define __j1APP_H__
#include "p2List.h"
#include "j1Module.h"
#include "PugiXml\src\pugixml.hpp"
#include "j1PerfTimer.h"
#include "j1Timer.h"

// Modules
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1Audio;
class j1Scene;
class j1SceneIntro;
class j1Collisions;
class j1Player;
class j1Map;
class j1EntityManager;
class j1PathFinding;
class j1Particles;
class j1Fonts;
class j1UI;

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

	char* currentScene;

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
	j1SceneIntro*		scene_intro;
	j1Map*				map;
	j1Collisions*		collisions;
	j1Player*			player;
	j1EntityManager*	entity_manager;
	j1PathFinding*		pathfinding;
	j1Particles*		particles;
	j1Fonts*			fonts;
	j1UI*				UI;
	bool SaveRequest = false;
	bool LoadRequest = false;

private:
	p2List<j1Module*>	modules;

	//WINDOW TITTLE REQUIREMENTS:
	uint				FPS;
	float				average_FPS;
	uint				MS_of_the_last_frame;
	char*				cap;
	char*				vsync;

	bool				FPS_cap;
	uint				frameRateCap = 0;
	uint				frames = 0;
	j1Timer				startupTimer;
	j1Timer				frameTimer;
	j1Timer				FPS_Timer;
	uint				FPS_count = 0;
	uint				last_FPS_count = 0;
	float dt = 0;

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