#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include "RBTree.h"


//===================================================================
//--------- check if a data file is opened --------------------------
bool haveOpenedFile();


//=========================================================================
//----------------------- function for node ----------------------

// see value from a input key
void viewNode(RBTree & tree, Cache & cache);

// get data value from data file
int viewValue(int pos);

// add node into tree, if cache filled, update data file
void addNode(RBTree & tree, Cache & cache);

// modify node, if cache filled, update data file
void modifyNode(RBTree & tree, Cache & cache);

// delete node, if cache filled, update data file
void deleteNode(RBTree & tree, Cache & cache);

//==========================================================================
//----------------------- function for file -----------------------

// open data file and initialize tree
void getFile(RBTree & tree, Cache & cache);

// get file name
void getFileName();

// update data file
void updateFile(Cache & cache);
void fileModifyNode(int pos, int value);
void fileAddNode(int pos, int key, int value);

//=============================================================================
//----------------------- function for tree ------------------------------
    
// set tree from input index file
// if the data file has no index file, set tree from the data file
void treeFromFile(RBTree & tree, Cache & cache);

// the data file has no index file
// set the tree from raw data, then set index file
void treeFromData(RBTree & tree, Cache & cache);


// add node from information get from index file
void indexAddNode(RBTree & tree, string nodePos, int dataKey, int dataPos, int nodeColor, int curLevel);


// after set tree, set index file for futrue need
void setIndexFile(RBTree & tree);


//==============================================================================
//----------------------- check input ------------------------------------------
bool isNum(string & str);


#endif