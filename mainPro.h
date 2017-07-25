#ifndef MAIN_H
#define MAIN_H


#include "file.h"

#define RETURN 0
#define OPEN_DATA_FILE 1
#define VIEW_NODE 2
#define ADD_NODE 3
#define MODIFY_NODE 4
#define DELETE_NODE 5
#define CLOSE_DATA_FILE 6



using namespace std;

//===============================================================================

// get user choice
void getFlag(int & flag);

// react to different user choice
void react(int & flag, fstream & dataFile, RBTree & tree, Cache & cache);

//=================================================================================

string dataFileName;
string indexFileName;

//====================== react ==================================================

void react(int & flag, fstream & dataFile, RBTree & tree, Cache & cache) {

	getFlag(flag);

	if (flag == RETURN) {
		// make sure the data file is updateed and closed before return;
		closeFile(dataFile, indexFileName, tree, cache);
		return;
	}


	else if (flag == OPEN_DATA_FILE) {
		getFile(dataFile, tree, cache);
		dataFile.close();
		tree.printSingle(tree.getRoot());
		cout << "Total nodes number: " << tree.totalNode() << endl;
	}
		

	else if (flag == VIEW_NODE)
		viewNode(dataFile, tree, cache);

	else if (flag == ADD_NODE)
		addNode(dataFile, tree, cache);

	else if (flag == MODIFY_NODE)
		modifyNode(dataFile, tree, cache);

	else if (flag == DELETE_NODE)
		deleteNode(dataFile, tree, cache);

	else if (flag == CLOSE_DATA_FILE)
		closeFile(dataFile, indexFileName, tree, cache);

	else {
		cout << "Error: no such demmend!" << endl;
		getFlag(flag);
	}

	return;
}

void getFlag(int & flag) {
	cout << "Please chose what to do?" << endl;

	cout << "----0---- quit" << endl;
	cout << "----1---- open data file" << endl;
	cout << "----2---- view data (from it's key)" << endl;
	cout << "----3---- add new node" << endl;
	cout << "----4---- modify node value" << endl;
	cout << "----5---- delete node" << endl;
	cout << "----6---- close data file" << endl;
	cout << endl;

	cin >> flag;
}


#endif
