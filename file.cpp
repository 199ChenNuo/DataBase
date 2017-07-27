#include "file.h"
#include <string>
#include <sstream>

// contain key(int: 4 bytes) and a " "(1 byte)
#define INDEX_BYTE sizeof(int)
// contain value(4 bytes)
#define VALUE_BYTE sizeof(int)
// contain key(int: 4 bytes), " "(1 byte), '\n' (1 byte) and  value(int: 4 bytes)
#define NODE_BYTE  VALUE_BYTE+INDEX_BYTE

#define TO_LEFT false
#define TO_RIGHT true


extern string dataFileName;
extern string indexFileName;

//================================================================================================
//------------------------------------ function about node ----------------------------------------

// ----------- view a node's value ----------------------
void viewNode(RBTree & tree, Cache & cache) {

	if (!haveOpenedFile()) {
		cout << "Error: no data file opened yet!" << endl;
		return;
	}

	string strKey = "";
	stringstream ss;
	int key = 0;
	int value = 0;

	cout << "Viewing..." << endl;
	cout << "Please enter the key." << endl;
	getline(cin, strKey);

	// make sure user's input is int
	while (!isNum(strKey)) {
		getline(cin, strKey);
	}

	ss << strKey;
	ss >> key;

	// first check cache
	map<Node*, int>::iterator it;

	for (it = cache.addNode.begin(); it != cache.addNode.end(); ++it) {
		if (it->first->key == key) {
			value = it->second;
			cout << "Key: " << key << " Value: " << value << endl;
			return;
		}
	}
	for (it = cache.modifyNode.begin(); it != cache.modifyNode.end(); ++it) {
		if (it->first->key == key) {
			value = it->second;
			cout << "Key: " << key << " Value: " << value << endl;
			return;
		}
	}

	// if the node is not in cache, get value from data file
	Node* node = tree.fetch(key);
	if (node != NULL && node->pos != -1) {
		int pos = node->pos;
		value = viewValue(pos);
		cout << "Key: " << key << " Value: " << value << endl;
	}
	else {
		cout << "Error: key does not exits!" << endl;
	}
}

int viewValue(int pos) {
	// get to the pos in the file
	int startByte = pos * 2 * sizeof(int) + sizeof(int);

	int value = 0;

	fstream dataFile;
	dataFile.open(dataFileName, ios::in | ios::binary);
	dataFile.seekg(startByte, ios::beg);
	dataFile.read((char*)&value, sizeof(int));
	dataFile.close();

	return value;
}


//--------------- add a node into the file -------------------
void addNode(RBTree & tree, Cache & cache) {

	if (!haveOpenedFile()) {
		cout << "Error: no data file opened yet!" << endl;
		return;
	}

	stringstream ss1, ss2;
	string strKey = "";
	string strValue = "";
	int key = 0;
	int value = 0;

	cout << "Adding..." << endl;
	cout << "Please enter the key:" << endl;
	getline(cin, strKey);
	while (!isNum(strKey)) {
		getline(cin, strKey);
	}
	cout << "Please enter the value:" << endl;
	getline(cin, strValue);
	while (!isNum(strValue)) {
		getline(cin, strValue);
	}

	ss1 << strKey;
	ss2 << strValue;
	ss1 >> key;
	ss2 >> value;

	if (tree.add(key, value, cache)) {
		cout << "Add succeed!" << endl;
	}

	// only modify data file if the cache size reaches SIZE_TO_UPDATE
	if (cache.addNode.size() == SIZE_TO_UPDATE) {
		updateFile(tree, cache);
	}
}


//------------ modify a node's value -----------------
void modifyNode(RBTree & tree, Cache & cache) {

	if (!haveOpenedFile()){
		cout << "Error: no data file opened yet!" << endl;
		return;
	}

	stringstream ss1, ss2;
	string strKey = "";
	string strValue = "";
	int key = 0;
	int value = 0;

	cout << "Modifying..." << endl;
	cout << "Please enter the key:" << endl;
	getline(cin, strKey);
	while (!isNum(strKey)) {
		getline(cin, strKey);
	}
	cout << "Please enter the new value:" << endl;
	getline(cin, strValue);
	while (!isNum(strKey)) {
		getline(cin, strValue);
	}

	ss1 << strKey;
	ss2 << strValue;
	ss1 >> key;
	ss2 >> value;

	tree.modify(key, value, cache);

	if (cache.modifyNode.size() == SIZE_TO_UPDATE) {
		updateFile(tree, cache);
	}
}


