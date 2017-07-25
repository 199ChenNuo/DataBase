#ifndef NODE_H
#define NODE_H

#define RED 0
#define BLACK 1
#define BLACK_BLACK 2

class Node {
public:
	Node();

	Node(int key, int pos);

	int key;
	int pos;
	int color;
	int height;

	Node* father;
	Node* right;
	Node* left;

};


#endif