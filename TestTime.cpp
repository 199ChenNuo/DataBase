#include "test.h"
#define CACHE_SIZE 20


void setTreeTime() {
	RBTree tree;
	Cache cache;

	dataFileName = "data10w.txt";
	indexFileName = "indexFordata10w.txt";
	cout << "dataFileName: " << dataFileName << endl;

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

void balanceTimeTest() {
	RBTree tree;
	Cache cache;

	// notice that key is in ascending order, the worst condition for Red Black Tree
	for (int i = 0; i < 100000; ++i) {
		int key = rand();
		tree.add(key, key, cache);
	}



	LARGE_INTEGER nFreq;
	LARGE_INTEGER t1;
	LARGE_INTEGER t2;
	double dt;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);

	for (int i = 0; i < 100; ++i) {
		int key = rand();

	}

	QueryPerformanceCounter(&t2);
	dt = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;

	cout << "fetch time cost: " << dt << "s." << endl;
}


void cacheTime() {
	RBTree tree;
	Cache cache;
	vector<int> modifyKey;

	LARGE_INTEGER nFreq;
	LARGE_INTEGER t1;
	LARGE_INTEGER t2;
	double dt;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);

	for (int i = 0; i < 10000; ++i) {
		tree.add(i, i, cache);
	}

	for (int i = 0; i < 100; ++i) {
		int key = rand();
		tree.modify(key, key + 1, cache);
		modifyKey.push_back(key);
		if (cache.modifyNode.size() == CACHE_SIZE)
			cache.clear();
	}

	
	for (int i = 0; i < 100; ++i) {
		int key = modifyKey[i];
		tree.modify(key, key, cache);
		if (cache.modifyNode.size() == CACHE_SIZE)
			cache.clear();
	}

	QueryPerformanceCounter(&t2);
	dt = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;

	cout << "with cache size: " << CACHE_SIZE;
	cout << " time cost: " << dt * 1000000 << "us." << endl;
	
}