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
 
	cout << n << endl;
	cout << m << endl;

        Matrix t = AAT(A, true, 0);
        t.print(false);

        Matrix t1 = AAT(A, false, 2);
        t1.print(false);

        Matrix t2 = AAT(A, false, 3);
        t2.print(false);

        Matrix t3 = AAT(A, false, 4);
        t3.print(false);

        Matrix t4 = AAT(A, false, 5);
        t4.print(false);

        Matrix t5 = AAT(A, false, 6);
        t5.print(false);

        Matrix t6 = AAT(A, false, 7);
        t6.print(false);

        Matrix t7 = AAT(A, false, 8);
        t7.print(false);

        Matrix t8 = AAT(A, false, 9);
        t8.print(false);
}
