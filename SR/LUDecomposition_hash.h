// Abolfazl Asudeh; http://asueh.github.io
// LU Decomposition for solving Ax=b

using namespace std;
#include<iostream>
#include<unordered_map>
#include<vector>

#ifndef MyMatrix
#define MyMatrix
#include "MyMatrix.h"
#endif

float GetValue(unordered_map<int,float> row, int index)
{
    if(row.find(index) == row.end()) return 0;
    return row[index];
}

void SetValue(unordered_map<int,float> row, int index, int value)
{
    row[index] = value;
}

unordered_map<int,float>* GenerateLUSig(Matrix A) // Generates the signature matrix for solving Ax = b
{
	// Sig matrix is the transpose of what proposed in the paper
	int n = A.n, m = A.m;

    unordered_map<int,float>* LU = new unordered_map<int,float>[n];

    float sum = 0.;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            sum = 0;
            for (int k = 0; k < i; k++)
                sum += GetValue(LU[i], k) * GetValue(LU[k], j);
            SetValue(LU[i], j, A.GetValue(i, j) - sum);
        }
        for (int j = i + 1; j < n; j++)
        {
            sum = 0;
            for (int k = 0; k < i; k++)
                sum += GetValue(LU[j], k) * GetValue(LU[k], i);
            SetValue(LU[j], i, (1 / GetValue(LU[i], i)) * (A.GetValue(j, i) - sum));
        }
    }

    return LU;
}

float* SolveByLUSig(int n, unordered_map<int,float>* LU, float* b)
{
    float* y = new float[n];
    float sum=0.;
    float* result = new float[n];
    for (int i = 0; i < n; i++)
    {
        sum = 0;
        for (int k = 0; k < i; k++)
            sum += GetValue(LU[i], k) * y[k];
        y[i] = b[i] - sum;
    }
    // find solution of Ux = y
    for (int i = n - 1; i >= 0; i--)
    {
        sum = 0;
        for (int k = i + 1; k < n; k++)
            sum += GetValue(LU[i], k) * result[k];
        result[i] = (1 / GetValue(LU[i], i)) * (y[i] - sum);
    }
    return result;
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

// generate the LU signature matrix
Matrix LUSig(3, 3);
GenerateLUSig(A, LUSig);
SolveByLUSig(n, LUSig, b, results);
cout << endl << "----Results------" << endl;
for (int i = 0; i < 3; i++) cout << results[i] << ", ";
cout << endl << "Done!" << endl;
//getchar();
return 0;
}
//The result should be 2.2, 1.4, 1.2
*/
