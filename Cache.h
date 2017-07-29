#ifndef CACHE_H
#define CACHE_H

#define SIZE_TO_UPDATE 20


#include <iostream>
#include <vector>
#include <map>
#include <queue>

#include "Node.h"

using namespace std;

struct Cache{
	Cache();

	void clear();

	priority_queue<int>deletePos;

	map<Node*, int>modifyNode;

	map<Node*, int>addNode;

	map<Node*, int>viewNode;
};

#endif
