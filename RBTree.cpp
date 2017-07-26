#include "RBTree.h"
#include <string>
#include <sstream>

using namespace std;

//---------------------------------------
RBTree::RBTree(){
    root = new Node;
    height = 0;
    lastPos = 0;
}

RBTree::RBTree(int key, int value){
    this->root = new Node;
    *root = Node(key, 0);
    root->color = BLACK;
	root->height = 0;
    this->setHeight(1);
    this->setLastPos(1);
}


void RBTree::clear() {
	queue<Node*> nodeWindow;
	nodeWindow.push(root);

	while (nodeWindow.size() != 0) {
		Node* topNode = nodeWindow.front();
		nodeWindow.pop();

		if (topNode->pos != -1) {
			nodeWindow.push(topNode->left);
			nodeWindow.push(topNode->right);
		}
		delete topNode;
	}
	root = new Node;
	lastPos = 0;
}

//-------------------------------------

Node* RBTree::getRoot(){
    return this->root;
}

int RBTree::getHeight(){
    return this->height;
}

int RBTree::getLastPos(){
    return lastPos;
}

//-----------------------------------

void RBTree::setRoot(Node* & newRoot){
    this->root = newRoot;
}

void RBTree::setHeight(int newHeight){
    this->height = newHeight;
}

void RBTree::setLastPos(int newPos){
    this->lastPos = newPos;
}

//--------------------------------------------------


// in-order
void RBTree::print(){

    if(root == NULL){
		cout << "Empty tree" << endl;
		return;
    }

	if (root->pos == -1) {
		cout << "Empty Tree" << endl;
		return;
	}

    Node* tempNode = root;

	if (tempNode->left != NULL) {

		print(tempNode->left);
	}
    
	if (tempNode != NULL) {
		if (tempNode->pos != -1) {
			cout << "Key: " << tempNode->key << "\tROOT" << "\tColor: " << tempNode->color << "\nRight:" << tempNode->right->key
				<< "\tLeft:" << tempNode->left->key << endl << endl;
		}
	}

	if (tempNode->right != NULL) {

		print(tempNode->right);
	}

}

void RBTree::print(Node*  node){

	if (node == NULL) {
		cout << "Error: empty node!" << endl;
		return;
	}

	if (node->pos == -1)
		return;

	if (node->left != NULL && node->left->pos != -1) {

		print(node->left);
	}
        

    if(node == NULL ){
        cout << "node is NULL" << endl;
    }else{
		cout << "Key: " << node->key << "\tColor: " << node->color << "\tFather: " << node->father->key
			<< "\nRight:" << node->right->key << "\tLeft:" << node->left->key << endl << endl;
    }

	if (node->right != NULL && node->right->pos != -1) {

		print(node->right);
	}
}


void RBTree::print(int key){
    Node* node = fetch(key);
    print(node);
}

void RBTree::printSingle(Node* node) {
	if (node == NULL) {
		cout << "NULL node" << endl;
		return;
	}
	if ((node->left == NULL) || (node->left->pos == -1)) {
		cout << "Left child is NULL" << endl;
	}
	else {
		cout << "Left child: " << node->left->key << endl;
	}

	cout << "Key: " << node->key << "\tfather: " << node->father->key << "\tColor: " << node->color << endl;

	if ((node->right == NULL) || (node->right->pos == -1)) {
		cout << "Right child is NULL" << endl;
	}
	else {
		cout << "Right child: " << node->right->key << endl;
	}
	cout << endl;
}

