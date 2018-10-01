using namespace std;
#include<iostream>

#include "Direct.h"



int main()
{
	string folder = "data/sd_631_edge_226/";
	BMatrix A(folder + "a_631.csv");
	int n = A.n, m = A.m;
	float* b = new float[n];
	float* xp = new float[m];
	ReadVector(folder + "b.csv", n);
	ReadVector(folder + "gravity.csv", m);

	float * x = Direct(A, b, xp);

	cout << endl << "--------------- Result -------------" << endl;
	for (int i = 0; i < m; i++)
		cout << x[i] << ", ";
	cout << endl << "Done!" << endl;
	getchar();
	return 0;
}