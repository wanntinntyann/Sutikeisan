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
const int ROW = N;  //�s��
const int COL = N;  //��

void input_matrix(double **a, char c, FILE *fin, FILE *fout);
void input_vector(double  *a, char c, FILE *fin, FILE *fout);

double **matrix_make(int row1, int row2, int col1, int col2);     //�s����쐬
double *vector_make(int i, int j);                                //�x�N�g�����쐬
void free_dvector(double *a, int i);                               //�x�N�g���̃��������
void free_dmatrix(double **arr, int row1, int row2, int col1, int col2);  //�s��̃��������

void gyoretu_init(double **arr, int row, int col);
void wa(double **a, double **b, double** c, int row1, int row2, int col1, int col2);
void seki(double **a, double **b, double **c, int row1, int row2, int col1, int col2, int nr, int nc);
void show(double **a, char c, int row, int col);

//LU����
void LU(double **a, int *p);

//LU�����ŉ���
void LU_solve(double **a, double *b, int *p);


int main()
{
	FILE *fin, *fout;
	int p[N];  //1�`N-1�܂ł𗘗p
	double **A = matrix_make(1, N, 1, N);
	double *b = vector_make(1, N);

	if (fopen_s(&fin, "input.txt", "r") != 0) {
		cout << "����܂���B" << endl;
	}

	if (fopen_s(&fout, "output.txt", "w") != 0) {
		cout << "���܂���B" << endl;
	}

	input_matrix(A, 'A', fin, fout);
	input_vector(b, 'b', fin, fout);

	LU(A, p);           //LU����
	LU_solve(A, b, p);  //LU������ɘA��������������

	fprintf(fout, "Ax=b�̉��͎��̒ʂ�ł��B\n");
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
	fprintf(fout, "�s��%c�͎��ł��B\n", c);

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
	fprintf(fout, "�x�N�g��%c�͎��ł��B\n", c);

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
	cout << "�s��" << c << endl;
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}

void LU(double **arr, int *p)
{
	double eps = pow(2, -50);
	double arufa, amax, temp;
	int ip;

	int i, j, k;
	for (i = 1; i <= N - 1; i++) {
		amax = abs(arr[i][i]);
		ip = i;
		
		for (j = i + 1; j <= N; j++) {
			if (abs(arr[j][i]) > amax) {
				amax = abs(arr[j][i]);
				ip = j;
			}
		}

		if (amax < eps) {
			cout << "���̍s��͐����łȂ�!" << endl;
		}

		p[i] = ip;

		//�s����
		if (ip != i) {
			for (j = i; j <= N; j++) {
				temp = arr[i][j];
				arr[i][j] = arr[ip][j];
				arr[ip][j] = temp;
			}
		}

		//�O�i����
		for (k = i + 1; k <= N; k++) {
			arufa = -arr[k][i] / arr[i][i];
			arr[k][i] = arufa;
			for (j = i + 1; j <= N; j++) {
				arr[k][j] += arr[i][j] * arufa;
			}
		}
	}
}

void LU_solve(double** arr, double *b, int *p)
{
	int i, j;
	double temp;
	for (i = 1; i <= N - 1; i++) {
		temp = b[i];
		b[i] = b[p[i]];
		b[p[i]] = temp;
		//�O�i���
		for (j = i + 1; j <= N; j++) {
			b[j] += arr[j][i] * b[i];
		}
	}

	//��ޑ��
	b[N] = b[N] / arr[N][N];
	for (i = N - 1; i >= 1; i--){
		temp = b[i];
		for (j = i + 1; j <= N; j++) {
			temp -= arr[i][j] * b[j];
		}
		b[i] = temp / arr[i][i];
	}
}