//-----------------------------------------------------------
// doubleRed
// new version 2017/07/23 13:13
void RBTree::doubleRed(Node* & redNode) {

	if (redNode == root) {
		redNode->color = BLACK;
		return;
	}

	Node* dad = redNode->father;

	if (dad->color != RED) {
		return;
	}

	if (dad == root) {
		dad->color = BLACK;
		return;
	}

	Node* grandpa = dad->father;
	Node* uncle = (dad == grandpa->right) ? grandpa->left : grandpa->right;

	// if curNode and newNode are on the same side
	if ((dad == grandpa->left) == (redNode == dad->left)) {

		// single rotate, finish
		if (uncle->color == BLACK) {
			redNode->color = BLACK;
			if (dad == grandpa->left) {
				zig(grandpa);
			}
			else {
				zag(grandpa);
			}
			if (dad->father->color != BLACK) {
				doubleRed(dad);
			}
		}
		else {
			// if uncle is also RED, push down BLACK level
			uncle->color = dad->color = BLACK;
			if (grandpa != root) {
				grandpa->color = RED;

				// check new condition with grandpa
				if (grandpa->father->color == RED) {
					doubleRed(grandpa);
				}
			}

			// if grandpa is root, finish
		}
	}
	else {
		// dad and newNode are in different side
		// rotate to make them on the same side and then go to conditions discussed above
		if (dad == grandpa->right) {
			// dad is right, newNode is left
			grandpa->right = redNode;
			grandpa->right->father = grandpa;

			redNode->right = dad;
			redNode->right->father = redNode;

			Node* newNode = new Node;
			dad->left = newNode;
			dad->left->father = dad;

			doubleRed(dad);
		}
		else {
			// dad is left, newNode is right
			grandpa->left = redNode;
			grandpa->left->father = grandpa;

			redNode->left = dad;
			redNode->left->father = redNode;

			Node* newNode = new Node;
			dad->right = newNode;
			dad->right->father = dad;

			doubleRed(dad);
		}
	}
}


// add
// new version 2017/07/23 13:13
bool RBTree::add(int key, int value, Cache & cache) {
	if (root == NULL || root->pos == -1) {
		root->key = key;
		root->pos = 0;
		root->right->height = root->left->height = 1;
		setLastPos(1);

		cache.addNode[root] = value;
		cout << "Add succeed!" << endl;
		return true;
	}

	
	Node* dad = root;

	int flag = 0;
	while (!flag) {
		if (key == dad->key) {
			cout << "Error: key " << key << " exits!" << endl;
			return false;
		}
		else if (key < dad->key) {
			flag = (dad->left->pos == -1) ? -1 : 0;
			dad = (!flag) ? dad->left : dad;
		}
		else {
			flag = (dad->right->pos == -1) ? 1 : 0;
			dad = (!flag) ? dad->right : dad;
		}
	}

	int pos = getLastPos();

	if (cache.deletePos.size() != 0) {
		pos = cache.deletePos.top();
		cache.deletePos.pop();
	}
	else {
		setLastPos(pos + 1);
	}

	if (flag == 1) {
		dad->right->pos = pos;
		dad->right->key = key;
		dad->right->color = RED;
		dad->right->left = new Node;
		dad->right->right = new Node;
		dad->right->left->father = dad->right->right->father = dad->right;
		doubleRed(dad->right);;
	}
	else {
		dad->left->pos = pos;
		dad->left->key = key;
		dad->left->color = RED;
		dad->left->left = new Node;
		dad->left->right = new Node;
		dad->left->left->father = dad->left->right->father = dad->left;
		doubleRed(dad->left);
	}
	
	cache.addNode[fetch(key)] = value;
	return true;
}

