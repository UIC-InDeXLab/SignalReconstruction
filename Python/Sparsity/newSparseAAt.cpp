// Jees Augustine, https://github.com/jeesaugustine

using namespace std;
#include <iostream>
#include <ctime>
#include <fstream>
#include <iterator>
#include <cstring>
#include <math.h> 
 
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

	cout << n << endl ;
	cout << m << endl ;

        cout << floor(log2(m)) << endl;

        int l = floor(log2(m));
        Matrix t = AAT(A, false, l);
	cout << t.n << endl;
	cout << t.m << endl;
        t.print(false);

}
