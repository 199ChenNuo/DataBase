#include "test.h"
#include <windows.h>

using namespace std;

void fetchPerformance() {
	RBTree tree;
	Cache cache;

	dataFileName = "data100w.txt";
	indexFileName = "indexFordata100w.txt";

	treeFromFile(tree, cache);

	LARGE_INTEGER nFreq;
	LARGE_INTEGER t1;
	LARGE_INTEGER t2;
	double dt;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	
	int key = -2;
	tree.fetch(key);

	QueryPerformanceCounter(&t2);
	dt =(t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;

	cout << "fetch time cost: " << dt * 1000000 << "us." << endl;

}