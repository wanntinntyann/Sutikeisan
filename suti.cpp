#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>
using namespace std;

const int ROW = 3; //行数
const int COL = 4; //列数

void input_matrix(double **a, char c, FILE *fin, FILE *fout);
void input_vector(double  *a, char c, FILE *fin, FILE *fout);

double **matrix_make(int row1, int row2, int col1, int col2);     //行列を作成
double *vector_make(int i, int j);                                //ベクトルを作成
void free_vector(double *a, int i);                               //ベクトルのメモリ解放
void free_dmatrix(double **arr, int row1, int row2, int col1, int col2);  //行列のメモリ解放

void gyoretu_init(double **arr, int row, int col);
void wa(double **a, double **b, double** c, int row1, int row2, int col1, int col2); 
void seki(double **a, double **b, double **c, int row1, int row2, int col1, int col2, int nr, int nc);
void show(double **a, char c, int row, int col);

//ノルムの計算
double vector_norm1(double **a, int n1, int n2, int m1, int m2);
double vector_norm_max(double **a, int n1, int n2, int m1, int m2);

int main()
{
	FILE *fin, *fout;
	double **a;

	a = matrix_make(1, ROW, 1, COL);

	for (int i = 1; i <= ROW; i++) {
		for (int j = 1; j <= COL; j++) {
			a[i][j] = 2.0 * (i + j) * pow(-1.0, j);
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	
	cout << vector_norm1(a, 1, ROW, 1, COL) << endl;
	cout << vector_norm_max(a, 1, ROW, 1, COL) << endl;

	return 0;
}

double *vector_make(int i, int j)
{
	double *vec = new double[j - i + 1];

	return (vec - i);
}

void free_vector(double *a, int i)
{
	delete[](a + i);
}

double **matrix_make(int row1, int row2, int col1, int col2)
{
	double **arr;
	int nrow = row2 - row1 + 1;
	int ncol = col2 - col1 + 1;

	arr = new double*[nrow];

	arr = arr - row1;

	for (int i = row1; i <= row2; i++) {
		arr[i] = new double[ncol];
	}

	for (int i = row1; i <= row2; i++) {
		arr[i] = arr[i] - col1;
	}

	return arr;
}

void free_dmatrix(double **arr, int row1, int row2, int col1, int col2)
{
	for (int i = row1; i <= row2; i++) {
		delete[](arr[i] + col1);
	}

	delete[](arr + row1);
}

void input_matrix(double **a, char c, FILE *fin, FILE *fout)
{
	fprintf(fout, "行列%cは次です。\n", c);

	for (int i = 1; i <= ROW; i++) {
		for (int j = 1; j <= COL; j++) {
			fscanf_s(fin, "%lf", &a[i][j]);
			fprintf(fout, "%5.2f", a[i][j]);
		}
		fprintf(fout, "\n");
	}
}

void input_vector(double *a, char c, FILE *fin, FILE *fout)
{
	fprintf(fout, "ベクトル%cは次です。\n", c);

	for (int i = 0; i < ROW; i++) {
		fscanf_s(fin, "%lf", &a[i]);
		fprintf(fout, "%5.2f", a[i]);
	}
	fprintf(fout, "\n");
}

void gyoretu_init(double **arr, int row, int col)
{
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			arr[i][j] = 2.0 * (i + j);
		}
	}
}

void wa(double **a, double **b, double **c, int row1, int row2, int col1, int col2)
{
	for (int i = row1; i <= row1; i++) {
		for (int j = col1; j <= col1; j++) {
			c[i][j] = a[i][j] + b[i][j];
		}
	}
}

void seki(double **a, double **b, double **c, int row1, int row2, int col1, int col2, int nr, int nc)
{
	for (int i = row1; i <= nr; i++) {
		for (int j = col1; j <= nc; j++) {
			c[i][j] = 0;
			for (int k = col1; k <= col2; k++) {
				c[i][j] += a[j][k] * b[k][i];
				cout << c[i][j] << endl;
			}
		}
	}
}

void show(double **a, char c, int row, int col)
{
	cout << "行列" << c << endl;
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}

double vector_norm1(double **a, int n1, int n2, int m1, int m2)
{
	double *temp;

	temp = vector_make(m1, m2);

	for (int i = m1; i <= m2; i++) {
		temp[i] = 0.0;
		for (int j = n1; j <= n2; j++) {
			temp[i] += abs(a[j][i]);
		}
	}

	sort(temp + m1, temp + m2 + m1);

	double norm = temp[m2];
	
	delete[](temp + m1);

	return norm;
}

double vector_norm_max(double **a, int n1, int n2, int m1, int m2)
{
	double *temp;

	temp = vector_make(n1, n2);

	for (int i = n1; i <= n2; i++) {
		temp[i] = 0.0;
		for (int j = m1; j <= m2; j++) {
			temp[i] += abs(a[i][j]);
		}
	}

	sort(temp + n1, temp + n2 + n1);

	double norm = temp[n2];

	delete[](temp + n1);

	return norm;
}