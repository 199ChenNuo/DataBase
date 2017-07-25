#include "test.h"
#include <time.h>


int main() {
	time_t startTime, finishTime;

	startTime = clock();
	
	totalNodeTest1();

	finishTime = clock();
	cout << "Time: " << double(finishTime - startTime) << "ms." << endl;
	
	system("pause");
	return 0;
}