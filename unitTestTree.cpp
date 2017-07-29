#include "test.h"

using namespace std;

//-------------- initialize tree -----------------
void totalNodeTest0() {
	RBTree tree;
	Cache cache;
	for (int i = 0; i < 1000000; ++i) {
		tree.add(i, i, cache);
	}

	for (int i = 0; i < 1000000; ++i) {

		if (i % 1000 == 0) {
			int total = tree.totalNode();

			if (total != 1000000 - i) {
				// delete more than one
				cout << "remove case fail." << endl;
				break;
			}
		}

		Node* node = tree.getRoot();
		tree.remove(node->key, cache);
	}

}
void totalNodeTest1() {
	RBTree tree;
	Cache cache;

	int count = 0;
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			int key = rand() % 1000 + i * 1000;
			count += tree.add(key, key, cache);
		}
		cache.addNode.clear();
	}
	
	int total = tree.getLastPos();
	cout << "Total:" << total << endl;

	for (int i = 0; i < count; ++i) {

		Node* root = tree.getRoot();
		tree.remove(root->key, cache);
	}

}
void tree0(){
    RBTree tree;
}

void tree1(){
    RBTree tree(0, 0);
}

//------- zig zag ---------------------------------------
void zig0() {
	RBTree tree;
	Cache cache;
	
	for (int i = 0; i < 15; ++i) {
		tree.add(i, i, cache);
	}

	tree.print(cache);

	Node* node = tree.fetch(3);
	tree.zig(node);

	cout << endl << endl;

	tree.print(cache);
}

void zag0() {
	RBTree tree;
	Cache cache;
	
	for (int i = 0; i < 15; ++i) {
		tree.add(i, i, cache);
	}

	tree.print(cache);

	Node* node = tree.fetch(3);
	tree.zag(node);

	cout << endl << endl;

	tree.print(cache);
}

//---------- isBalance(Node* & node) ---------
void balanceTest0() {
	RBTree tree;
	Cache cache;
	Node* zero = new Node(0, 0);
	Node* one = new Node(1, 0);
	Node* two = new Node(2, 0);
	Node* three = new Node(3, 0);
	Node* four = new Node(4, 0);
	Node* five = new Node(5, 0);
	Node* six = new Node(6, 0);

	zero->father = one;
	one->left = zero;
	two->father = one;
	one->right = two;
	one->father = three;
	three->left = one;
	four->father = five;
	five->left = four;
	six->father = five;
	five->right = six;
	five->father = three;
	three->right = five;

	
}

void balanceTest1() {
	RBTree tree;
	Cache cache;
	Node* zero = new Node(0, 0);
	zero->color = RED;
	Node* one = new Node(1, 0);
	Node* two = new Node(2, 0);
	Node* three = new Node(3, 0);
	Node* four = new Node(4, 0);
	Node* five = new Node(5, 0);
	Node* six = new Node(6, 0);

	zero->father = one;
	one->left = zero;
	two->father = one;
	one->right = two;
	one->father = three;
	three->left = one;
	four->father = five;
	five->left = four;
	six->father = five;
	five->right = six;
	five->father = three;
	three->right = five;

	tree.setRoot(three);


	Node* root = tree.getRoot();
	
}

//--------------- add new node -------------------------
void treeAdd0(){
    RBTree tree;
    Cache cache;

    // add many keys
    for(int i = 0; i < 40; ++i){
        tree.add(i, i, cache);
    }
	
}

void treeAdd1(){
    RBTree tree;
    Cache cache;

    // add two same keys
    tree.add(0, 0, cache);
    tree.add(0, 0, cache);
	tree.add(1, -1, cache);
}


//------------- remove node -------------------------
// the smallest node in right subtree is RED
void removeCase0() {
	RBTree tree;
	Cache cache;
	Node* zero = new Node(0, 0);
	Node* one = new Node(1, 0);
	Node* two = new Node(2, 0);
	Node* three = new Node(3, 0);
	Node* four = new Node(4, 0);
	Node* five = new Node(5, 0);
	Node* six = new Node(6, 0);

	zero->father = one;
	one->left = zero;
	two->father = one;
	one->right = two;
	one->father = three;
	three->left = one;
	four->father = five;
	five->left = four;
	six->father = five;
	five->right = six;
	five->father = three;
	three->right = five;

	one->color = six->color = four->color = RED;

	
	tree.setRoot(three);

	tree.print(cache);
	tree.remove(3, cache);
	cout << "remove 3" << endl;
	tree.print(cache);

	Node* newRoot = tree.getRoot();
	if ((tree.fetch(3) == NULL)) {
		cout << "remove case0 pass." << endl;
	}
}

