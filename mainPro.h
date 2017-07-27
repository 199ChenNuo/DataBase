#ifndef MAIN_H
#define MAIN_H


#include "file.h"

#define RETURN 0
#define OPEN_DATA_FILE 1
#define VIEW_NODE 2
#define ADD_NODE 3
#define MODIFY_NODE 4
#define DELETE_NODE 5



using namespace std;

//=================================================================================

string dataFileName = "";
string indexFileName = "";

//=================================================================================

// get user choice
void getFlag(int & flag);

// react to different user choice
void react(int & flag, RBTree & tree, Cache & cache);

//=============================================
//---------------- react ----------------------

void react(int & flag, RBTree & tree, Cache & cache) {

	getFlag(flag);

	if (flag == RETURN) {
		// make sure the data file is updateed and closed before return;
		updateFile(tree, cache);
		return;
	}

	else if (flag == OPEN_DATA_FILE) {
		if (haveOpenedFile()) {
			updateFile(tree, cache);
		}
		tree.clear();
		cache.clear();
		getFile(tree, cache);
	}

	else if (flag == VIEW_NODE)
		viewNode(tree, cache);

	else if (flag == ADD_NODE)
		addNode(tree, cache);

	else if (flag == MODIFY_NODE)
		modifyNode(tree, cache);

	else if (flag == DELETE_NODE)
		deleteNode(tree, cache);

	else {
		cout << "Error: no such demmend!" << endl;
		getFlag(flag);
	}

	return;
}


//====================================================
//---------- getFlag ---------------------------------
void getFlag(int & flag) {
	cout << "===================================" << endl;
	cout << "Please chose what to do?" << endl;

	cout << "----0---- quit" << endl;
	cout << "----1---- open data file" << endl;
	cout << "----2---- view data (from it's key)" << endl;
	cout << "----3---- add new node" << endl;
	cout << "----4---- modify node value" << endl;
	cout << "----5---- delete node" << endl;
	cout << endl;

	string strFlag = "";
	getline(cin, strFlag);

	if (strFlag == "quit") {
		flag = 0;
	}

	if (isNum(strFlag)) {
		stringstream ss;
		ss << strFlag;
		ss >> flag;
	}
	else {
		cout << "Please enter again!" << endl;
		cout << "\"quit\" to quit." << endl;
		getFlag(flag);
	}

}



#endif
