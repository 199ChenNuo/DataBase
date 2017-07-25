#include "test.h"

// add 1,000,000 node into an empty tree ( sort, the wrost condition)
void fileAddNode0() {
	RBTree tree;
	Cache cache;

	for (int i = 0; i < 1000000; ++i) {
		tree.add(i, i, cache);
	}
}

// add 100 new node into a tree( already contains 1,000,000 nodes)
void fileAddNode1() {
	RBTree tree;
	Cache cache;
	fstream dataFile;

	dataFile.open("largeData.txt", ios::in | ios::binary);

	treeFromData(tree, dataFile, cache);

	cout << "total node:" << tree.getLastPos();

	// delete
	int count = 0;

	Node* cur = tree.getRoot();
	while (cur->pos != -1) {
		count++;
		tree.remove(cur->key, cache);
		cur = tree.getRoot();
	}
}

// fetch 100 node in a tree
void fileFetchNode() {
	fstream dataFile("smallDataFile0.txt", ios::in | ios::binary);
	RBTree tree;
	Cache cache;

	treeFromData(tree, dataFile, cache);

	for (int i = 0; i < 100; ++i) {
		tree.fetch(i);
	}
}

// modify 100 node in a tree( contains 1,000,000 nodes)
void fileModifyNode() {
	fstream dataFile;
	RBTree tree;
	Cache cache;

	dataFile.open("largeDataBase.txt", ios::in | ios::binary);

	treeFromData(tree, dataFile, cache);

	int count = 0;
	for (int i = 0; count < 100; ++i) {
		if (tree.modify(i, i, cache)) {
			count++;
		}
	}
}

// remove root from a tree until it's empty
void fileDeleteNode() {
	fstream dataFile("smallDataFile0.txt", ios::in | ios::binary);
	RBTree tree; 
	Cache cache;

	treeFromData(tree, dataFile, cache);

	Node* curNode = tree.getRoot();
	while (curNode != NULL) {
		tree.remove(curNode->key, cache);
		curNode = tree.getRoot();
	}
}


void fileViewNode0() {
	RBTree tree;
	Cache cache;
	fstream dataFile("smallDataBase0.txt", ios::in | ios::binary);
	
	treeFromData(tree, dataFile, cache);

	Node* curNode = tree.getRoot();

	while (curNode != NULL) {
		tree.printSingle(curNode);
		tree.remove(curNode->key, cache);
		curNode = tree.getRoot();
	}
}

// print 100 node
void fileViewNode1() {
	RBTree tree;
	Cache cache;
	fstream dataFile("smallDataBase0.txt", ios::in | ios::binary);

	treeFromData(tree, dataFile, cache);

	int count = 0;
	for (int i = 0; count < 100; ++i) {
		Node* curNode = tree.fetch(i);

		if (curNode != NULL) {
			tree.printSingle(curNode);
			count++;
		}
	}
}