// the smallest node in right subtree is BLACK
void removeCase1() {
	RBTree tree;
	Cache cache;
	Node* zero = new Node(0, 0);
	Node* one = new Node(1, 0);
	Node* two = new Node(2, 0);
	Node* three = new Node(3, 0);
	Node* four = new Node(4, 0);
	Node* five = new Node(5, 0);
	Node* six = new Node(6, 0);

	zero->father = one;
	one->left = zero;
	two->father = one;
	one->right = two;
	one->father = three;
	three->left = one;
	four->father = five;
	five->left = four;
	six->father = five;
	five->right = six;
	five->father = three;
	three->right = five;

	tree.setRoot(three);

	tree.print(cache);
	tree.remove(3, cache);
	cout << "remove 3" << endl;
	tree.print(cache);

	Node* newRoot = tree.getRoot();
	if ((tree.fetch(3) == NULL)) {
		cout << "remove case1 pass." << endl;
	}
}

// no right subtree
// the biggest node in left subtree is RED
void removeCase2() {
	RBTree tree;
	Cache cache;
	Node* zero = new Node(0, 0);
	Node* one = new Node(1, 0);
	//Node* two = new Node(2, 0);
	Node* three = new Node(3, 0);
	Node* four = new Node(4, 0);
	Node* five = new Node(5, 0);
	Node* six = new Node(6, 0);

	zero->father = one;
	one->left = zero;
	//two->father = one;
	//one->right = two;
	one->father = three;
	three->left = one;
	four->father = five;
	five->left = four;
	six->father = five;
	five->right = six;
	five->father = three;
	three->right = five;

	zero->color = five->color = RED;

	tree.setRoot(three);
	
	tree.print(cache);
	tree.remove(1, cache);
	cout << "remove 1" << endl;
	tree.print(cache);

	Node* newRoot = tree.getRoot();
	if ((tree.fetch(1) == NULL) ) {
		cout << "remove case2 pass." << endl;
	}
}

// no right subtree
// the biggest node in left subtree is BLACK
void removeCase3() {
	RBTree tree;
	Cache cache;
	Node* zero = new Node(0, 0);
	Node* one = new Node(1, 0);
	Node* two = new Node(2, 0);
	Node* three = new Node(3, 0);
	Node* four = new Node(4, 0);
	Node* five = new Node(5, 0);
	Node* six = new Node(6, 0);

	zero->father = one;
	one->left = zero;
	two->father = one;
	one->right = two;
	one->father = three;
	three->left = one;
	four->father = five;
	five->left = four;
	six->father = five;
	five->right = six;
	five->father = three;
	three->right = five;

	tree.setRoot(three);
	
	tree.print(cache);
	tree.remove(0, cache);
	cout << "remove 0" << endl;
	tree.print(cache);

	Node* newRoot = tree.getRoot();
	if ((tree.fetch(0) == NULL) ) {
		cout << "remove case3 pass." << endl;
	}
}

// no subtree
// node is RED
void removeCase4() {
	RBTree tree;
	Cache cache;
	Node* zero = new Node(0, 0);
	Node* one = new Node(1, 0);
	Node* two = new Node(2, 0);
	Node* three = new Node(3, 0);
	Node* four = new Node(4, 0);
	Node* five = new Node(5, 0);
	Node* six = new Node(6, 0);

	zero->father = one;
	one->left = zero;
	two->father = one;
	one->right = two;
	one->father = three;
	three->left = one;
	four->father = five;
	five->left = four;
	six->father = five;
	five->right = six;
	five->father = three;
	three->right = five;

	zero->color = two->color = four->color = six->color = RED;

	tree.setRoot(three);

	tree.print(cache);
	tree.remove(0, cache);
	cout << "remove 0" << endl;
	tree.print(cache);

	Node* newRoot = tree.getRoot();
	if ((tree.fetch(0) == NULL)) {
		cout << "remove case4 pass." << endl;
	}
}


