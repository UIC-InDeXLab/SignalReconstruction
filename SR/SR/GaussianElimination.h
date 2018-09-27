// C++ Implementation for Gauss-Jordan, modified from https://www.geeksforgeeks.org/program-for-gauss-jordan-elimination-method/
// Elimination Method 
using namespace std;
#include<iostream>

#include "MyMatrix.h"

#define M 10 

// Function to print the matrix 
void PrintMatrix(float a[][M], int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= n; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
}

// function to reduce matrix to reduced 
// row echelon form. 
int PerformOperation(Matrix A, vector<float> b) // solves the equation Ax = b
{
	int n = A.n, i, j, k = 0, c, flag = 0, m = 0;
	float pro = 0;

	int* pointers = new int[n];
	for (i = 0; i < n; i++) pointers[i] = 0;

	// Performing elementary operations 
	for (i = 0; i < n; i++)
	{
		if (A.rows[i][pointers[i]].index > i /*i.e. A[i][i] == 0*/) // note that we use this function for inverse of AAT --> the diagonal is not zero, i.e. we don't need to worry about it :-)
		{
			c = 1;
			while (A.rows[i + c][pointers[i + c]].index>i && (i + c) < n)
			//while (a[i + c][i] == 0 && (i + c) < n)
				c++;
			if ((i + c) == n) {
				flag = 1;
				break;
			}
			for (j = i, k = 0; k <= n; k++)
				swap(a[j][k], a[j + c][k]);
		}

		for (j = 0; j < n; j++) {

			// Excluding all i == j 
			if (i != j) {

				// Converting Matrix to reduced row 
				// echelon form(diagonal matrix) 
				float pro = a[j][i] / a[i][i];

				for (k = 0; k <= n; k++)
					a[j][k] = a[j][k] - (a[i][k]) * pro;
			}
		}
	}
	return flag;
}

// Function to print the desired result  
// if unique solutions exists, otherwise  
// prints no solution or infinite solutions  
// depending upon the input given. 
void PrintResult(float a[][M], int n, int flag)
{
	cout << "Result is : ";

	if (flag == 2)
		cout << "Infinite Solutions Exists" << endl;
	else if (flag == 3)
		cout << "No Solution Exists" << endl;


	// Printing the solution by dividing constants by 
	// their respective diagonal elements 
	else {
		for (int i = 0; i < n; i++)
			cout << a[i][n] / a[i][i] << " ";
	}
}

// To check whether infinite solutions  
// exists or no solution exists 
int CheckConsistency(float a[][M], int n, int flag)
{
	int i, j;
	float sum;

	// flag == 2 for infinite solution 
	// flag == 3 for No solution 
	flag = 3;
	for (i = 0; i < n; i++)
	{
		sum = 0;
		for (j = 0; j < n; j++)
			sum = sum + a[i][j];
		if (sum == a[i][j])
			flag = 2;
	}
	return flag;
}
