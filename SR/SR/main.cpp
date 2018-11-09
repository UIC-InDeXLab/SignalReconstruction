using namespace std;
#include<iostream>

#include "Direct.h"



int main()
{
	string folder = "data/sd_631_edge_226/";
	BMatrix A(folder + "a.csv");
	int n = A.n, m = A.m;
	float* b = ReadVector(folder + "b.csv", n);
	float* xp = ReadVector(folder + "xp.csv", m);
	
	/*float * x = Direct(A, b, xp);
	cout << endl << "--------------- Result-E -------------" << endl;
	for (int i = 0; i < m; i++)
		cout << x[i] << ", ";
	cout << endl << "Done!" << endl;*/
	
	float * x2 = Direct(A, b, xp, false,6);
	cout << endl << "--------------- Result-A -------------" << endl;
	for (int i = 0; i < m; i++)
		//if (!std::isnan(x2[i]))
			cout << x2[i] << ", ";
	cout << endl << "Done!" << endl;

	getchar();
	return 0;
}