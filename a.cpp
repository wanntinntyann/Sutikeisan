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

const int N = 4;
const int ROW = N;  //行数
const int COL = N;  //列数

void input_matrix(double **a, char c, FILE *fin, FILE *fout);
void input_vector(double  *a, char c, FILE *fin, FILE *fout);

double **matrix_make(int row1, int row2, int col1, int col2);     //行列を作成
double *vector_make(int i, int j);                                //ベクトルを作成
void free_dvector(double *a, int i);                               //ベクトルのメモリ解放
void free_dmatrix(double **arr, int row1, int row2, int col1, int col2);  //行列のメモリ解放

void gyoretu_init(double **arr, int row, int col);
void wa(double **a, double **b, double** c, int row1, int row2, int col1, int col2);
void seki(double **a, double **b, double **c, int row1, int row2, int col1, int col2, int nr, int nc);
void show(double **a, char c, int row, int col);

//ガウスの消去法
void gausu(double **a, double *b);


int main()
{
	FILE *fin, *fout;
	double **A = matrix_make(1, N, 1, N);
	double *b  = vector_make(1, N);

	if (fopen_s(&fin, "input.txt", "r") != 0) {
		cout << "ありません。" << endl;
	}

	if (fopen_s(&fout, "output.txt", "w") != 0) {
		cout << "作れません。" << endl;
	}

	input_matrix(A, 'A', fin, fout);
	input_vector(b, 'b', fin, fout);

	gausu(A, b);

	fprintf(fout, "Ax=bの解は次の通りです。\n");
	for (int i = 1; i <= N; i++) {
		fprintf(fout, "%lf\n", b[i]);
	}

	free_dmatrix(A, 1, N, 1, N);
	free_dvector(b, 1);
	fclose(fin);
	fclose(fout);

	return 0;
}

double *vector_make(int i, int j)
{
	double *vec = new double[j - i + 1];

	return (vec - i);
}

void free_dvector(double *a, int i)
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

	for (int i = 1; i <= ROW; i++) {
		fscanf_s(fin, "%lf", &a[i]);
		fprintf(fout, "%.2f\n", a[i]);
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

void gausu(double **arr, double *b)
{
	double arufa = 0.0, sum = 0.0;

	//前進消去
	int i, j, k;
	for (i = 1; i <= N - 1; i++) {
		for (j = i + 1; j <= N; j++) {
			arufa = -(arr[j][i] / arr[i][i]);
			for (k = i; k <= N; k++) {
				arr[j][k] += (arufa * arr[i][k]);
			}
			b[j] += (arufa * b[i]);
		}
	}

	//後退代入
	b[N] = b[N] / arr[N][N];
	for (int i = N - 1; i >= 1; i--) {
		sum = b[i];
		for (int j = i + 1; j <= N; j++) {
			sum -= arr[i][j] * b[j];
		}
		b[i] = sum / arr[i][i];
	}
}