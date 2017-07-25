#include "test.h"
#include <time.h>

void roundTest0() {
	fstream dataFile("largeData.txt", ios::in | ios::binary);
	RBTree tree;
	Cache cache;

	treeFromData(tree, dataFile, cache);

	int count = 0;
	while (count++ < 1000000) {
		if (count % 37 == 0) {
			tree.remove(count, cache);
		}
		if (count % 11 == 0) {
			tree.add(count, count, cache);
			tree.fetch(count);
		}
		if (count % 17 == 0) {
			tree.modify(count, count, cache);
		}
	}
}

void roundTest1() {
	fstream dataFile("largeData.txt", ios::in | ios::binary);
	RBTree tree;
	Cache cache;

	treeFromData(tree, dataFile, cache);

	cout << "total:" << tree.getLastPos() << endl;

	Node* cur = tree.getRoot();
	while (cur != NULL && cur->pos != -1) {
		cout << cur->key << endl;
		cout << "temp total:" << tree.totalNode() << endl;
		cout << "=====================================" << endl;
		tree.remove(cur->key, cache);
		cur = tree.getRoot();
	}
}