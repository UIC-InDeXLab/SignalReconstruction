// Abolfazl Asudeh; http://asueh.github.io
// LU Decomposition for solving Ax=b

using namespace std;
#include<iostream>
#include "MyMatrix.h"



void GenerateLUSig(Matrix A, Matrix& LU) // Generates the signature matrix for solving Ax = b
{
	// Sig matrix is the transpose of what proposed in the paper
	int n = A.n, m = A.m;
    //lu = new double[n, n];
    LU = Matrix(n,n);
    float sum = 0.;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            sum = 0;
            for (int k = 0; k < i; k++)
                sum += LU.GetValue(i, k) * LU.GetValue(k, j);
            LU.SetValue(i, j, A.GetValue(i, j) - sum);
        }
        for (int j = i + 1; j < n; j++)
        {
            sum = 0;
            for (int k = 0; k < i; k++)
                sum += LU.GetValue(j, k) * LU.GetValue(k, i);
            LU.SetValue(j, i, (1 / LU.GetValue(i, i)) * (A.GetValue(j, i) - sum));
        }
    }
}

void SolveByLUSig(int n, Matrix lu, float* b, float* result)
{
    float* y = new float[n];
    float sum=0.;
    for (int i = 0; i < n; i++)
    {
        sum = 0;
        for (int k = 0; k < i; k++)
            sum += lu.GetValue(i, k) * y[k];
        y[i] = b[i] - sum;
    }
    // find solution of Ux = y
    for (int i = n - 1; i >= 0; i--)
    {
        sum = 0;
        for (int k = i + 1; k < n; k++)
            sum += lu.GetValue(i, k) * result[k];
        result[i] = (1 / lu.GetValue(i, i)) * (y[i] - sum);
    }
//    return result;
}


/*
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
//The result should be 2.2, 1.4, 1.2
*/
