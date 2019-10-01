#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

// TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
// ----------------------------------------------------

struct TileSet {

	char* source;
	unsigned int firstgid = 0;			//1
	char* name = " ";					//Desert
	unsigned int width = 0;				//50			//uint width = 0u;	uint is a number with sign, if we add the las "u", it is unsigned
	unsigned int height = 0;			//15
	unsigned int tilewidth = 0;			//32
	unsigned int tileheight = 0;		//32
	unsigned int margin = 0;			//1

	//Terrain Types enum
	//Tile Types enum

};

// TODO 1: Create a struct needed to hold the information to Map node

enum map_orientation {

	ORTHOGONAL,
	ISOMETRIC,
	ISOMETRIC_SCALATED,
	HEXAGONAL_SCALATED,

	UNKNOWN_ORIENTATION,

};

enum map_renderorder {				//enum class: if you use this, you don't have to worry about namespaces (the same name in different enums collide), but you will need to write name_of_the_enum_class::name

	RIGHT_DOWN,
	RIGHT_UP,
	LEFT_DOWN,
	LEFT_UP,

	UNKNOWN_RENDERORDER,

};

struct Map {

	//float map_version = 1.0f;				//not needed (probably)
	map_orientation orientation = UNKNOWN_ORIENTATION;
	map_renderorder renderorder = UNKNOWN_RENDERORDER;
	unsigned int width = 0;				//50			//uint width = 0u;	uint is a number with sign, if we add the las "u", it is unsigned
	unsigned int height = 0;			//15
	unsigned int tilewidth = 0;			//32
	unsigned int tileheight = 0;		//32
	unsigned int nextobject = 0;		//1

};


// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

private:


public:

	// TODO 1: Add your struct for map info as public for now
	Map map1;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__