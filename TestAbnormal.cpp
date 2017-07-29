#include "test.h"

void abnormalTest() {
	RBTree tree; 
	Cache cache;

	for (int i = 0; i < 10000; ++i) {
		tree.add(i, i, cache);
	}

	for (int i = 10000; i < 20000; ++i) {

		tree.add(i, i, cache);
		if (tree.fetch(i)->pos != i) {
			cout << "Error0!" << endl;
			system("pause");
		}

		tree.remove(i, cache);
		if (tree.fetch(i) != NULL) {
			cout << "Error1!" << endl;
				system("pause");
		}

		if (tree.modify(i, i, cache)) {
			cout << "Error2!" << endl;
			system("pause");
		}

		tree.add(i, i + 1, cache);
		if (tree.fetch(i) == NULL) {
			cout << "Error3!" << endl;
			system("pause");
		}
	}
}