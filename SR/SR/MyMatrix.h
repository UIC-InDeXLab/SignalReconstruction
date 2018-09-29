using namespace std;
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>

class Cell
{
public:
	int index;
	float value;
	Cell(int i, float v)
	{
		index = i;
		value = v;
	}
};


class BMatrix // Binary Sparse Matrix
{
public:
	int n; // number of rows
	int m; // number of columns
	vector<int>* rows;
	BMatrix(int number_of_rows, int number_of_columns)
	{
		n = number_of_rows;
		m = number_of_columns;
		rows = new vector<int>[n];
	}
	BMatrix(int number_of_rows, int number_of_columns, string filename)
	{
		n = number_of_rows;
		m = number_of_columns;
		rows = new vector<int>[n];
		ReadFile(filename);
	}
	void ReadFile(string filename)
	{
		vector <vector <string> > data;
		ifstream infile(filename.c_str());
		int i = 0;
		while (infile)
		{
			string s;
			if (!getline(infile, s)) break;
			istringstream ss(s);
			vector <string> record;

			while (ss)
			{
				string s;
				if (!getline(ss, s, ',')) break;
				rows[i].push_back(stoi(s));
				//record.push_back(s);
			}
			//data.push_back(record);
		}
		if (!infile.eof())
		{
			cerr << "Fooey!\n";
		}
	}
};

class Matrix
{
public:
	int n; // number of rows
	int m; // number of columns
	vector<Cell>* rows; // the non-zero cells in each row
	Matrix(int number_of_rows, int number_of_columns)
	{
		n = number_of_rows;
		m = number_of_columns;
		rows = new vector<Cell>[n];
	}
	void print()
	{
		int i, j, k;
		cout << endl << "---------- A ------------" << endl;
		for(i = 0; i < n; i++)
		{
			k = 0;
			for (j = 0; j < m; j++)
				if (k == rows[i].size() || rows[i][k].index > j) cout << "0, ";
				else
				{
					cout << rows[i][k].value << ", ";
					k++;
				}
			cout << endl;
		}
		cout << "----------------------" << endl;
	}
};

Matrix AAT(BMatrix A, bool exact=true)
{
	int n = A.n;
	Matrix t(n, n);
	for (int i = 0; i < n; i++)
	{
		t.rows[i].push_back(Cell(i, A.rows[i].size()));
		for (int j = i + 1; i < n; j++)
		{
			float tmp = 0; int k1 = 0, k2 = 0;
			while (k1 < A.rows[i].size() && k2 < A.rows[j].size())
			{
				if (A.rows[i][k1] < A.rows[j][k2]) k1++;
				else if (A.rows[i][k1] > A.rows[j][k2]) k2++;
				else{ tmp++; k1++; k2++;}
			}
			t.rows[i].push_back(Cell(i, tmp)); 
			t.rows[j].push_back(Cell(j, tmp));
		}
	}
	return t;
}

vector<float> Mul(BMatrix A, vector<float> b)
{
	if (b.size() != A.m) { cerr << "Error: The vector length should be the same as the matrix columns!\n"; exit;}
	int n = A.n;
	vector<float> output;
	for (int i = 0; i < n; i++)
	{
		float tmp = 0;
		for (int j = 0; j < A.rows[i].size(); i++) tmp += b[A.rows[i][j]];
		output.push_back(tmp);
	}
	return output;
}

BMatrix Transpose(BMatrix A)
{
	BMatrix At(A.m, A.n);
	for (int i = 0; i < A.n; i++)
		for (int j = 0; j < A.rows[i].size(); j++)
			At.rows[j].push_back(i);
	return At;
}

vector<float> Sub(vector<float> A, vector<float> B)
{
	if (A.size() != B.size()) {cerr << "Error: the vectors should have equal sizes"; exit;}
	for (int i = 0; i < A.size(); i++) A[i] -= B[i];
	return A;
}








