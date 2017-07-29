#include "test.h"

#define TIMES 1000000

bool readNode(RBTree & tree, Cache & cache,  Node* & node);

void correctTest() {
	RBTree tree;
	Cache cache;
	// cache won't be cleared, so we can see node in cache

	for (int i = 0; i < TIMES; ++i) {
		tree.add(i, i, cache);
	}


	for (int i = 0; i < TIMES; ++i) {
		tree.modify(i, i + 1, cache);
	}

	map<Node*, int>::iterator it;
	for (it = cache.addNode.begin(); it != cache.addNode.end(); ++it) {
		if (it->first->key != it->second - 1) {
			// avoid promt information cover Error information
			system("pause");
			cout << "Error0!" << endl;
		}
	}

	for (int i = 0; i < TIMES; ++i) {
		tree.remove(i, cache);
	}

	if (cache.addNode.size() != 0) {
		for (it = cache.addNode.begin(); it != cache.addNode.end(); ++it) {
			// in map.erase(it), map may just set node->key to -1
			if (it->first->key != -1) {
				// avoid promt information cover Error information
				system("pause");
				cout << "Error1!" << endl;
			}
		}
	}


	for (int i = TIMES; i < 2 * TIMES; ++i) {
		tree.add(i, i + 1, cache);
	}


	for (it = cache.addNode.begin(); it != cache.addNode.end(); ++it) {
		if (it->first->key != it->second - 1 && it->first->key != -1) {
			// avoid promt information cover Error information
			system("pause");
			cout << "Error2!" << endl;
		}
	}
	
}


bool readNode(RBTree & tree, Cache & cache, Node* & node) {

}

