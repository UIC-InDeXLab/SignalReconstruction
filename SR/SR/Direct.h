using namespace std;
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <stack>

#include "GaussianElimination.h"

float * Direct(BMatrix A, float* b, float* xp, bool exact = true)
{
	int n = A.n, m = A.m;
//	float* x = new float[m];
	Matrix t = AAT(A, exact);
	t.print(true);
	float* t2 = Sub(Mul(A, xp), b, n);
	float* tmp = new float[n]; 
	// Solve system of linear equations: t*tmp = t2
	int flag = Solve(t, t2, tmp);
	return Sub(xp, Mul(Transpose(A), tmp), m);
}
