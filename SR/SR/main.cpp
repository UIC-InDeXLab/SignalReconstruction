using namespace std;
#include<iostream>

#include "Direct.h"



int main()
{
	string folder = "data/sample/";
	BMatrix A(folder + "a.txt");
	int n = A.n, m = A.m;
	float* b = ReadVector(folder + "b.txt", n);
	float* xp = ReadVector(folder + "xp.txt", m);
	
	float * x = Direct(A, b, xp,false);

	cout << endl << "--------------- Result -------------" << endl;
	for (int i = 0; i < m; i++)
		cout << x[i] << ", ";
	cout << endl << "Done!" << endl;
	getchar();
	return 0;
}