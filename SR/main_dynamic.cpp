// Abolfazl Asudeh; http://asueh.github.io

using namespace std;
#include <iostream>
#include <ctime>
#include <fstream>
#include <iterator>
#include <cstring>

#include "Direct.h"


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
	startfromzero = false; // DELETE THIS!!!!
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
	//float * x = Direct(A, b, xp, exact, threshold);
	float* x = Dynamic_Direct(A, b, xp, exact, threshold);
	clock_t end = clock();
	double t2, t1 = double(end - begin) / CLOCKS_PER_SEC;
	begin = clock();
	x = Dynamic_Update(A, b, xp, exact, threshold);
	end = clock();
	t2 = double(end - begin) / CLOCKS_PER_SEC;
	cout << n << ", " << m << ", " << exact << ", " << t1 << ", " << t2 << endl;

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

/* unit test for the dynamic setting
int main()
{
Matrix A(3, 3);
A.rows[0].push_back(Cell(1, 2));
A.rows[0].push_back(Cell(2, 1));
A.rows[1].push_back(Cell(0, 1));
A.rows[1].push_back(Cell(1, 1));
A.rows[1].push_back(Cell(2, 2));
A.rows[2].push_back(Cell(0, 2));
A.rows[2].push_back(Cell(1, 1));
A.rows[2].push_back(Cell(2, 1));
float b[3] = { 4, 6, 7 };
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

// generate the signature matrix
vector<pair<int, float> >* sig = new vector<pair<int, float> >[A.n];
float* diameter = new float[A.n];
GenerateSignature(A, sig, diameter);
SolveBySigint(A.n, sig, diameter, b, results);
cout << endl << "----Results------" << endl;
for (int i = 0; i < 3; i++) cout << results[i] << ", ";
cout << endl << "Done!" << endl;
getchar();
return 0;
}
*/