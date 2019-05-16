// Abolfazl Asudeh; http://asueh.github.io

using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <ctime>
#include <fstream>
#include <iterator>
#include <cstring>

#include "GaussianElimination.h"
#include "LUDecomposition.h"

int main(int argc, char *argv[])
{
	int i;
	string folder = "data/861/";
	bool exact = true, startfromzero = true;
	int threshold = 2;
	string outputfile = "";

	if (argc > 1)
		for (i = 1; i < argc; i += 2)
		{
			if (!strcmp(argv[i], "-f")) // if argv[i] IS equal to "-f"
				folder = argv[i + 1];
			else if (!strcmp(argv[i], "-o"))
				outputfile = argv[i + 1];
			else if (!strcmp(argv[i], "-th"))
				threshold = stoi(argv[i + 1]);
			else if (!strcmp(argv[i], "-sz") && (!strcmp(argv[i + 1], "false") || !strcmp(argv[i + 1], "False") || !strcmp(argv[i + 1], "0")))
				startfromzero = false;
			else if (!strcmp(argv[i], "-e") && (!strcmp(argv[i + 1], "false") || !strcmp(argv[i + 1], "False") || !strcmp(argv[i + 1], "0")))
				exact = false;
		}
	cout << "about to read a" << endl;
	BMatrix A(folder + "a.txt", startfromzero); // for the small settings, we have the indices starting from 1
	cout << "read a" << endl;
	int n = A.n, m = A.m;
	if (threshold == -1)
		threshold = log(A.m);
	float* b = ReadVector(folder + "b.txt", n);
	cout << "read b" << endl;
	float* xp = ReadVector(folder + "xp.txt", m);
	cout << "read c" << endl;


    // Run the first few steps from the Direct Algorithm to generate AAT
	vector<pair<int,float> >* sig = new vector<pair<int, float> >[n];
	float* diameter = new float[n];
	Matrix t = AAT(A, exact, threshold);
	float* t2 = Sub(Mul(A, xp), b, n);
	float* tmp = new float[n];
    // Now do the comparisons
    cout<<"started GenerateSignature(..)"<<endl;
    clock_t begin = clock();
	GenerateSignature(t, sig, diameter);
    clock_t end = clock();
    int size1 = 0;
    for(i=0;i<n;i++) size1+=sig[i].size();
	double time1 = double(end - begin) / CLOCKS_PER_SEC;

    cout<<"started SolveBySigint(..)"<<endl;
    begin = clock();
	SolveBySigint(n, sig, diameter, t2, tmp);
    end = clock();
    double time2 = double(end - begin) / CLOCKS_PER_SEC;

    cout<<"started GenerateLUSig(..)"<<endl;  
    Matrix LUSig(n, n);  
    begin = clock();
    GenerateLUSig(t, LUSig);
    end = clock();
    int size2 = LUSig.size();
    double time3 = double(end - begin) / CLOCKS_PER_SEC;

    cout<<"started SolveByLUSig(..)"<<endl;  
    begin = clock();
    SolveByLUSig(n, LUSig, b, tmp);
    end = clock();
    double time4 = double(end - begin) / CLOCKS_PER_SEC;
    
	cout << n << ", " << m << ", " << exact <<endl;
    cout << "Sig. time to ge:" << time1 << ", time to solve:" << time2 <<", size:"<<size1<< endl;
    cout << "LUSig. time to ge:" << time3 << ", time to solve:" << time4 <<", size:"<<size2<< endl;

	//getchar();
	return 0;
}


