#include "file.h"

#include <sstream>

// contain key(int: 4 bytes), " "(1 byte), '\n' (1 byte) and  value(int: 4 bytes)
#define NODE_BYTE 8
// contain key(int: 4 bytes) and a " "(1 byte)
#define INDEX_BYTE 4
// contain value(4 bytes)
#define VALUE_BYTE 4

extern string dataFileName;
extern string indexFileName;

//=============================================================
//------------------------------------ function about node ----------------------------------------
void viewNode(fstream & dataFile, RBTree & tree, Cache & cache) {

	int key = 0;

	cout << "Viewing..." << endl;
	cout << "Please enter the key" << endl;
	cin >> key;

	map<Node*, int>::iterator it;
	int value = 0;

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

	Node* node = tree.fetch(key);
	tree.printSingle(node);
	if (node != NULL && node->pos != -1) {
		int pos = node->pos;
		value = viewValue(dataFile, pos);
		cout << "value read in from data file--|" << value << "|--" << endl;
	}
	else {
		cout << "Error: key does not exits!" << endl;
		return;
	}
	cout << "Key: " << key << " Value: " << value << endl;
}

int viewValue(fstream & dataFile, int pos) {
	// get to the pos in the file
	int startByte = pos * NODE_BYTE + INDEX_BYTE;

	int value = 0;

	dataFile.open(dataFileName, ios::in | ios::binary);

	dataFile.seekg(startByte, ios::beg);
	dataFile.read((char*)&value, VALUE_BYTE);

	dataFile.close();
	return value;
}

void addNode(fstream & dataFile, RBTree & tree, Cache & cache) {
	int key = 0;
	int value = 0;

	cout << "Adding..." << endl;
	cout << "Please enter the key:" << endl;
	cin >> key;
	cout << "Please enter the value:" << endl;
	cin >> value;

	tree.add(key, value, cache);

	// better to put this step into tree.add(key, value, cache);
	// therefore, only one tree.fetch(key) is needed(now it needs twice);
	// alse, pass cache into add can enable add to use deltepos in cache
	cache.addNode[tree.fetch(key)] = value;

	if (cache.addNode.size() == SIZE_TO_UPDATE) {
		updateFile(dataFile, cache);
	}
}

void modifyNode(fstream & dataFile, RBTree & tree, Cache & cache) {
	int key = 0;
	int newValue = 0;

	cout << "Modifying..." << endl;
	cout << "Please enter the key:" << endl;
	cin >> key;
	cout << "Please enter the new value:" << endl;
	cin >> newValue;

	tree.modify(key, newValue, cache);

	// better to put this step into tree.modify(key, value, cache);
	// therefor, only one tree.fetch(key) is needed(now it needs twice);
	Node* node = tree.fetch(key);
	cache.modifyNode[node] = newValue;
	cache.addNode[node] = newValue;

	if (cache.modifyNode.size() == SIZE_TO_UPDATE) {
		updateFile(dataFile, cache);
	}

}

void deleteNode(fstream & dataFile, RBTree & tree, Cache & cache) {
	int key = 0;

	cout << "Deleting..." << endl;
	cout << "Please enter the key:" << endl;
	cin >> key;

	Node* node = tree.fetch(key);
	if (node == NULL || node->pos == -1) {
		cout << "Error: key " << key << " does not exits!" << endl;
		return;
	}
	
	// cache is updated in tree.remove(int key, Cache& cache)
	tree.remove(key, cache);

	if (cache.deletePos.size() == SIZE_TO_UPDATE) {
		updateFile(dataFile, cache);
	}
}

//---------------- end --------------------------------------------------------------------
//======================================================


//======================================================
//----------------- function about file ---------------------------------------------------


void getFile(fstream & dataFile, RBTree & tree, Cache & cache) {
	dataFileName = getFileName();
	dataFile.open(dataFileName, ios::in | ios::binary);

	while (!dataFile) {
		dataFileName = getFileName();
		if (dataFileName == "quit")
			return;
		dataFile.open(dataFileName, ios::in | ios::binary);
	}


	indexFileName = "IndexFor" + dataFileName;

	treeFromFile(tree, dataFile, indexFileName, cache);

}

string getFileName() {
	string dataFileName = "";
	cout << "Please enter the and name of data file" << endl;
	cout << "(quit) to quit" << endl;
	cin >> dataFileName;
	return dataFileName;
}

void updateFile(fstream & dataFile, Cache & cache) {
	int modifySize = cache.modifyNode.size();
	int addSize = cache.addNode.size();
	int deleteSize = cache.deletePos.size();

	if (modifySize || addSize || deleteSize) {
		cout << "updating the file...";
		for (int i = 0; i < modifySize; ++i) {
			int pos = cache.deletePos.top();
			cache.deletePos.pop();
			cout << "Delete data in data file, pos:" << pos << endl;
		}
		map<Node*, int>::iterator it;
		for (it = cache.addNode.begin(); it != cache.addNode.end(); ++it) {
			int key = it->first->key;
			int pos = it->first->pos;
			int value = it->second;
			cout << "newly add data in data file, key: " << key << " pos: " << pos << " value: " << value << endl;
		}
		for (it = cache.modifyNode.begin(); it != cache.modifyNode.end(); ++it) {
			int key = it->first->key;
			int pos = it->first->pos;
			int value = it->second;
			cout << "modify data in data file, key: " << key << " pos: " << pos << " value: " << value << endl;
		}
		cache.modifyNode.clear();
		cache.addNode.clear();
	}
}

void closeFile(fstream & dataFile, string & indexFileName, RBTree & tree, Cache & cache) {
	updateFile(dataFile, cache);
	setIndexFile(tree, indexFileName);
	dataFile.close();
}