// no subtree
// node is BLACK
void removeCase5() {
	RBTree tree;
	Cache cache;
	Node* zero = new Node(0, 0);
	Node* one = new Node(1, 0);
	Node* two = new Node(2, 0);
	Node* three = new Node(3, 0);
	Node* four = new Node(4, 0);
	Node* five = new Node(5, 0);
	Node* six = new Node(6, 0);

	zero->father = one;
	one->left = zero;
	two->father = one;
	one->right = two;
	one->father = three;
	three->left = one;
	four->father = five;
	five->left = four;
	six->father = five;
	five->right = six;
	five->father = three;
	three->right = five;

	tree.setRoot(three);

	tree.print(cache);
	tree.remove(0, cache);
	cout << "remove 0" << endl;
	tree.print(cache);

	Node* newRoot = tree.getRoot();
	if ((tree.fetch(0) == NULL) ) {
		cout << "remove case5 pass." << endl;
	}
}


void treeRemove0(){
	fstream dataFile("largeDataBase.txt");
    RBTree tree;
    Cache cache;

	string line = "";
	while (getline(dataFile, line)) {
		int pos = line.find(" ");
		int key = 0, value = 0;
		stringstream ss1, ss2;
		ss1 << line.substr(0, pos);
		ss2 << line.substr(pos + 1);
		ss1 >> key;
		ss2 >> value;
		tree.add(key, value, cache);
	}

	int count = 0;
	int total = tree.totalNode();
	Node* curNode = tree.getRoot();
	while (curNode != NULL) {
		tree.remove(curNode->key, cache);
		curNode = tree.getRoot();
		cache.deletePos.pop();
		count++;
		cout << "temp node total:" << tree.totalNode() << endl;
	}

	dataFile.close();
	cout << "all node: " << total << endl;
	cout << "delete for time: " << count << endl;
}

void treeRemove1(){
    RBTree tree;
    Cache cache;

    for(int i = 0; i < 2000; ++i){
        tree.add(i, i, cache);
		cache.addNode.clear();
    }

	tree.printSingle(tree.maxNodeOf(tree.getRoot()->left), cache);

	int preTotal = 2000;
	int newTotal = 2000;
    // remove a lot of keys
	for (int i = 0; i < 2000; ++i) {
		preTotal = newTotal;
		Node* curRoot = tree.getRoot();
		

		tree.remove(curRoot->key, cache);
		cache.deletePos.pop();


		newTotal = tree.totalNode();

		if (preTotal - newTotal != 1) {
			cout << "root:" << endl;
			tree.printSingle(curRoot, cache);
			system("pause");
		}
		else {
			cout << "delete!" << endl;
		}
    }

}

void treeRemove2(){
	RBTree tree;
	Cache cache;

	int count = 0;
	int span = 1000;
	int times = 1000000 / span;

	for (int i = 0; i < times; ++i) {
		for (int j = 0; j < span; ++j) {
			int key = rand() % span + i * span;
			if (tree.add(key, key, cache)) {
				count++;
			}
		}
		cache.addNode.clear();
	}
	for (int i = 0; i < count; ++i) {
		if (i % 1000 == 0) {
			if (tree.totalNode() != count - i) {
				system("pause");
			}
		}
		Node* root = tree.getRoot();
		tree.remove(root->key, cache);
	}
}


//-------------- fetch node ---------------------------
void treeFetch0(){
    RBTree tree;
    Cache cache;

    Node* node = tree.fetch(0);
    tree.printSingle(node, cache);

    tree.add(0, 0, cache);
    node = tree.fetch(0);
    tree.printSingle(node, cache);
}

void treeFetch1(){
    RBTree tree;
    Cache cache;

    for(int i = 0; i < 100; ++i){
        tree.add(i, i, cache);
        Node* node = tree.fetch(i);

        if(node == NULL){
            cout << "ERROR!" << endl;
            break;
        }
    }
}


//------------ print node -----------------------
void treePrint0(){
    RBTree tree;
    Cache cache;

    for(int i = 0; i < 9; ++i){
        cout << "============================"<<endl;
        cout << "root:" << endl;
        tree.printSingle(tree.getRoot(), cache);
        cout << "the whole tree:" << endl;
        tree.print(cache);
    }
}

void treePrint1(){
    RBTree tree;
    Cache cache;

    tree.print(cache);

    tree.printSingle(NULL, cache);
}