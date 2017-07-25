#ifndef CACHE_H
#define CACHE_H


#include <iostream>
#include <vector>
#include <map>
#include <queue>

#include "Node.h"

using namespace std;

struct Cache{
	Cache();

	priority_queue<int>deletePos;

	map<Node*, int>modifyNode;

	map<Node*, int>addNode;
};

#endif
