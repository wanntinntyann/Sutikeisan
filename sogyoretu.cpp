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
const int N = 800;
int x[N];  //交換した列を記憶

//2度目の列移動の範囲
int hani_start[N];
int hani_end[N]; 

//ファイルから読み込む
void input_matrix(double **a, char c, FILE *fin, FILE *fout);

//メモリ解放
void free_matrix(double **a);

//行列、ベクトルのメモリ取得
double **make_matrix();

void init();
void show(FILE *fout, double **a);  //見る
void sogyoretu(double **a);         //疎行列全体の処理
void retu(double **a);              //列交換
void retu_sita(double **a, int x);         //また列交換

//評価関数
double hyoka(double **a);

int main()
{
	FILE *fin, *fout;
	if (fopen_s(&fin, "mat800x800.txt", "r") != 0) {
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

	double before = hyoka(A);

	cout << before << endl;

	sogyoretu(A);

	double after = hyoka(A);

	cout << after << endl;

	show(fout, A);

	free_matrix(A);

	return 0;
}

void show(FILE *fout, double **a)
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fprintf(fout, "%.0f", a[i][j]);
		}
		fprintf(fout, "\n");
	}
	fprintf(fout, "\n\n");

	for (int i = 0; i < N; i++) {
		fprintf(fout, "%d ", x[i]);
	}
}

void input_matrix(double **a, char c, FILE *fin, FILE *fout)
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fscanf_s(fin, "%lf", &a[i][j]);
		}
	}
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
double hyoka(double **a)
{
	double value = 1;
	double keisu = 1.0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - 1; j++) {
			if (a[i][j] != 0) {
				value += keisu * a[i][j];
				if (a[i][j + 1] != 0) {
					keisu += 1.0;
			
				}
			}
			else {
				//もし途中で0になったら係数を1.0に戻す。
				keisu = 1.0;
			}
		}
	}

	return value;
}

void sogyoretu(double **a)
{
	retu(a);
	for (int i = 0; i < N; i++) {
		retu_sita(a, i);
	}
}

void retu(double **a)
{
	int *temp = new int[N];
	int count = 0;
	double val;
	int t = 0;
	int i = 0, j = 0, k = 0;

	for (i = 0; i < N; i++) {
		hani_start[i] = t;
		for (j = count; j < N; j++) {
			if (a[i][j] != 0) {
				for (k = 0; k < N; k++) {
					val = a[k][count];
					a[k][count] = a[k][j];
					a[k][j] = val;
				}
				int t = x[j];
				x[j] = x[count];
				x[count] = t;
				if (count >= N - 1) {
					break;
				}
				count++;
			}
		}
		hani_end[i] = count;
		t = hani_end[i];
	}

	delete[] temp;
}

void retu_sita(double **a, int p)
{
	double val;
	int count = hani_start[p];

	for (int i = 0; i < N; i++) {
		for (int j = hani_start[p]; j < hani_end[p]; j++) {
			if (a[i][j] != 0) {
				for (int k = 0; k < N; k++) {
					val = a[k][count];
					a[k][count] = a[k][j];
					a[k][j] = val;
				}
				int t = x[j];
				x[j] = x[count];
				x[count] = t;
				if (count >= hani_end[i] - 1) {
					break;
				}
				count++;
			}
		}
		count = hani_start[p];
	}
}