//-------------------------------------------- end --------------------------------------------
//========================================================

//============================================================
//------------------ function for tree ---------------------------------------------------------------

void treeFromFile(RBTree & tree, fstream & dataFile, string & indexFileName, Cache & cache) {
	fstream indexFile;
	indexFile.open(indexFileName, ios::in | ios::binary);

	if (!indexFile) {
		// there is no index file, set tree from raw data
		treeFromData(tree, dataFile, cache);
		return;
	}

	// set tree from index file
	string line = "";
	while (getline(indexFile, line)) {
		string::size_type pos1, pos2, pos3;
		string nodePos;
		stringstream ss1, ss2, ss3;
		int dataKey = 0;
		int dataPos = 0;
		int nodeColor = 0;

		pos1 = line.find(" ");
		pos2 = line.find(" ", pos1 + 1);
		pos3 = line.find(" ", pos2 + 1);

		nodePos = line.substr(0, pos1);
		ss1 << line.substr(pos1 + 1, pos2 - pos2 - 1);
		ss2 << line.substr(pos2 + 1, pos3 - pos2 - 1);
		ss3 << line.substr(pos3 + 1);

		ss1 >> dataKey;
		ss2 >> dataPos;
		ss3 >> nodeColor;

		indexAddNode(tree, nodePos, dataKey, dataPos, nodeColor);
	}
}

void indexAddNode(RBTree & tree, string & nodePos, int dataKey, int dataPos, int nodeColor) {
	Node* cur = tree.getRoot();
	Node* fatherNode = cur;

	if (cur == NULL || cur->pos == -1) {
		delete cur;
		cur = new Node(dataKey, dataPos);
		return;
	}

	int size = nodePos.size();

	for (int i = 0; i < size; ++i) {
		fatherNode = cur;
		string dirction = nodePos.substr(i, 1);
		cur = (dirction == to_string(LEFT)) ? cur->left : cur->right;
	}

	bool isLeft = true;
	if (cur == fatherNode->right) {
		isLeft = false;
	}

	cur = new Node(dataKey, dataPos);
	cur->color = nodeColor;
	cur->father = fatherNode;
	if (isLeft) {
		fatherNode->left = cur;
	}
	else {
		fatherNode->right = cur;
	}

}

void treeFromData(RBTree & tree, fstream & dataFile, string & indexFileName, Cache & cache) {
	string line = "";
	while (getline(dataFile, line)) {
		string::size_type pos = line.find(" ");

		stringstream ss1, ss2;
		int dataKey = 0;
		int dataValue = 0;

		ss1 << line.substr(0, pos);
		ss2 << line.substr(pos + 1);

		ss1 >> dataKey;
		ss2 >> dataValue;

		tree.add(dataKey, dataValue, cache);
	}

	setIndexFile(tree, indexFileName);
}

void setIndexFile(RBTree & tree, string & indexFileName) {
	fstream indexFile(indexFileName);

	queue<Node*> nodeWindow;
	queue<string> posWindow;
	nodeWindow.push(tree.getRoot());
	posWindow.push("");


	while (nodeWindow.size() != 0) {
		Node* topNode = nodeWindow.front();
		nodeWindow.pop();

		string curPos = posWindow.front();
		posWindow.pop();

		Node* rc = topNode->right;
		Node* lc = topNode->right;

		indexFile << curPos << " " << topNode->key << " " << topNode->pos << " " << topNode->color << '\n';

		if (lc != NULL && lc->pos != -1) {
			nodeWindow.push(lc);
			posWindow.push(curPos + to_string(LEFT));
		}

		if (rc != NULL && rc->pos != -1) {
			nodeWindow.push(rc);
			posWindow.push(curPos + to_string(RIGHT));
		}
	}

	indexFile.close();
}

void treeFromData(RBTree & tree, fstream & dataFile, Cache & cache) {
	dataFile.seekg(0, ios::end);
	int lenght = dataFile.tellg();
	dataFile.seekg(0, ios::beg);

	cout << "file len" << lenght << endl;

	int nodeNum = lenght / NODE_BYTE;
	int curPos = 0;

	for (int i = 0; i < nodeNum; ++i) {
		dataFile.clear(ios::goodbit);
		//cout << "TempPos:" << dataFile.tellg() << endl;

		dataFile.seekg(curPos, ios::beg);

		int nodeKey = -2;
		int nodeValue = -2;

		dataFile.read((char*)& nodeKey, sizeof(int));
		int tempPos = dataFile.tellg();
		//cout << "TempPos:" << tempPos << endl;
		if (tempPos == -1) {
			tempPos = curPos + sizeof(int);
			cout << "TempPos:" << tempPos << endl;
			system("pause");
		}
		dataFile.read((char*)&nodeValue, sizeof(int));
		tempPos = dataFile.tellg();
		//cout << "TempPos:" << tempPos << endl;
		if (tempPos == -1) {
			tempPos = curPos + sizeof(int);
			cout << "TempPos:" << tempPos << endl;
			system("pause");
		}
			

		//if (nodeKey == -2) {
			//cout << "tempPos:" << dataFile.tellg() << endl;
			//system("pause");
		//}

		//cout << "key: " << nodeKey << "\tValue: " << nodeValue << endl;

		!tree.add(nodeKey, nodeValue, cache);
		curPos += NODE_BYTE;

		//cout << "TempPos:" << dataFile.tellg() << endl;
		dataFile.seekg(curPos, ios::beg);
		//cout << "TempPos:" << dataFile.tellg() << " cur Pos" << curPos << endl;
		//cout << "=======================" << endl;

	}
}
