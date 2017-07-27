#include "test.h"
#include <windows.h>
extern string dataFileName;
extern string indexFileName;

void roundTest0() {
	RBTree tree;
	Cache cache;

	dataFileName = "data100w.txt";
	indexFileName = "indexFordata100w.txt";

	LARGE_INTEGER nFreq;
	LARGE_INTEGER start0, start1, start2, end0, end1, end2;

	QueryPerformanceFrequency(&nFreq);

	QueryPerformanceCounter(&start0);
	treeFromData(tree, cache);
	QueryPerformanceCounter(&end0);

	cout << "set tree from data, time cost:" << (end0.QuadPart - start0.QuadPart) / (double)nFreq.QuadPart << "s." << endl;

	QueryPerformanceCounter(&start1);
	setIndexFile(tree);
	QueryPerformanceCounter(&end1);

	cout << "set index from tree, time cost:" << (end1.QuadPart - start1.QuadPart) / (double)nFreq.QuadPart << "s." << endl;

	tree.clear();
	cache.clear();

	QueryPerformanceCounter(&start2);
	treeFromFile(tree, cache);
	QueryPerformanceCounter(&end2);

	cout << "set tree from index file, time cost:" << (end2.QuadPart - start2.QuadPart) / (double)nFreq.QuadPart << "s." << endl;

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