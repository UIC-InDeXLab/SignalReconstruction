using namespace std;
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <stack>

#include "GaussianElimination.h"

float * Direct(BMatrix A, float* b, float* xp, bool exact = true)
{
	int n = A.n, m = A.m, i;
	Matrix t = AAT(A, exact);
	//t.print(true);
	float* t2 = Sub(Mul(A, xp), b, n);
	float* tmp = new float[n]; 
	// Solve system of linear equations: t*tmp = t2
	int flag = Solve(t, t2, tmp);
	float* tmp2 = Mul(Transpose(A), tmp);
	return Sub(xp, Mul(Transpose(A), tmp), m);
}


/* Direct - Exact Unit Test
int main()
{
string folder = "data/sample/";
BMatrix A(folder + "a.txt");
int n = A.n, m = A.m;
float* b = ReadVector(folder + "b.txt", n);
float* xp = ReadVector(folder + "xp.txt", m);


float * x = Direct(A, b, xp);

cout << endl << "--------------- Result -------------" << endl;
for (int i = 0; i < m; i++)
cout << x[i] << ", ";
cout << endl << "Done!" << endl;
getchar();
return 0;
}
Output to compare with: 2.96589, 1.00147, 0.02, 1.00147, 1.03116, 0.0326316, 1.96589,
*/