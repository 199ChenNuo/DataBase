#ifndef RBTREE_H
#define RBTREE_H

#define LEFT 0
#define RIGHT 1

#define MaxLen = 8


#include "Cache.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>



class RBTree{
public:
    //------------------------

    RBTree();

    RBTree(int key, int value);

	void clear();

    //-----------------------------


	int totalNode();
	int totalNode(Node* & node);

	bool isBalance();

    Node* getRoot();

    int getHeight();

    int getLastPos();

    //-----------------------------

	void setRoot(Node* & newRoot);

    void setHeight(int newHeight);

    void setLastPos(int newPos);

    //-----------------------------------

    void print(Cache & cache);

    void print(Node*  node, Cache & cache);

    void print(int key, Cache & cache);

	void printSingle(Node* node, Cache & cache);

    //-----------------------------------

    bool add(int key, int value, Cache & cache);

    bool remove(int key, Cache & cache);
    void doubleBlack(Node* & node);
    void doubleRed(Node* & node);

    bool modify(int key ,int value, Cache & cache);

    Node* fetch(int key);

    void view(int key, Cache & cache);

    //--------------------------------------

	void zig(Node* & node);

	void zag(Node* & node);

    //--------------------------------------

    Node* minNodeOf(Node* node);

    Node* maxNodeOf(Node* node);

private:
    Node* root;
    int height;
    int lastPos;
};



#endif
