using namespace std;
#include <iostream>
#include <ctime>
#include <fstream>
#include <iterator>

#include "Direct.h"

int main(int argc, char *argv[])
{
	int i;
	string folder = "data/sd_631_edge_226/";
	bool exact = false;
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
			else if (!strcmp(argv[i], "-e") && (!strcmp(argv[i + 1], "true") || !strcmp(argv[i + 1], "True") || !strcmp(argv[i + 1], "1")))
				exact = true;
		}

	BMatrix A(folder + "a.csv");
	int n = A.n, m = A.m;
	if (threshold == -1)
		threshold = log(A.m);
	float* b = ReadVector(folder + "b.csv", n);
	float* xp = ReadVector(folder + "xp.csv", m);

	clock_t begin = clock();
	float * x = Direct(A, b, xp,exact,threshold);
	clock_t end = clock();
	double time = double(end - begin) / CLOCKS_PER_SEC;
	cout << endl << n << ", " << m << ", " << exact << ", " << time;

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


/* Use this for test
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