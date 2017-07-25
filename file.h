#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include "RBTree.h"




//=========================================================================
//----------------------- function for node ----------------------

// see value from a input key
void viewNode(fstream & dataFile, RBTree & tree, Cache & cache);

// get data value from data file according to node->pos
int viewValue(fstream & dataFile, int pos);

// add node into tree, if cache filled, update data file
void addNode(fstream & dataFile, RBTree & tree, Cache & cache);

// modify node, if cache filled, update data file
void modifyNode(fstream & dataFile, RBTree & tree, Cache & cache);

// delete node, if cache filled, update data file
void deleteNode(fstream & dataFile, RBTree & tree, Cache & cache);

//==========================================================================
//----------------------- function for file -----------------------

// open data file and initialize tree
void getFile(fstream & dataFile, RBTree & tree, Cache & cache);

// get file name
string getFileName();

// update data file
void updateFile(fstream & dataFile, Cache & cache);
void fileDeleteNode(fstream & dataFile, int pos);
void fileModifyNode(fstream & dataFile, int pos, int value);
void fileAddNode(fstream & dataFile, int pos, int value);

// close data file(after update data file)
void closeFile(fstream & dataFile, string & indexFileName, RBTree & tree, Cache & cache);

//=============================================================================
//----------------------- function for tree ------------------------------
    
// set tree from input index file
// if the data file has no index file, set tree from the data file
void treeFromFile(RBTree & tree, fstream & dataFile, string & indexFileName, Cache & cache);

// add node from information get from index file
void indexAddNode(RBTree & tree, string & nodePos, int dataKey, int dataPos, int nodeColor);

// after set tree, set index file for futrue need
void setIndexFile(RBTree & tree, string & indexFileName);

// the data file has no index file
// set the tree from raw data
void treeFromData(RBTree & tree, fstream & dataFile, Cache & cache);

#endif