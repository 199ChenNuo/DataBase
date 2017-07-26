#ifndef TEST_H
#define TEST_H

#include "file.h"

//===================================
//------- unit test -----------------------------------------
void tempIndexTest();
//------------------- unit test for tree --------------------
void totalNodeTest0();
void totalNodeTest1();

void tree0();
void tree1();

void treeAdd0();
void treeAdd1();

void balanceTest0();
void balanceTest1();

void zig0();
void zag0();

void removeCase0();
void removeCase1();
void removeCase2();
void removeCase3();
void removeCase4();
void removeCase5();


void treeRemove0();
void treeRemove1();
void treeRemove2();



void treeFetch0();
void treeFetch1();

void treePrint0();
void treePrint1();

//------------------ unit test for file ----------------------
void fileTree0();

void indexFile0();

//--------------- unit test with file, node and tree -----
void fileAddNode0();
void fileAddNode1();

void fileFetchNode();

void fileViewNode1();

void fileDeleteNode();

//------ round test --------
void roundTest0();

void roundTest1();

//----- standard test ------
int standardTest();

#endif
