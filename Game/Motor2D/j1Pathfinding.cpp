#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1PathFinding.h"
#include "Brofiler.h"

j1PathFinding::j1PathFinding() : j1Module(), map(NULL), lastPath(DEFAULT_PATH_LENGTH), width(0), height(0) {
	name.create("pathfinding");
}

j1PathFinding::~j1PathFinding() {
	RELEASE_ARRAY(map);
}

bool j1PathFinding::CleanUp() {
	lastPath.Clear();
	RELEASE_ARRAY(map);
	return true;
}

void j1PathFinding::SetMap(uint w, uint h, uchar* data) {
	width = w;
	height = h;
	RELEASE_ARRAY(map);
	map = new uchar[w * height];
	memcpy(map, data, w * height);
}

bool j1PathFinding::CheckBoundaries(iPoint& p) {
	return (p.x >= 0 && p.x <= width && p.y >= 0 && p.y <= height);
}

bool j1PathFinding::IsWalkable(iPoint& p) {
	uchar t = GetTileAt(p);
	return true;
}

uchar j1PathFinding::GetTileAt(iPoint& p) {
	if(CheckBoundaries(p)) return map[(p.y * width) + p.x];
	return INVALID_WALK_CODE;
}

p2DynArray<iPoint>* j1PathFinding::GetLastPath() {
	return &lastPath;
}

p2List_item<PathNode>* PathList::Find(iPoint& point) {
	p2List_item<PathNode>* item = node_list.start;
	while(item)	{
		if(item->data.pos == point)
			return item;
		item = item->next;
	}
	return NULL;
}

p2List_item<PathNode>* PathList::GetNodeLowestScore() {
	p2List_item<PathNode>* ret = NULL;
	int min = 1000000;

	p2List_item<PathNode>* item = node_list.end;
	while(item)	{
		if(item->data.Score() < min) {
			min = item->data.Score();
			ret = item;
		}
		item = item->prev;
	}
	return ret;
}

PathNode::PathNode() : g(-1), h(-1), pos(-1, -1), parent(NULL) {}

PathNode::PathNode(int g, int h, iPoint& p, PathNode* parent) : g(g), h(h), pos(p), parent(parent) {}

PathNode::PathNode(PathNode& node) : g(node.g), h(node.h), pos(node.pos), parent(node.parent) {}

uint PathNode::FindWalkableAdjacents(PathList& list_to_fill) {
	iPoint cell;
	uint before = list_to_fill.node_list.count();
	// 8
	cell.create(pos.x, pos.y + 1);
	if(App->pathfinding->IsWalkable(cell))
		list_to_fill.node_list.add(PathNode(-1, -1, cell, this));
	// 2
	cell.create(pos.x, pos.y - 1);
	if(App->pathfinding->IsWalkable(cell))
		list_to_fill.node_list.add(PathNode(-1, -1, cell, this));
	// 6
	cell.create(pos.x + 1, pos.y);
	if(App->pathfinding->IsWalkable(cell))
		list_to_fill.node_list.add(PathNode(-1, -1, cell, this));
	// 4
	cell.create(pos.x - 1, pos.y);
	if(App->pathfinding->IsWalkable(cell))
		list_to_fill.node_list.add(PathNode(-1, -1, cell, this));

	return list_to_fill.node_list.count();
}

int PathNode::Score() {
	return g + h;
}

int PathNode::CalculateF(iPoint& destination) {
	g = parent->g + 1;
	h = pos.DistanceTo(destination);

	return g + h;
}

p2DynArray<iPoint>* j1PathFinding::CreatePath(iPoint& origin, iPoint& destination) {
	BROFILER_CATEGORY("PathFinding_CreatePath", Profiler::Color::Green)

	lastPath.Clear();

	if (IsWalkable(origin) && IsWalkable(destination)) {
		PathList open, close;
		PathNode origin(0, origin.DistanceNoSqrt(destination), origin, nullptr);
		open.node_list.add(origin);

		while (open.node_list.count() > 0) 	{
			close.node_list.add(open.GetNodeLowestScore()->data);
			open.node_list.del(open.GetNodeLowestScore());

			if (close.node_list.end->data.pos != destination) {

				PathList adjacent;

				close.node_list.end->data.FindWalkableAdjacents(adjacent);

				for (p2List_item<PathNode>* iterator = adjacent.node_list.start; iterator != nullptr; iterator = iterator->next) {
					if (close.Find(iterator->data.pos))
						continue;

					else if (open.Find(iterator->data.pos))	{
						PathNode tmp = open.Find(iterator->data.pos)->data;
						iterator->data.CalculateF(destination);

						if (tmp.g > iterator->data.g) {
							tmp.parent = iterator->data.parent;
						}
					}

					else {
						iterator->data.CalculateF(destination);
						open.node_list.add(iterator->data);
					}
				}
				adjacent.node_list.clear();
			}

			else {
				for (p2List_item<PathNode>* iterator = close.node_list.end; iterator->data.parent != nullptr; iterator = close.Find(iterator->data.parent->pos)) {
					lastPath.PushBack(iterator->data.pos);

					if (iterator->data.parent == nullptr)
						lastPath.PushBack(close.node_list.start->data.pos);
				}

				lastPath.Flip();

				return &lastPath;
			}
		}
	}

	else return nullptr;
}

MOVE_TO j1PathFinding::WillMoveTo(p2DynArray<iPoint>& path) {
	
	if (path.Count() >= 2) {
		iPoint tile = path[0];
		iPoint next_tile = path[1];
		int x_difference = next_tile.x - tile.x;
		int y_difference = next_tile.y - tile.y;
		if (x_difference == -1 && y_difference == 1) return PATH_1;
		else if (y_difference == 1)	return PATH_2;
		else if (x_difference == 1 && y_difference == 1) return PATH_3;
		else if (x_difference == -1) return PATH_4;
		else if (x_difference == 1) return PATH_6;
		else if (x_difference == -1 && y_difference == -1) return PATH_7;
		else if (y_difference == -1) return PATH_8;
		else if (x_difference == 1 && y_difference == -1) return PATH_9;
	}
	return PATH_5;
}

MOVE_TO j1PathFinding::WillMoveTo_Land(p2DynArray<iPoint>& path) {
	if (path.Count() >= 2) {
		iPoint tile = path[0];
		iPoint next_tile = path[1];

		int x_difference = next_tile.x - tile.x;
		int y_difference = next_tile.y - tile.y;
		if (y_difference == 1)	return PATH_2;
		else if (x_difference == -1) return PATH_4;
		else if (x_difference == 1) return PATH_6;
		else if (y_difference == -1) return PATH_8;
	}
	return PATH_5;
}