//new version
// 2017/07/21 22:01
bool RBTree::remove(int key, Cache & cache) {
	Node* node = fetch(key);

	if (node == NULL) {
		cout << "Error: key " << key << " does not exits!" << endl;
		return false;
	}

	if (node->pos == -1) {
		cout << "Error: key " << key << "does not exits!" << endl;
		return false;
	}

	// right chlid and left child of node
	Node* rc = node->right;
	Node* lc = node->left;

	// update cache
	cache.deletePos.push(node->pos);
	map<Node*, int>::iterator it;
	for (it = cache.modifyNode.begin(); it != cache.modifyNode.end(); ++it) {
		if (it->first->key == key) {
			cache.modifyNode.erase(it);
		}
	}
	for (it = cache.addNode.begin(); it != cache.addNode.end(); ++it) {
		if (it->first->key == key) {
			cache.addNode.erase(it);
		}
	}

	// replace node's key and pos with the smallest node in it's right subtree
	// or replace with the biggest node in it's left subtree

	// look in node's right subtree
	if ((rc != NULL) && (rc->pos != -1)) {

		Node* rightMin = minNodeOf(rc);

		// replace node
		node->key = rightMin->key;
		node->pos = rightMin->pos;

		// father of minNode
		Node* dad = rightMin->father;

		// minNode is RED, has no child, replace it with leaf, finish
		if (rightMin->color == RED) {
				rightMin->key = rightMin->pos = -1;
				rightMin->left = rightMin->right = NULL;
				rightMin->color = BLACK;
				cout << "Delete succeed!" << endl;
				return true;
		}

			// minNode is BLACK, right chlid of minNode
			Node* minRC = rightMin->right;

			if (minRC->color == RED) {
				rightMin->key = minRC->key;
				rightMin->pos = minRC->pos;
				minRC->key = minRC->pos = -1;
				minRC->color = BLACK;
			}

			else {
				rightMin->key = rightMin->pos = -1;
				rightMin->color = BLACK_BLACK;
				rightMin->right = rightMin->left = NULL;
			}

			doubleBlack(rightMin);
			cout << "Delete succeed!" << endl;
			return true;
	}

	// node does not have right subtree, look in node's left subtree
	else if ((lc != NULL) && (lc->pos != -1)) {
		Node* maxNode = maxNodeOf(lc);

		// replace node
		node->key = maxNode->key;
		node->pos = maxNode->pos;

		// father of maxNode
		Node* dad = maxNode->father;

		// maxNode is RED, has no child, replace it with leaf, finish
		if (maxNode->color == RED) {
			maxNode->key = maxNode->pos = -1;
			maxNode->left = maxNode->right = NULL;
			maxNode->color = BLACK;
			cout << "Delete succeed!" << endl;
			return true;
		}

		// maxNode is BLACK, left chlid of maxNode
		Node* maxLC = maxNode->left;

		// maxNode has no child, mark maxNode double black, then make the tree balance
		maxNode->key = maxLC->key;
		maxNode->pos = maxLC->pos;
		maxNode->right = NULL;
		maxNode->left = NULL;
		maxNode->color += maxLC->color;

		doubleBlack(maxNode);
		cout << "Delete succeed!" << endl;
		return true;
	}

	// if the node has neither left subtree nor right subtree
	else {

		// if node is root
		if (node == root) {
			delete root;
			root = new Node;
			cout << "Delete succeed!" << endl;
			return true;
		}

		// if node is not root, replace it with a leaf
		Node* newNode = new Node;
		Node* dad = node->father;

		if (node == dad->right) {
			dad->right = newNode;
			dad->right->father = dad;
		}
		else {
			dad->left = newNode;
			dad->left->father = dad;
		}

		// mark newNode->color
		newNode->color += node->color;
		delete node;
		doubleBlack(newNode);
		cout << "Delete succeed!" << endl;
		return true;
	}

}




bool RBTree::modify(int key, int value, Cache & cache){
    Node* node = fetch( key );

    if( node == NULL ){
        cout << "Error: key does not exits!" << endl;
        return false;
    }

	map<Node*, int>::iterator it;
	for( it = cache.addNode.begin(); it != cache.addNode.end(); ++it){
			if( it->first->key == key){
				cache.modifyNode[node] = it->second;
				cout << "Modify succeed!" << endl;
				return true;
        }
    }

	// node is not in cache, find the node in the tree
    Node* tempNode = this->root;
    int flag = 0;
    
    while(!flag){
        if( tempNode->key == key ){
			cache.modifyNode[tempNode] = value;
            return true;            
		}
		else if(tempNode->key > key){
            flag = ( tempNode->left == NULL || tempNode->left->pos == -1) ? 1 : 0;
            tempNode = (!flag) ? tempNode->left : tempNode;
        }
		else{
            flag = ( tempNode->right == NULL || tempNode->right->pos == -1) ? -1 : 0;
            tempNode = (!flag) ? tempNode->right : tempNode;
         }
    }
	cout << "Error: key does not exits!" << endl;
	return false;
}


