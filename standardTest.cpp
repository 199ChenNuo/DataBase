
#include "mainPro.h"
#include "test.h"

#include <string>



//==============================================================================

// use global so the interface are clear
// both open and close file function can use names
extern string dataFileName;
extern string indexFileName;


int standardTest()
try {
	fstream dataFile;
	RBTree tree;
	Cache cache;

	// initialize, suppose to open a data file

	int flag = OPEN_DATA_FILE;
	while (flag != RETURN) {
		react(flag, dataFile, tree, cache);
	}

	return 0;
}
catch (exception& e) {
	cout << e.what() << endl;
	return 1;
}
catch (...) {
	cout << "Unknow exception!" << endl;
	return 2;
}

