#include "test.h"

void tempIndexTest() {
	ifstream indexFile("indexFortemp.txt", ios::in | ios::binary);
	indexFile.seekg(0, ios::end);
	int len = indexFile.tellg();
	indexFile.seekg(0, ios::beg);
	int curPos = 0;
	while (curPos != len) {
		cout << "curPos" << curPos << "\tlen" << len << endl;
		int nodeInforLen = 0;
		int key = -1;
		int pos = -1;
		int color = -1;

		// get the length of the information of the node
		indexFile.read((char*)& nodeInforLen, sizeof(int));

		char* nodePos = new char[nodeInforLen - 3 * sizeof(int)];

		indexFile.read(nodePos, nodeInforLen - 3 * sizeof(int));
		indexFile.read((char*)& key, sizeof(int));
		indexFile.read((char*)& pos, sizeof(int));
		indexFile.read((char*)& color, sizeof(int));

		cout << "nodeInforLen: " << nodeInforLen << endl;
		cout << "nodePos: " << nodePos << endl;
		cout << "key: " << key << endl;
		cout << "pos: " << pos << endl;
		cout << "color: " << color << endl;
		cout << "===============================" << endl;

		curPos = indexFile.tellg();
	}
	indexFile.close();
	system("pause");
}