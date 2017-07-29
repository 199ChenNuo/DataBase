#ifndef TEST_H
#define TEST_H

#include <time.h>
#include <windows.h>
#include "file.h"

//===================================
//===================================
//------- unit test -----------------------------------------
void tempIndexTest();

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

void fileTree0();

void indexFile0();

void fileAddNode();
void fileFetchNode();

void fileViewNode();
void fileDeleteNode();


//==============================
//==============================
//---- performance ----
void fetchPerformance();
void performance0();
void performance1();
//-------correct test---------
void correctTest();
//------ abnormal test ------
void abnormalTest();
// ----round test ----------
void roundTest();


// this is not test!!!
// this is not test!!!
// this is not test!!!

//=====================================
//---------TestTime.cpp------------------------------------
// this function is write to get the time cost of setting tree
void setTreeTime();
//balance time
void balanceTimeTest();
// time cost use different cache size
void cacheTime();

#endif