//--------------- delete a node ---------------------------
void deleteNode(RBTree & tree, Cache & cache) {

	if (!haveOpenedFile()) {
		cout << "Error: no data file opened yet!" << endl;
		return;
	}
	

	stringstream ss;
	string strKey = "";
	int key = 0;

	cout << "Deleting..." << endl;
	cout << "Please enter the key:" << endl;
	getline(cin, strKey);
	while (!isNum(strKey)) {
		getline(cin, strKey);
	}
	ss << strKey;
	ss >> key;

	// cache is updated in tree.remove(int key, Cache& cache)
	tree.remove(key, cache);

	if (cache.deletePos.size() == SIZE_TO_UPDATE) {
		updateFile(tree, cache);
	}
}

//------------------------------------ end --------------------------------------
//================================================================================


//===============================================================================
//----------------- function about file -----------------------------------------

//===========================================
//------------- getFile -------------------
void getFile(RBTree & tree, Cache & cache) {
	getFileName();
	fstream dataFile;
	dataFile.open(dataFileName, ios::in | ios::binary);

	while (!dataFile) {
		cout << "open " << dataFileName << " failed." << endl;
		getFileName();
		if (dataFileName == "quit")
			return;
		dataFile.open(dataFileName, ios::in | ios::binary);
	}
	dataFile.close();

	indexFileName = "indexFor" + dataFileName;

	treeFromFile(tree, cache);
}

//===========================================
//------------- getFileName -------------------
void getFileName() {
	cout << "Please enter the and name of data file" << endl;
	cout << "(quit) to quit" << endl;
	getline(cin, dataFileName);
}

//===========================================
//------------- updateFile -------------------
void updateFile(RBTree & tree, Cache & cache) {
	int modifySize = cache.modifyNode.size();
	int addSize = cache.addNode.size();
	int deleteSize = cache.deletePos.size();

	if (modifySize || addSize || deleteSize) {
		cout << "Updating the file..." << endl;
		map<Node*, int>::iterator it;
		for (it = cache.addNode.begin(); it != cache.addNode.end(); ++it) {
			int key = it->first->key;
			int pos = it->first->pos;
			int value = it->second;
			cout << "Add data in data file, key: " << key << " pos: " << pos << " value: " << value << endl;
			fileAddNode(pos, key, value);
		}
		for (it = cache.modifyNode.begin(); it != cache.modifyNode.end(); ++it) {
			int key = it->first->key;
			int pos = it->first->pos;
			int value = it->second;
			cout << "Modify data in data file, key: " << key << " pos: " << pos << " value: " << value << endl;
			fileModifyNode(pos, value);
		}
		for (int i = 0; i < 0; ++i) {
			cout << "Delete value at pos:" << cache.deletePos.top() << endl;
			cache.deletePos.pop();
		}
		cache.modifyNode.clear();
		cache.addNode.clear();
	}
	setIndexFile(tree);
}

void fileModifyNode(int pos, int value) {
	
	fstream dataFile(dataFileName, ios::out | ios::binary);
	if (!dataFile) {
		cout << "open " << dataFileName << " fail." << endl;
	}
	int nodePos = (pos * 2 + 1) * sizeof(int);
	dataFile.seekg(nodePos, ios::beg);

	dataFile.write((char*)& value, sizeof(int));

	dataFile.close();
}

void fileAddNode(int pos, int key, int value) {

	fstream dataFile(dataFileName, ios::out | ios::binary);
	int nodePos = (pos * 2) * sizeof(int) ;
	dataFile.seekg(nodePos, ios::beg);

	dataFile.write((char*)& key, sizeof(int));
	dataFile.write((char*)& value, sizeof(int));
	dataFile.close();
}


//-------------------------------------------- end --------------------------------------------
//=============================================================================================

//=============================================================================================
//------------------ function for tree --------------------------------------------------------

void treeFromFile(RBTree & tree, Cache & cache) {
	fstream indexFile;
	indexFile.open(indexFileName, ios::in | ios::binary);

	if (!indexFile) {
		// there is no index file, set tree from raw data
		treeFromData(tree, cache);
		return;
	}

	// set tree from index file
	indexFile.seekg(0, ios::end);
	int indexLen = indexFile.tellg();
	indexFile.seekg(0, ios::beg);

	// the current position of file pointer
	int indexPos = 0;

	while (indexPos != indexLen) {
		int nodeInforLen = 0;
		vector<int> nodePos;
		int key = -2;
		int pos = -2;
		int color = -1;

		// get the length of the information of the node
		indexFile.read((char*)& nodeInforLen, sizeof(int));

		int nodePosLen = nodeInforLen - 3 * sizeof(int);

		for (int i = 0; i < nodePosLen/4; ++i) {
			int temp = 0;
			indexFile.read((char*)& temp, sizeof(int));
			nodePos.push_back(temp);
		}
		
		indexFile.read((char*)& key, sizeof(int));
		indexFile.read((char*)& pos, sizeof(int));
		indexFile.read((char*)& color, sizeof(int));

		indexAddNode(tree, nodePos, key, pos, color);

		indexPos = indexFile.tellg();
	}
	indexFile.close();
}