Node* RBTree::fetch(int key){
    Node* tempNode = this->root;

    if(root == NULL){
        return NULL;
    }

    int flag = 0;

    while(!flag){
        if(tempNode->key == key){
            return tempNode;
        }else if(tempNode->key > key){
            flag = (tempNode->left == NULL) ? 1 : 0;
			tempNode = (flag) ? tempNode : tempNode->left;
        }else{
            flag = (tempNode->right == NULL) ? 1 : 0;
            tempNode = (flag) ? tempNode : tempNode->right;
        }
    }

    return NULL;
}


void RBTree::view(int key, Cache & cache){
	map<Node*, int>::iterator it;

	Node* node;

	for (it = cache.addNode.begin(); it != cache.addNode.end(); ++it) {
		if (it->first->key == key) {
			printSingle(it->first);
			return;
		}
	}

	for (it = cache.modifyNode.begin(); it != cache.modifyNode.end(); ++it) {
		if (it->first->key == key) {
			printSingle(it->first);
			return;
		}
	}

	node = fetch(key);
	printSingle(node);
}

//--------------------------------------------------

void totate(Node* & node, int dirction){
    /* zig-zag */
}

void balance(Node* node) {
	/* make the tree balance */
    cout << "Balance the tree" << endl;
}

//---------------------------------------------------

Node* RBTree::minNodeOf(Node* node){
	// return the Node* with smallest key in the subtree(with node as it's root)
	Node* curNode = node;
	Node* dad = node;
	while (curNode->pos != -1) {
		dad = curNode;
		curNode = curNode->left;
	}
	return dad;
}

Node* RBTree::maxNodeOf(Node* node){
	// return the Node* with the largest key in subtree(with node as it's root)
	Node* dad = node;
	Node* curNode = node;
	while (curNode->pos != -1) {
		dad = curNode;
		curNode = curNode->right;
	}
	return dad;
}

// new version:2017/07/21 22:31
void RBTree::doubleBlack(Node* & node) {
	if (node->color != BLACK_BLACK) {
		return;
	}

	if (node == root) {
		root->color = BLACK;
		return;
	}

	Node* dad = node->father;
	Node* bro = (node == dad->right) ? dad->left : dad->right;
	// Left Nephew and right Nephew
	Node* ln = bro->left;
	Node* rn = bro->right;

	// if node is left child
	if (node == dad->left) {

		// if nephew in the oppsite dirction is RED, zag and recolor, finish
		if (rn->color == RED) {
			rn->color = node->color = BLACK;
			if (dad->color == RED) {
				dad->color = BLACK;
				bro->color = RED;
			}
			zag(dad);
		}

		// if nephew in the same dirction is RED, zig-zag and recolor, finish
		else if (ln->color == RED) {
			if (dad->color == RED) {
				dad->color = BLACK;
				node->color = BLACK;
			}
			else {
				ln->color = node->color = BLACK;
			}
			zig(bro);
			zag(dad);
		}

		// if both nephew is BLACK
		else {

			// if bro is RED, zag to make bro BLACK
			if (bro->color == RED) {
				dad->color = RED;
				bro->color = BLACK;
			
				zag(dad);
			
				doubleBlack(node);
				// or doubleRed(dad);
			}

			// if bro is BLACK, push up BLACK level, check dad's new condition
			else {
				bro->color = RED;
				node->color = BLACK;
				dad->color += 1;
				doubleBlack(dad);
			}
		}
	}

	// if node is right chlid
	else {

		// if nephew in the oppsite dirction is RED, zig and recolor, finish
		if ((ln != NULL) && (ln->color == RED)) {
			ln->color = node->color = BLACK;
			if (dad->color == RED) {
				dad->color = BLACK;
				bro->color = RED;
			}
			zig(dad);
		}

		// if newphew in the same dirciton is RED, zag-zig and recolor, finish
		else if ((rn != NULL ) && (rn->color == RED)) {
			if (dad->color == RED) {
				dad->color = BLACK;
				node->color = BLACK;
			}
			else {
				rn->color = node->color = BLACK;
			}
			zag(bro);
			zig(dad);
		}

		// both nephew is BLACK
		else {

			// if bro is RED, zig and make node's bro BLACK
			if (bro->color == RED) {
				bro->color = BLACK;
				dad->color = RED;
				zig(dad);
				doubleBlack(node);
			}

			// bro is BLACK, push up BLACK level, check dad's new condition
			else {
				bro->color = RED;
				node->color = BLACK;
				dad->color += 1;
				doubleBlack(dad);
			}
		}
	}
}


