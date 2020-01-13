#ifndef __j1PATHFINDING_H__
#define __j1PATHFINDING_H__

#include "j1Module.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "p2List.h"

#define DEFAULT_PATH_LENGTH 50
#define INVALID_WALK_CODE 255

enum MOVE_TO
{
	PATH_5 = -1,

	PATH_1,
	PATH_2,
	PATH_3,
	PATH_4,
	PATH_6,
	PATH_7,
	PATH_8,
	PATH_9
};

class j1PathFinding : public j1Module {
public:
	j1PathFinding();
	~j1PathFinding();
	bool CleanUp();
	void SetMap(uint w, uint h, uchar* data);
	p2DynArray<iPoint>* CreatePath(iPoint& origin, iPoint& destination);
	p2DynArray<iPoint>* GetLastPath();
	bool CheckBoundaries(iPoint& p);
	bool IsWalkable(iPoint& p);
	uchar GetTileAt(iPoint& p);
	MOVE_TO WillMoveTo(p2DynArray<iPoint>& path);
	MOVE_TO WillMoveTo_Land(p2DynArray<iPoint>& path);

private:
	p2DynArray<iPoint>* path = nullptr;
	p2DynArray<iPoint> lastPath;
	uint width;
	uint height;
	uchar* map = nullptr;
};

struct PathList;

struct PathNode {
	PathNode();
	PathNode(int g, int h, iPoint& p, PathNode* parent);
	PathNode(PathNode& node);
	uint FindWalkableAdjacents(PathList& list_to_fill);
	int Score();
	int CalculateF(iPoint& destination);
	int g;
	int h;
	iPoint pos;
	PathNode* parent = nullptr;
};

struct PathList {
	p2List_item<PathNode>* Find(iPoint& point);
	p2List_item<PathNode>* GetNodeLowestScore();
	p2List<PathNode> node_list;
};

#endif // __j1PATHFINDING_H__
