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
#include <cmath>

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
	for (int i = 0; i < len && ss; i++)
	{
		if (!getline(ss, s, ',')) break;
		output[i] = stof(s);
	}
	return output;
}

Matrix AAT(BMatrix A, bool exact = true, float th = 0)
{
	if (!exact) return AAT_approx(A, th);
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

Matrix AAT_approx(BMatrix A, float th)
{
	int n = A.n,i,j,k,kp;
	Matrix t(n, n);
	vector<int> validIndices;
	for (i = 0; i < n; i++)
		if (A.rows[i].size() < th) t.rows[i].push_back(Cell(i, A.rows[i].size()));
		else
			validIndices.push_back(i);
	for (i = 0; i < validIndices.size(); i++)
	{
		k = validIndices[i];
		t.rows[k].push_back(Cell(k, A.rows[k].size()));
		for (j = i + 1; j < validIndices.size(); j++)
		{
			kp = validIndices[j];
			float v = SIM(A.rows[k], A.rows[j], th, log(A.m), A.m);
			if (!v) continue;
			t.rows[k].push_back(Cell(kp, v));
			t.rows[kp].push_back(Cell(k, v));
		}
	}
	return t;
}


float SIM(vector<int>& a, vector<int>& b,float th, float k /*switch threshold*/, int m)
{
	int i, j, k,k1,k2,hk; float tmp;
	if (a.size() < k || b.size() < k) // apply threshold-based
	{
		tmp = 0; k1 = 0; k2 = 0;
		while (k1 < a.size() && k2 < b.size())
		{
			if (a[k1] < b[k2]) k1++;
			else if (a[k1] > b[k2]) k2++;
			else{ tmp++; k1++; k2++;}
		}
		return tmp;
	}
	tmp = 0; k1 = 0; k2 = 0;
	while (k1 < k && k2 < k)
	{
		if (a[k1] < b[k2]) k1++;
		else if (a[k1] > b[k2]) k2++;
		else{ tmp++; k1++; k2++; }
	}
	k1 = 0; k2 = 0;
	for(i=0;i<k;i++)
		if (a[k1] < b[k2]) { hk = a[k1]; k1++; }
		else if (a[k1] > b[k2]) { hk = b[k2]; k2++; }
		else { hk = b[k2]; k1++;  k2++;}
	return (tmp / k)*((k - 1) / hk)*m;
}

























