void RBTree::zag(Node* & node){
    //zag
    //turn left

    //right child
    Node* rc = node->right;

    //left son of rc(left grandson)
    Node* lg = rc->left;

    if(node->father != NULL && node->father->pos != -1){
        Node* grandpa = node->father;

        if(node == grandpa->right){
            grandpa->right = rc;
			grandpa->right->father = grandpa;
        }else{
            grandpa->left = rc;
			grandpa->left->father = grandpa;
        }
    }
	else{
        //father is root
        root = rc;
        rc->father = new Node;
    }

	rc->left = node;
	rc->left->father = rc;

	node->right = lg;
	node->right->father = node;
    
	root->color = BLACK;

}

void RBTree::zig(Node* & node){
    //zig
    //turn right

    Node* grandpa = node->father;

	// left child
    Node* lc = node->left;
    
	// right grandson( right of lc)
    Node* rg = lc->right;

    if( (grandpa != NULL) && (grandpa->pos != -1) ){
        
        if(node == grandpa->right){
            grandpa->right = lc;
			grandpa->right->father = grandpa;
        }else{
            grandpa->left = lc;
			grandpa->left->father = grandpa;
        }
    }
	else{
		// node is root
        root = lc;
        lc->father = new Node;
    }

    node->left = rg;
	node->left->father = node;

	lc->right = node;
	lc->right->father = lc;

	root->color = BLACK;
}

int RBTree::totalNode() {
	if (root == NULL || root->pos == -1) {
		return 0;
	}
	
	return totalNode(root->left) + 1 + totalNode(root->right);
}

int RBTree::totalNode(Node* & node) {
	if (node == NULL || node->pos == -1) {
		return 0;
	}

	return totalNode(node->left) + 1 + totalNode(node->right);
}

bool RBTree::isBalance() {
	if (root == NULL || root->pos == -1) {
		return true;
	}
	queue<Node*> nodeWindowLeft;
	queue<Node*> nodeWindowRight;
	int leftTotal = 0;
	int rightTotal = 0;
	nodeWindowLeft.push(root->left);
	nodeWindowRight.push(root->right);

	while (nodeWindowLeft.size() != 0) {
		Node* top = nodeWindowLeft.front();
		nodeWindowLeft.pop();
		leftTotal += top->color;
		if (top->pos != -1) {
			nodeWindowLeft.push(top->left);
		}
	}
	while (nodeWindowRight.size() != 0) {
		Node* top = nodeWindowRight.front();
		nodeWindowRight.pop();
		rightTotal += top->color;
		if (top->pos != -1) {
			nodeWindowRight.push(top->left);
		}
	}
	return (leftTotal == rightTotal);
}

