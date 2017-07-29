#include "test.h"
#include <windows.h>

#define nrec 1000000
#define loopSize 10000

void roundTest() {
	RBTree tree;
	Cache cache;

	for (int i = 0; i < nrec; ++i) {
		tree.add(i, i, cache);
	}

	for (int i = 0; i < loopSize; ++i) {
		int key = rand() % nrec;
		tree.fetch(key);

		if (i % 37 == 0) {
			tree.remove(i, cache);
		}

		if (i % 11 == 0) {
			int newKey = rand() % nrec;
			tree.add(newKey, newKey, cache);
			tree.fetch(newKey);
		}

		if (i % 17 == 0) {
			tree.modify(key, key + 1, cache);
		}
	}
}