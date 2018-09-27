using namespace std;
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <stack>

#include "GaussianElimination.h"
//#include "MyMatrix.h"

vector<float> Direct(BMatrix A, vector<float> b, vector<float> xp, bool exact = true)
{
	vector<float> x;
	Matrix t = AAT(A, exact);
	vector<float> t2 = Sub(Mul(A, xp),b);
	vector<float> tmp; // Solve system of linear equations: t*tmp = t2
	return Sub(xp, Mul(Transpose(A), tmp));
}
