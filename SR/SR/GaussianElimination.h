// Abolfazl Asudeh; http://asueh.github.io
// Gaussian Elimination method for solving Ax=b
// The code is a modification from https://www.geeksforgeeks.org/program-for-gauss-jordan-elimination-method/

using namespace std;
#include<iostream>

#include "MyMatrix.h"

int Solve(Matrix A, float* b, float* result) // solves the equation Ax = b
{
	int n = A.n, i, j, k = 0, kp = 0, c, flag = 0, m = 0;
	float pro = 0;
	int* pointers = new int[n];
	for (i = 0; i < n; i++) pointers[i] = 0;

	// Performing elementary operations 
	for (i = 0; i < n; i++)
	{
		if (A.rows[i][pointers[i]].index > i /*i.e. A[i][i] == 0*/) // note that we use this function for inverse of AAT --> the diagonal is not zero, i.e. we don't need to worry about it :-)
		{
			c = 1;
			while ((i + c) < n && A.rows[i + c][pointers[i + c]].index>i)
			//while (a[i + c][i] == 0 && (i + c) < n)
				c++;
			if ((i + c) == n) {
				flag = 1;
				break;
			}
			//for (j = i, k = 0; k <= n; k++)
			//	swap(a[j][k], a[j + c][k]);
			swap(A.rows[i], A.rows[i + c]);
			swap(b[i], b[i + c]);
		}

		result[i] = A.rows[i][pointers[i]].value;

		for (j = 0; j < n; j++) {
			// Excluding all i == j 
			if (i != j) {
				k = pointers[i]; kp = pointers[j];
				// Converting Matrix to reduced row 
				// echelon form(diagonal matrix)
				if (kp == A.rows[j].size() || A.rows[j][kp].index > i) continue; // A[j][i] is already zero
				// if A[j][i]!=0. Note: A.rows[j][kp].index cannot be less than i
				float pro = A.rows[j][kp].value / A.rows[i][k].value;

				// For all columns forward update the weights --> start from the pointers[j] and continue
				while (k < A.rows[i].size() && kp < A.rows[j].size())
					if (A.rows[i][k].index>A.rows[j][kp].index) kp++;
					else if (A.rows[i][k].index < A.rows[j][kp].index) k++;
					else
					{
						// a[j][k] = a[j][k] - (a[i][k]) * pro;
						A.rows[j][kp].value -= pro * A.rows[i][k].value;
						k++; kp++;
					}
					b[j] -= b[i] * pro;
					pointers[j]++;
			}
			pointers[i]++;
		}
	}

	for (int i = 0; i < n; i++)
			result[i] = b[i] / result[i];

	return flag;
}