#include "test.h"
#include <windows.h>

// remove 1,000,000 nodes from the tree(every time is root, the worst condition)
// notice that the function used here--tree.remove(int key, Cache & cache) is not accessible
// so the file won't be updated( the file will be updated in the add function that can be used by users)
void fileAddNode() {
	RBTree tree;
	Cache cache;
	dataFileName = "largeData.txt";

	treeFromData(tree, cache);

	Node* cur = tree.getRoot();
	while (cur->pos != -1) {
		tree.remove(cur->key, cache);
		cur = tree.getRoot();
	}
}

// fetch 100 node in a tree
void fileFetchNode() {
	RBTree tree;
	Cache cache;
	dataFileName = "small.txt";

	treeFromData(tree, cache);

	for (int i = 0; i < 100; ++i) {
		tree.fetch(i);
	}
}

// modify 100 node in a tree( contains 1,000,000 nodes)
void fileModifyNode() {
	RBTree tree;
	Cache cache;
	dataFileName = "largeData.txt";

	treeFromData(tree, cache);

	int count = 0;
	for (int i = 0; count < 100; ++i) {
		if (tree.modify(i, i, cache)) {
			count++;
		}
	}
}

// remove root from a tree until it's empty
void fileDeleteNode() {
	RBTree tree; 
	Cache cache;
	dataFileName = "small.txt";

	treeFromData(tree, cache);

	Node* curNode = tree.getRoot();
	while (curNode != NULL) {
		tree.remove(curNode->key, cache);
		curNode = tree.getRoot();
	}
}



// print 100 node
void fileViewNode() {
	RBTree tree;
	Cache cache;
	dataFileName = "largeData.txt";

	treeFromData(tree, cache);

	int count = 0;
	for (int i = 0; count < 100; ++i) {
		Node* curNode = tree.fetch(i);

		if (curNode != NULL) {
			tree.printSingle(curNode, cache);
			count++;
		}
	}
}