#include "test.h"
#include <windows.h>

using namespace std;


void fetchPerformance() {
	RBTree tree;
	Cache cache;

	// containing 100w <key, value>
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

void performance0() {
	RBTree tree;
	Cache cache;

	LARGE_INTEGER nFreq;
	LARGE_INTEGER t1;
	LARGE_INTEGER t2;
	double dt;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);

	for (int i = 0; i < 10000; ++i) {
		if (!tree.add(i, i, cache)) 
			cout << "Error0!" << endl;
		if(!tree.remove(i, cache))
			cout << "Error1!" << endl;
		if(tree.remove(i, cache))
			cout << "Error2!" << endl;
		if(tree.modify(i, i + 1, cache))
			cout << "Error3!" << endl;
		if (!tree.add(i, i + 2, cache))
			cout << "Error4!" << endl;
		if (tree.fetch(i) == NULL) 
			cout << "Error5!" << endl;
	}
	QueryPerformanceCounter(&t2);
	dt = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;

	cout << "fetch time cost: " << dt << "s." << endl;

}



void performance1() {
	RBTree tree;
	Cache cache;

	dataFileName = "viewTest0.txt";
	indexFileName = "indexForviewTest0.txt";

	cout << "with read cache";
	time_t start1000, end1000;
	start1000 = clock();
	for (int i = 0; i < 1000; ++i) {
		for (int j = 0; j < 20; ++j) {
			tree.add(i * 20 + j, i * 20 + j, cache);
			tree.fetch(i * 20 + j);
		}
	}
	end1000 = clock();
	cout << "1000 times cost:" << end1000 - start1000 << endl;

	tree.clear();
	cache.clear();

	time_t start10000, end10000;
	start10000= clock();
	for (int i = 0; i < 10000; ++i) {
		for (int j = 0; j < 20; ++j) {
			tree.add(i * 20 + j, i * 20 + j, cache);
			tree.fetch(i * 20 + j);
		}
	}
	end10000 = clock();
	cout << "10000 times cost:" << end10000 - start10000 << endl;

	tree.clear();
	cache.clear();

	time_t start100000, end100000;
	start100000 = clock();
	for (int i = 0; i < 100000; ++i) {
		for (int j = 0; j < 20; ++j) {
			tree.add(i * 20 + j, i * 20 + j, cache);
			tree.fetch(i * 20 + j);
		}
	}
	end100000= clock();
	cout << "100000 times cost" << end100000 - start100000 << endl;


	tree.clear();
	cache.clear();

	time_t start1000000, end1000000;
	start1000000= clock();
	for (int i = 0; i < 1000000; ++i) {
		for (int j = 0; j < 20; ++j) {
			tree.add(i * 20 + j, i * 20 + j, cache);
			tree.fetch(i * 20 + j);
		}
	}
	end1000000= clock();
	cout << "1000000time cost" << end1000000 - start1000000 << endl;
}