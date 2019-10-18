#ifndef __j1MAP1_H__
#define __j1MAP1_H__
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

struct SDL_Texture;

struct MapProperties {

	struct MapProperty {
		p2SString mapname;
		int value;
	};

	~MapProperties() {
		p2List_item<MapProperty*>* item;
		item = list.start;

		while (item != NULL) {
			RELEASE(item->data);
			item = item->next;
		}

		list.clear();
	}

	int Get(const char* name, int default_value = 0) const;
	p2List<MapProperty*>	list;
};

struct MapLayer {
	p2SString mapname;
	uint width = 0;
	uint height = 0;
	uint* data = nullptr;
	uint size = 0;
	MapProperties	properties;
	float parallaxSpeed;
	~MapLayer();

	inline uint Get(uint x, uint y) const {
		return x + y * width;
	}

	inline uint GetID(uint x, uint y) const {
		return data[(y * width) + x];
	}
};

struct ObjectsData {
	uint16_t	name;
	int			x;
	int			y;
	uint		width;
	uint		height;

};

struct ObjectsGroup {
	p2SString				name;
	p2List<ObjectsData*>	objects;
	~ObjectsGroup();
};

struct TileSet {
	SDL_Rect GetTileRect(int id) const;
	p2SString			name;
	int					firstgid;
	int					margin;
	int					spacing;
	int					tile_width;
	int					tile_height;
	SDL_Texture*		texture;
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

enum MapLevels {
	MAP_LEVEL1,
	MAP_LEVEL2,
	MAP_UNKNOW = 0			//Intro
};

struct MapData {
	int						width;
	int						height;
	int						tile_width;
	int						tile_height;
	SDL_Color				background_color;
	MapTypes				type;
	p2List<TileSet*>		tilesets;
	p2List<MapLayer*>		layers;
	p2List<ObjectsGroup*>	objLayers;
	p2SString				musicFile;
};

class j1Map1 : public j1Module {
	//-------------Functions-----------------
public:
	j1Map1();
	// Destructor
	virtual ~j1Map1();
	// Called before render is available
	bool Awake(pugi::xml_node& conf);
	// Called each loop iteration
	void Draw();
	void DebugDraw();
	// Called before quitting
	bool CleanUp();
	// Load new map
	bool Load_map(const char* path);
	//Method that translates x,y coordinates from map positions to world positions
	iPoint MapToWorld(int x, int y) const;
	iPoint j1Map1::WorldToMap(int x, int y) const;
	//Unloads the current map and loads the map specified with the corresponding music. 
	bool SwitchMaps(p2SString* new_map);
	bool j1Map1::CreateWalkabilityMap(int& width, int& height, uchar** buffer) const;

private:
	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadObjectLayers(pugi::xml_node& node, ObjectsGroup* group);
	bool LoadProperties(pugi::xml_node& node, MapProperties& properties);
	TileSet* GetTilesetFromTileId(int id) const;

	//-------------Variables-----------------
public:
	MapData				data;
	bool				debug = false;

private:
	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;

};

#endif // __j1MAP1_H__