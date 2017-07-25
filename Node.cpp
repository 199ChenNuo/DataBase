#include "Node.h"
#include <iostream>

using namespace std;

Node::Node(){
    father = new Node(-1, -1); 
	right = new Node(-1, -1); 
	left = new Node(-1, -1);
	right->father = left->father = this;
	father->right = father->left = this;
    color = BLACK;
    key = -1;
    pos = -1;
	height = 0;
}

Node::Node(int key, int pos){
    if(pos == -1){
        father = right = left = NULL;
    }else{
        father = new Node(-1, -1); 
		right = new Node(-1, -1); 
		left = new Node(-1, -1);
		right->father = left->father = this;
		father->right = father->left = this;
    }
   
    color = BLACK;
	height = 0;
    this->key = key;
    this->pos = pos;
}


//----------------------------------------------------------------------

