#if 0;

#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

// TODO 1: Create a struct for the map layer
// ----------------------------------------------------

// TODO 6: Short function to get the value of x,y


struct MapLayer
{
	p2SString			name;
	uint				width;
	uint				height;
	uint* data;
	inline uint Get(int x, int y) const
	{
		return x + y * width;
	}
};


// ----------------------------------------------------
struct TileSet
{
	// TODO 7: Create a method that receives a tile id and returns it's Rect
	SDL_Rect* Tilerect = new SDL_Rect;
	SDL_Rect* TileRect(uint tile_id) {
		SDL_Rect* ret = Tilerect;
		int x = ((tile_id - firstgid) % num_tiles_width);
		int y = ((tile_id - firstgid) / num_tiles_width);

		ret->x = x * tile_width + margin + spacing * x;
		ret->y = y * tile_height + margin + spacing * y;
		ret->w = tile_width;
		ret->h = tile_height;

		return ret;
	}

	inline p2Point<uint> GetPos(uint x, uint y) {
		p2Point<uint> ret;
		ret.x = x * tile_width;
		ret.y = y * tile_height;

		return ret;
	}

	p2SString			name;
	int					firstgid;
	int					margin;
	int					spacing;
	int					tile_width;
	int					tile_height;
	SDL_Texture* texture;
	int					tex_width;
	int					tex_height;
	int					num_tiles_width;
	int					num_tiles_height;
	int					offset_x;
	int					offset_y;
};

enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};
// ----------------------------------------------------
struct MapData
{
	int					width;
	int					height;
	int					tile_width;
	int					tile_height;
	SDL_Color			background_color;
	MapTypes			type;
	p2List<TileSet*>	tilesets;
	p2List<MapLayer*>	layers;


	// TODO 2: Add a list/array of layers to the map!
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

	// TODO 8: Create a method that translates x,y coordinates from map positions to world positions


private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	// TODO 3: Create a method that loads a single layer
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);

public:

	MapData data;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__


/////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////



#ifndef __j1MAP_H__
#define __j1MAP_H__
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "SDL/include/SDL.h"
#include "PugiXml/src/pugixml.hpp"


// TODO 1: Create a struct for the map layer
struct MapLayer {
	p2SString	name = " ";
	uint		width = 0u;
	uint		height = 0u;
	uint* data = 0u;
	MapLayer() : data(NULL) {}

	~MapLayer() {
		RELEASE(data);
	}

	// TODO 6 (old): Short function to get the value of x,y
	inline uint Get(int x, int y) const {
		return data[x + y * width];
	}
};

// ----------------------------------------------------
struct TileSet {
	// TODO 7: Create a method that receives a tile id and returns it's Rect
	SDL_Rect* Tilerect = new SDL_Rect;

	SDL_Rect* TileRect(uint tile_id) {
		SDL_Rect* ret = Tilerect;
		int x = ((tile_id - firstgid) % num_tiles_width);
		int y = ((tile_id - firstgid) / num_tiles_width);
		ret->x = x * tile_width + margin + spacing * x;
		ret->y = y * tile_height + margin + spacing * y;
		ret->w = tile_width;
		ret->h = tile_height;

		return ret;
	}

	inline p2Point<uint> GetPos(uint x, uint y) {
		p2Point<uint> ret;
		ret.x = x * tile_width;
		ret.y = y * tile_height;

		return ret;
	}

	SDL_Rect GetTileRect(uint id) const;
	p2SString			name;
	int					firstgid;
	int					margin;
	int					spacing;
	int					tile_width;
	int					tile_height;
	SDL_Texture* texture;
	int					tex_width;
	int					tex_height;
	int					num_tiles_width;
	int					num_tiles_height;
	int					offset_x;
	int					offset_y;
};

enum MapTypes {
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};

// ----------------------------------------------------
struct MapData {
	int					width;
	int					height;
	int					tile_width;
	int					tile_height;
	SDL_Color			background_color;
	MapTypes			type;
	p2List<TileSet*>	tilesets;
	// TODO 2: Add a list/array of layers to the map!
	p2List<MapLayer*>	layers;
};

// ----------------------------------------------------
class j1Map : public j1Module {
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
	// TODO 8: Create a method that translates x,y coordinates from map positions to world positions
	// Coordinate translation methods
	iPoint MapToWorld(int x, int y) const;
	iPoint WorldToMap(int x, int y) const;

	//xxx
	//iPoint MapToWorld(int x, int y) const;
	//iPoint WorldToMap(int x, int y) const;

private:
	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	// TODO 3: Create a method that loads a single layer
	// bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);

public:
	MapData data;

private:
	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__


//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

#if 0;

#ifndef __j1MAP_H__
#define __j1MAP_H__
#include "PugiXml/src/pugixml.hpp"
#include "SDL/include/SDL.h"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"


struct MapLayer {

	p2SString	name = " ";
	uint		width = 0u;
	uint		height = 0u;
	uint* data = 0u;
	MapLayer() : data(NULL) {}

	~MapLayer() {
		RELEASE(data);
	}

	inline uint Get(int x, int y) const {
		{
			return x + y * width;
		}
	};


	// ----------------------------------------------------
	struct TileSet
	{
		// TODO 7: Create a method that receives a tile id and returns it's Rect
		SDL_Rect* Tilerect = new SDL_Rect;
		SDL_Rect* TileRect(uint tile_id) {
			SDL_Rect* ret = Tilerect;
			int x = ((tile_id - firstgid) % num_tiles_width);
			int y = ((tile_id - firstgid) / num_tiles_width);

			ret->x = x * tile_width + margin + spacing * x;
			ret->y = y * tile_height + margin + spacing * y;
			ret->w = tile_width;
			ret->h = tile_height;

			return ret;
		}

		inline p2Point<uint> GetPos(uint x, uint y) {
			p2Point<uint> ret;
			ret.x = x * tile_width;
			ret.y = y * tile_height;

			return ret;
		}

		p2SString			name;
		int					firstgid;
		int					margin;
		int					spacing;
		int					tile_width;
		int					tile_height;
		SDL_Texture* texture;
		int					tex_width;
		int					tex_height;
		int					num_tiles_width;
		int					num_tiles_height;
		int					offset_x;
		int					offset_y;
	};

	enum MapTypes
	{
		MAPTYPE_UNKNOWN = 0,
		MAPTYPE_ORTHOGONAL,
		MAPTYPE_ISOMETRIC,
		MAPTYPE_STAGGERED
	};
	// ----------------------------------------------------
	struct MapData
	{
		int					width;
		int					height;
		int					tile_width;
		int					tile_height;
		SDL_Color			background_color;
		MapTypes			type;
		p2List<TileSet*>	tilesets;
		p2List<MapLayer*>	layers;


		// TODO 2: Add a list/array of layers to the map!
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

		// TODO 8: Create a method that translates x,y coordinates from map positions to world positions


	private:

		bool LoadMap();
		bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
		bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
		// TODO 3: Create a method that loads a single layer
		bool LoadLayer(pugi::xml_node& node, MapLayer* layer);

	public:

		MapData data;

	private:

		pugi::xml_document	map_file;
		p2SString			folder;
		bool				map_loaded;
	};

#endif // __j1MAP_H__


#endif;



/////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////



#endif;