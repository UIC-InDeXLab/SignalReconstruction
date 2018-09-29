using namespace std;
#include<iostream>

#include "Direct.h"



int main()
{
	Matrix A(3, 3);
	A.rows[0].push_back(Cell(1,2));
	A.rows[0].push_back(Cell(2, 1));
	A.rows[1].push_back(Cell(0, 1));
	A.rows[1].push_back(Cell(1, 1));
	A.rows[1].push_back(Cell(2, 2));
	A.rows[2].push_back(Cell(0, 2));
	A.rows[2].push_back(Cell(1, 1));
	A.rows[2].push_back(Cell(2, 1));
	float b[3] = {4,6,7};
	//float a[M][M] = { { 0, 2, 1, 4 },
	//{ 1, 1, 2, 6 },
	//{ 2, 1, 1, 7 } };

	// Order of Matrix(n) 
	int n = 3, flag = 0;

	// Performing Matrix transformation 
	float results[3];
	flag = Solve(A, b, results);


	cout << endl << "----Results------" << endl;
	for (int i = 0; i < 3; i++) cout << results[i] << ", ";


	cout << endl << "Done!" << endl;
	getchar();
	return 0;
}