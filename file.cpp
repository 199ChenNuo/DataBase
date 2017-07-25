#include "file.h"

#include <sstream>

// contain key(int: 4 bytes) and a " "(1 byte)
#define INDEX_BYTE sizeof(int)
// contain value(4 bytes)
#define VALUE_BYTE sizeof(int)
// contain key(int: 4 bytes), " "(1 byte), '\n' (1 byte) and  value(int: 4 bytes)
#define NODE_BYTE  VALUE_BYTE+INDEX_BYTE

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
		cout << "open " << dataFileName << " failed." << endl;
		dataFileName = getFileName();
		if (dataFileName == "quit")
			return;
		dataFile.open(dataFileName, ios::in | ios::binary);
	}


	indexFileName = "indexFor" + dataFileName;

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
		for (int i = 0; i < deleteSize; ++i) {
			int pos = cache.deletePos.top();
			cache.deletePos.pop();
			cout << "Delete data in data file, pos:" << pos << endl;
			fileDeleteNode(dataFile, pos);
		}
		map<Node*, int>::iterator it;
		for (it = cache.addNode.begin(); it != cache.addNode.end(); ++it) {
			int key = it->first->key;
			int pos = it->first->pos;
			int value = it->second;
			cout << "newly add data in data file, key: " << key << " pos: " << pos << " value: " << value << endl;
			fileAddNode(dataFile, pos, value);
		}
		for (it = cache.modifyNode.begin(); it != cache.modifyNode.end(); ++it) {
			int key = it->first->key;
			int pos = it->first->pos;
			int value = it->second;
			cout << "modify data in data file, key: " << key << " pos: " << pos << " value: " << value << endl;
			fileModifyNode(dataFile, pos, value);
		}
		cache.modifyNode.clear();
		cache.addNode.clear();
	}
}

void fileDeleteNode(fstream & dataFile, int pos) {
	int nodePos = pos * NODE_BYTE;
	dataFile.seekg(0, ios::beg);
	int fileLen = dataFile.tellg();
	// the pos of node( next to the node to be deleted)
	dataFile.seekg(nodePos + NODE_BYTE, ios::beg);
	int nodeNum = (fileLen - nodePos) / NODE_BYTE;
	for (int i = 0; i < nodeNum; ++i) {
		int key = -1;
		int value = -1;
		dataFile.read((char*)&key, sizeof(int));
		dataFile.read((char*)&value, sizeof(int));
		dataFile.seekg(-8);
		dataFile.write((char*)&key, sizeof(int));
		dataFile.write((char*)&value, sizeof(int));
	}
}

void fileModifyNode(fstream & dataFile, int pos, int value) {
	int nodePos = pos * NODE_BYTE;
	dataFile.seekg(nodePos + INDEX_BYTE, ios::beg);
	dataFile.write((char*)&value, value);
}

void fileAddNode(fstream & dataFile, int pos, int value) {
	// form last to pos, push back
	// put node into pos
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
	indexFile.seekg(0, ios::end);
	int indexLen = indexFile.tellg();
	int curPos = 0;
	indexFile.seekg(0, ios::beg);

	int nodeNum = indexLen / NODE_BYTE;
	while(curPos != indexLen) {
		int nodeInforLen = 0;
		string nodePos = "";
		int key = -1;
		int pos = -1;
		int color = -1;

		// get the length of the information of the node
		indexFile.read((char*)& nodeInforLen, sizeof(int));

		indexFile.read((char*)& nodePos, nodeInforLen - 3 * sizeof(int));
		indexFile.read((char*)& key, sizeof(int));
		indexFile.read((char*)& pos, sizeof(int));
		indexFile.read((char*)& color, sizeof(int));

		indexAddNode(tree, nodePos, key, pos, color);

		curPos += NODE_BYTE;
	}
}

void indexAddNode(RBTree & tree, string & nodePos, int key, int pos, int color) {
	Node* cur = tree.getRoot();
	Node* fatherNode = cur;

	// if the tree is empty
	if (cur == NULL || cur->pos == -1) {
		delete cur;
		cur = new Node(key, pos);
		tree.setLastPos(1);
		return;
	}

	int size = nodePos.size();

	for (int i = 0; i < size; ++i) {
		fatherNode = cur;
		string dirction = nodePos.substr(i, 1);
		cur = (dirction == to_string(LEFT)) ? cur->left : cur->right;
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

// set index file
// nodes are managed in level-order
void setIndexFile(RBTree & tree, string & indexFileName) {
	ofstream indexFile(indexFileName, ios::out | ios::binary);

	queue<Node*> nodeWindow;
	queue<string> posWindow;

	Node* root = tree.getRoot();

	// if the tree is empty
	if (root == NULL) {
		return;
	}

	// initialize two windows
	nodeWindow.push(root);
	posWindow.push("");

	while (nodeWindow.size() != 0) {
		Node* topNode = nodeWindow.front();
		nodeWindow.pop();

		string curPos = posWindow.front();
		posWindow.pop();

		// the length of the node's information( curPos + key + pos + color )
		int nodeInforLen = 3*sizeof(int) + sizeof(char)*curPos.size();

		// first write how long the node's information is
		// then write every necessary information
		indexFile.write((char*)& nodeInforLen, sizeof(int));
		indexFile.write(curPos.c_str(), sizeof(char) * curPos.size());
		indexFile.write((char*)&topNode->key, sizeof(int));
		indexFile.write((char*)&topNode->pos, sizeof(int));
		indexFile.write((char*)&topNode->color, sizeof(int));
		
		Node* lc = topNode->left;
		Node* rc = topNode->right;

		if (lc->pos != -1) {
			nodeWindow.push(lc);
			posWindow.push(curPos + to_string(LEFT));
		}

		if (rc->pos != -1) {
			nodeWindow.push(rc);
			posWindow.push(curPos + to_string(RIGHT));
		}
	}

	indexFile.close();
}

void treeFromData(RBTree & tree, fstream & dataFile, Cache & cache) {
	dataFile.seekg(0, ios::end);
	int length = dataFile.tellg();
	dataFile.seekg(0, ios::beg);

	// the number of nodes
	int nodeNum = length / NODE_BYTE;
	// current position in dataFile
	int curPos = 0;

	cout << "length:" << length << " NODE_BYTE:" << NODE_BYTE << endl;
	cout << "nodeNum:" << nodeNum << endl;

	while(curPos!=length) {
		//dataFile.clear(ios::goodbit);
		//dataFile.seekg(curPos, ios::beg);

		int nodeKey = -1;
		int nodeValue = -1;

		dataFile.read((char*)& nodeKey, sizeof(int));
		dataFile.read((char*)& nodeValue, sizeof(int));

		tree.add(nodeKey, nodeValue, cache);

		curPos += NODE_BYTE;
	}

	// set the index file
	setIndexFile(tree, indexFileName);
}
