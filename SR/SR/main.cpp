using namespace std;
#include<iostream>

#include "Direct.h"



int main()
{
	float a[M][M] = { { 0, 2, 1, 4 },
	{ 1, 1, 2, 6 },
	{ 2, 1, 1, 7 } };

	// Order of Matrix(n) 
	int n = 3, flag = 0;

	// Performing Matrix transformation 
	flag = PerformOperation(a, n);

	if (flag == 1)
		flag = CheckConsistency(a, n, flag);

	// Printing Final Matrix 
	cout << "Final Augumented Matrix is : " << endl;
	PrintMatrix(a, n);
	cout << endl;

	// Printing Solutions(if exist) 
	PrintResult(a, n, flag);


	cout << "Done!" << endl;
	getchar();
	return 0;
}