// add nodes into tree from index, don't need to balance the tree
void indexAddNode(RBTree & tree, vector<int>& nodePos, int key, int pos, int color) {
	Node* cur = tree.getRoot();

	// if the tree is empty
	if (cur == NULL || cur->pos == -1) {
		Node* root = new Node(key, pos);
		tree.setRoot(root);
		tree.setLastPos(1);
		return;
	}

	int posSize = nodePos.size();

	for (int i = 0; i < posSize; ++i) {
		if (nodePos[i] == LEFT) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}

	cur->key = key;
	cur->pos = pos;
	cur->color = color;
	cur->left = new Node;
	cur->right = new Node;
	cur->left->father = cur->right->father = cur;

	// update tree's lastPos
	// so that when add node it won't make mistake
	int lastPos = tree.getLastPos();
	tree.setLastPos(lastPos + 1);
}



// set index file
// nodes are managed in level-order
void setIndexFile(RBTree & tree) {
	ofstream indexFile(indexFileName, ios::out | ios::binary);

	queue<Node*> nodeWindow;
	queue<vector<int>> posWindow;

	Node* root = tree.getRoot();

	// if the tree is empty
	if (root == NULL) {
		indexFile.close();
		return;
	}

	// initialize two windows
	nodeWindow.push(root);
	vector<int> rootPos;
	posWindow.push(rootPos);

	while (nodeWindow.size() != 0) {
		Node* topNode = nodeWindow.front();
		nodeWindow.pop();

		vector<int> topPos = posWindow.front();
		posWindow.pop();

		// the length of the vector(is also the level of this node)
		int posLen = topPos.size();

		// the length of the node's information( curPos + key + pos + color )
		int nodeInforLen = (3 + posLen) * sizeof(int);

		// first write how long the node's information is
		// then write every necessary information
		indexFile.write((char*)& nodeInforLen, sizeof(int));

		for (int i = 0; i < posLen; ++i) {
			indexFile.write((char*)& topPos[i], sizeof(int));
		}
		indexFile.write((char*)&topNode->key, sizeof(int));
		indexFile.write((char*)&topNode->pos, sizeof(int));
		indexFile.write((char*)&topNode->color, sizeof(int));

		Node* lc = topNode->left;
		Node* rc = topNode->right;

		// don't write leaves into index file
		if (lc->pos != -1) {
			nodeWindow.push(lc);
			vector<int> leftPos = topPos;
			leftPos.push_back(LEFT);
			posWindow.push(leftPos);
		}

		if (rc->pos != -1) {
			nodeWindow.push(rc);
			vector<int> rightPos = topPos;
			rightPos.push_back(RIGHT);
			posWindow.push(rightPos);
		}
	}

	indexFile.close();
}

// there is no index file, set the tree from raw data
void treeFromData(RBTree & tree, Cache & cache) {
	ifstream dataFile(dataFileName, ios::in | ios::binary);
	dataFile.seekg(0, ios::end);
	int length = dataFile.tellg();
	dataFile.seekg(0, ios::beg);

	// current position in dataFile
	int curPos = 0;

	while (curPos != length) {
		//dataFile.clear(ios::goodbit);

		int nodeKey = -1;
		int nodeValue = -1;

		dataFile.read((char*)& nodeKey, sizeof(int));
		dataFile.read((char*)& nodeValue, sizeof(int));

		tree.add(nodeKey, nodeValue, cache);

		curPos += NODE_BYTE;
	}
	//=======================
	// delete or not
	cache.addNode.clear();
	//=======================
	dataFile.close();
	// set the index file
	setIndexFile(tree);
}


//===============================================================
//----------------------------------- check input ---------------
bool isNum(string & str) {
	int len = str.size();
	string sub = "";
	for (int i = 0; i < len; ++i) {
		sub = str.substr(i, 1);
		if ((sub < "0" || sub > "9") && (sub != "-")) {
			cout << "Error: Invalid input!( int only )" << endl;
			cout << "Please enter again." << endl;
			return false;
		}
	}

	stringstream ss;
	ss << str;
	long int tempInt = 0;
	ss >> tempInt;

	if (tempInt > numeric_limits<int>::max()) {
		cout << "Error: number out of int range( too big )!" << endl;
		cout << "Please enter again." << endl;
		return false;
	}
	if (tempInt < numeric_limits<int>::min()) {
		cout << "Error: number out of int range( too small )!" << endl;
		cout << "Please enter again." << endl;
		return false;
	}
	return true;
}

//===============================================================
//----------------- check if a data file is opened ---------------
bool haveOpenedFile() {
	fstream dataFile(dataFileName, ios::in | ios::binary);
	if (!dataFile) {
		return false;
	}
	else {
		dataFile.close();
		return true;
	}
}
