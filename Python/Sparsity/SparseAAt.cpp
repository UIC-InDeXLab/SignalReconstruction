// Jees Augustine, https://github.com/jeesaugustine

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
        string folder = "45ke/1M/";
        bool exact = true, startfromzero = true;
        int threshold = -1;
        string outputfile = "output.txt";
        
	std::cout << folder << "\n";
	std::cout << outputfile << "\n";
	
	cout << "about to read a" << endl;
        BMatrix A(folder + "a.txt", startfromzero); // for the small settings, we have the indices starting fro    m 1
        cout << "read a" << endl;
        int n = A.n, m = A.m;
        if (threshold == -1)
               threshold = log(A.m);
        float* b = ReadVector(folder + "b.txt", n);
        cout << "read b" << endl;

        float* xp = ReadVector(folder + "xp.txt", m);
        cout << "read c" << endl;
 
        clock_t begin = clock();
        Matrix t = AAT(A, true, 0);
        t.print(false);

        t = AAT(A, false, 2);
        t.print(false);

        t = AAT(A, false, 3);
        t.print(false);

        t = AAT(A, false, 4);
        t.print(false);

        t = AAT(A, false, 5);
        t.print(false);

        t = AAT(A, false, 6);
        t.print(false);

        t = AAT(A, false, 7);
        t.print(false);

        t = AAT(A, false, 8);
        t.print(false);

        t = AAT(A, false, 9);
        t.print(false);
	//int w = 0;
        //for (int a = 0; a< y ; a++ ){
	//	for (int j = 0; j < z; j++){
	//		if (t[a][j] == 0)
	//			w++;
	//	}
	//}
	//cout << w << endl;
}
