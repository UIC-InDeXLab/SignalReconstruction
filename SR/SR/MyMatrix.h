// Abolfazl Asudeh, http://asudeh.github.io

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
	BMatrix(string filename)
	{
		vector <vector <string> > data;
		ifstream infile(filename.c_str());
		int i = 0, first_line = 1;
		while (infile)
		{
			string s;
			if (!getline(infile, s)) break;
			istringstream ss(s);
			if (first_line)
			{
				first_line = 0;
				getline(ss, s, ',');
				n = stoi(s);
				getline(ss, s, ',');
				m = stoi(s);
				rows = new vector<int>[n];
				continue;
			}
			vector <string> record;
			while (ss)
			{
				if (!getline(ss, s, ',')) break;
				rows[i].push_back(stoi(s));
				//record.push_back(s);
			}
			//data.push_back(record);
			i++;
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
	void print(bool printSparse=false)
	{
		int i, j, k;
		cout << endl << "---------- A ------------" << endl;
		if (!printSparse)
		{
			for (i = 0; i < n; i++)
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
		}
		else
		{
			for (i = 0; i < n; i++)
			{
				for (j = 0; j < rows[i].size(); j++)
					cout << rows[i][j].index << ":" << rows[i][j].value << "; ";
				cout << endl;
			}
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
		for (int j = i + 1; j < n; j++)
		{
			float tmp = 0; int k1 = 0, k2 = 0;
			while (k1 < A.rows[i].size() && k2 < A.rows[j].size())
			{
				if (A.rows[i][k1] < A.rows[j][k2]) k1++;
				else if (A.rows[i][k1] > A.rows[j][k2]) k2++;
				else{ tmp++; k1++; k2++;}
			}
			if (tmp)
			{
				t.rows[i].push_back(Cell(j, tmp));
				t.rows[j].push_back(Cell(i, tmp));
			}
		}
	}
	return t;
}

float* Mul(BMatrix A, float* b)
{
	// if (b.size() != A.m) { cerr << "Error: The vector length should be the same as the matrix columns!\n"; exit;}
	int n = A.n;
	float * output = new float[n];
	for (int i = 0; i < n; i++)
	{
		output[i] = 0;
		for (int j = 0; j < A.rows[i].size(); j++) output[i] += b[A.rows[i][j]];
	}
	return output;
}

BMatrix Transpose(BMatrix A)
{
	BMatrix At(A.m, A.n);
	for (int i = 0; i < A.n; i++)
		for (int j = 0; j < A.rows[i].size(); j++)
			At.rows[A.rows[i][j]].push_back(i);
	return At;
}

float* Sub(float* A, float* B, int size)
{
	float* output = new float[size];
	//if (A.size() != B.size()) {cerr << "Error: the vectors should have equal sizes"; exit;}
	for (int i = 0; i < size; i++) output[i] = A[i] - B[i];
	return output;
}

float* ReadVector(string filename, int len)
{
	float* output = new float[len];
	ifstream infile(filename.c_str());
	string s;
	getline(infile, s);
	istringstream ss(s);
	for (int i = 0; i < len && ss;i++)
	{
		if (!getline(ss, s, ',')) break;
		output[i] = stof(s);
	}
	return output;
}






