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

#define SIZE_TO_UPDATE 20

class RBTree{
public:
    //------------------------

    //RBTree(string & indexFileName);
    //construct RBTree from index file

    //void setTreeFile(string & indexFileName);
    //construct index file from tree

    //void newDataFile(string & dataFileName);
    //open data file and put new information in

    //void newIndexFile(string & indexFileName);
    //open index file and put new information in

    RBTree();

    RBTree(int key, int value);

    //-----------------------------


    //RBTree treeFromFile(string & indexFileName, string & dataFileName);
    //RBTree treeFromFile(string & dataFileName);
    //-----------------------------

    //map<Node* node, int value> modifyNode---nodes that were recently modified
   // map<Node*, int> modifyNode;

    //map<int key, int pos> deleteNode---nodes that were recently deleted
   // map<int, int> deleteNode;

    //map<Node* node, int value> addNode---nodes that were recentlt added,
    // notice that position of new nodes should first check deleteNode
   // map<Node*, int> addNode;
    //----------------------------

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

    void print();

    void print(Node*  node);

    void print(int key);

	void printSingle(Node* node);

    //-----------------------------------

    bool add(int key, int value, Cache & cache);
    //bool add(string & line);
    //bool add(string & nodePos, int nodeKey, int dataPos, int nodeColor);

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
