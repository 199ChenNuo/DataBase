#include "Cache.h"

using namespace std;

Cache::Cache() {
	priority_queue<int>deletePos;

	map<Node*, int>modifyNode;

	map<Node*, int>addNode;
}
void Cache::clear() {
	while (deletePos.size() != 0) {
		deletePos.pop();
	}

	modifyNode.clear();
	addNode.clear();
}