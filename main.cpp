#include "test.h"
#include <windows.h>


int main() {

	LARGE_INTEGER nFreq;
	LARGE_INTEGER t1;
	LARGE_INTEGER t2;
	double dt;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);

	standardTest();

	QueryPerformanceCounter(&t2);
	dt = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;

	cout << "time cost: " << dt << "s." << endl;

	system("pause");

	return 0;
}