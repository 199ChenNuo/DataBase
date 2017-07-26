#include "test.h"

using namespace std;

extern string dataFileName;
extern string indexFileName;

void fileTree0(){
	fstream dataFile;
	RBTree tree;
	Cache cache;

	getFile(tree, cache);
}

void indexFile0() {
	fstream dataFile;
	fstream indexFile;
	RBTree tree;
	Cache cache;

	indexFileName = "indexForsmall.txt";
	treeFromFile(tree, cache);
}
