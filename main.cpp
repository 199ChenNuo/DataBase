#include "test.h"
#include <time.h>


int main() {
	time_t startTime, finishTime;

	startTime = clock();;
	roundTest0();
	finishTime = clock();

	cout << "total time cost:" << double(finishTime - startTime) << "ms." << endl;

	system("pause");

	return 0;
}