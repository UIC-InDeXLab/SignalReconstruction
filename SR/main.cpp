// Abolfazl Asudeh; http://asueh.github.io

using namespace std;
#include <iostream>
#include <ctime>
#include <fstream>
#include <iterator>
#include <cstring>

#include "Direct.h"


//#ifndef LUDecomposition
//#define LUDecomposition
#include "LUDecomposition_hash.h"
//#endif


/*
int main(int argc, char *argv[])
{
	int i;
	string folder = "data/861/";
	bool exact = true, startfromzero = true;
	int threshold = -1;
	string outputfile = "";

	if (argc > 1)
		for (i = 1; i < argc;i+=2)
		{
			if (!strcmp(argv[i],"-f")) // if argv[i] IS equal to "-f"
				folder = argv[i + 1];
			else if (!strcmp(argv[i], "-o"))
				outputfile = argv[i + 1];
			else if (!strcmp(argv[i], "-th"))
				threshold = stoi(argv[i + 1]);
			else if (!strcmp(argv[i], "-sz") && (!strcmp(argv[i + 1], "false") || !strcmp(argv[i + 1], "False") || !strcmp(argv[i + 1], "0")))
				startfromzero = false;
			else if (!strcmp(argv[i], "-e") && (!strcmp(argv[i + 1], "true") || !strcmp(argv[i + 1], "True") || !strcmp(argv[i + 1], "1")))
				exact = true;
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

	clock_t begin = clock();
	float * x = Direct(A, b, xp,exact,threshold);
	clock_t end = clock();
	double time = double(end - begin) / CLOCKS_PER_SEC;
	cout << n << ", " << m << ", " << exact << ", " << time << endl;

	if (outputfile != "")
	{
		ofstream myfile;
		myfile.open(folder + outputfile, ios_base::trunc);
		for (int i = 0; i < m; i++)
			myfile << x[i] << ", ";
		myfile.close();
	}

	//getchar();
	return 0;
}
*/

/*
// Use this for test
int main(int argc, char *argv[])
{
	string folder = "data/sd_631_edge_226/";
	BMatrix A(folder + "a.csv");
	int n = A.n, m = A.m;
	float* b = ReadVector(folder + "b.csv", n);
	float* xp = ReadVector(folder + "xp.csv", m);
	
	float * x = Direct(A, b, xp);
	cout << endl << "--------------- Result-E -------------" << endl;
	for (int i = 0; i < m; i++)
		cout << x[i] << ", ";
	cout << endl << "Done!" << endl;
	
	float * x2 = Direct(A, b, xp, false,6);
	cout << endl << "--------------- Result-A -------------" << endl;
	for (int i = 0; i < m; i++)
		//if (!std::isnan(x2[i]))
			cout << x2[i] << ", ";
	cout << endl << "Done!" << endl;

	getchar();
	return 0;
}
*/

// ------------------ Unit Test ------------------
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

// generate the LU signature matrix
unordered_map<int,float>* LUSig = GenerateLUSig(A);
float* results2 = SolveByLUSig(n, LUSig, b);
cout << endl << "----Results------" << endl;
for (int i = 0; i < 3; i++) cout << results2[i] << ", ";
cout << endl << "Done!" << endl;
//getchar();
return 0;
}
//The result should be 2.2, 1.4, 1.2