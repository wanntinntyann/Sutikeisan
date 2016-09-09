#include <iostream>
#include <cmath>
#include <ctime>
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

int x[N];  //交換した列を記憶

//ファイルから読み込む
void input_matrix(double **a, char c, FILE *fin, FILE *fout);

//メモリ解放
void free_matrix(double **a);

//行列、ベクトルのメモリ取得
double **make_matrix();

void init();
void show(FILE *fout, double **a);

void sogyoretu(double **a);    //疎行列全体の処理
void retu(double **a);         //列交換

//評価関数
int hyoka(double **a);

int main()
{
	FILE *fin, *fout;

	if (fopen_s(&fin, "input.txt", "r") != 0) {
		cout << "読み込めません。" << endl;
		exit(1);
	}

	if (fopen_s(&fout, "output.txt", "w") != 0) {
		cout << "作成できません。" << endl;
		exit(1);
	}

	double **A = make_matrix();

	input_matrix(A, 'A', fin, fout);

	init();

	int before = hyoka(A);

	cout << before << endl;

	sogyoretu(A);

	int after = hyoka(A);

	cout << after << endl;

	show(fout, A);

	free_matrix(A);

	return 0;
}

void sogyoretu(double **a)
{
	retu(a);
}

void retu(double **a)
{
	int max = -10;
	int count = 0;

	int pt;
	int i, j, k;
	for (i = 0; i < N - 1; i++) {
		for (j = i; j < N; j++) {
			for (k = 0; k < N; k++) {
				if (a[k][j] != 0) {
					count++;
				}
			}

			if (max < count) {
				max = count;
				pt = j;
			}
			count = 0;
		}
		if (i != pt) {
			int t;
			double temp;
			for (int l = 0; l < N; l++) {
				temp = a[l][i];
				a[l][i] = a[l][pt];
				a[l][pt] = temp;
			}
			t = x[i];
			x[i] = x[pt];
			x[pt] = t;
		}
		max = -10;
	}
}

void show(FILE *fout, double **a)
{
	fprintf(fout, "変形後の行列A\n");

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fprintf(fout, "%5.2f", a[i][j]);
		}
		fprintf(fout, "\n");
	}

	fprintf(fout, "\n\n");


	fprintf(fout, "変形後の変形前の列の位置\n");
	for (int i = 0; i < N; i++) {
		fprintf(fout, "%d ", x[i]);
	}
}

void input_matrix(double **a, char c, FILE *fin, FILE *fout)
{
	fprintf(fout, "行列%cは次です。\n", c);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fscanf_s(fin, "%lf", &a[i][j]);
			fprintf(fout, "%5.2f", a[i][j]);
		}
		fprintf(fout, "\n");
	}
	fprintf(fout, "\n");
}

void input_vector(double *a, char c, FILE *fin, FILE *fout)
{
	fprintf(fout, "ベクトル%cは次です。\n", c);

	for (int i = 0; i < N; i++) {
		fscanf_s(fin, "%lf", &a[i]);
		fprintf(fout, "%5.2f\n", a[i]);
	}
	fprintf(fout, "\n");
}

double **make_matrix()
{
	double **a;

	a = new double*[N];

	for (int i = 0; i < N; i++) {
		a[i] = new double[N];
	}

	return a;
}

void free_matrix(double **a)
{
	for (int i = 0; i < N; i++) {
		delete[] a[i];
	}

	delete[] a;
}

void init()
{
	for (int i = 0; i < N; i++) {
		x[i] = i;
	}
}

/*行の終わりから最初までの0が連続で続いた個数が多ければ
それだけ0でない値が右によってると考えられる。すべての行の合計を足してリターンする*/
int hyoka(double **a)
{
	int count = 0;
	for (int i = 0; i < N; i++) {
		for (int j = N - 1; j >= 0; j--){
			if (a[i][j] == 0) {
				count++;
			} else{
				break;
			}
		}
	}

	return count;
}