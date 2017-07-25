#include "test.h"

using namespace std;

extern string dataFileName;
extern string indexFileName;

void fileTree0(){
	fstream dataFile;
	RBTree tree;
	Cache cache;

	getFile(dataFile, tree, cache);
}

void indexFile0() {
	fstream dataFile;
	fstream indexFile;
	RBTree tree;
	Cache cache;

	indexFileName = "IndexForDataBase.txt";
	treeFromFile(tree, dataFile, indexFileName, cache);
}
