#include "test.h"
#include <time.h>

extern string dataFileName;
extern string indexFileName;

void roundTest0() {
	RBTree tree;
	Cache cache;
	dataFileName = "data100w.txt";
	indexFileName = "indexFordata100w.txt";

	time_t start0, start1, start2, end0, end1, end2;

	start0 = clock();
	treeFromData(tree, cache);
	end0 = clock();

	cout << "set tree from data, time cost:" << end0 - start0 << "ms." << endl;

	start1 = clock();
	setIndexFile(tree);
	end1 = clock();

	cout << "set index from tree, time cost:" << end1 - start1 << "ms." << endl;

	tree.clear();
	cache.clear();

	start2 = clock();
	treeFromFile(tree, cache);
	end2 = clock();

	cout << "set tree from index file, time cost:" << end2 - start2 << "ms." << endl;

}

void roundTest1() {
	fstream dataFile("largeData.txt", ios::in | ios::binary);
	RBTree tree;
	Cache cache;

	treeFromData(tree, cache);

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