//y=Axの行列Aを最適化するプログラム1
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

const int N = 20;
int x[N];  //交換した列を記憶

//2度目の列移動の範囲
int hani_start[N];
int hani_end[N];

double wari; //0でない数の割合
int akusesu; //メモリにアクセスする回数
vector<int> group;  //連続で続いている0でない数字が何個連続しているかを記憶する


//ファイルから読み込む
void input_matrix(double **a, char c, FILE *fin, FILE *fout);

//メモリ解放
void free_matrix(double **a);

//行列、ベクトルのメモリ取得
double **make_matrix();

void init(double **a, FILE *fout, int kakuritu);
void show(FILE *fout, double **a);  //見る
void sogyoretu(double **a);         //疎行列全体の処理
void retu(double **a);              //列交換
void retu_sita(double **a, int x);  //2度目の列交換
double hyoka(double **a);		    //評価関数

int akusesu_keisan(double **a);     //普通のアクセスの回数計算
int akusesu2_keisan(double **a);    //普通じゃい方のアクセスの回数計算
void group_kazoeru(double **a);     //連続で続いてる数を数える

int main()
{
	FILE *fin, *fout, *fout2, *fout3;
	/*
	if (fopen_s(&fin, "mat800x800.txt", "r") != 0) {
	cout << "読み込めません。" << endl;
	exit(1);
	}
	*/
	if (fopen_s(&fout, "output.txt", "w") != 0) {
		cout << "作成できません。" << endl;
		exit(1);
	}

	if (fopen_s(&fout2, "output2.txt", "w") != 0) {
		cout << "作成できません。" << endl;
		exit(1);
	}

	if (fopen_s(&fout3, "output3.ods", "w") != 0) {
		cout << "作成できません。" << endl;
		exit(1);
	}

	double **A = make_matrix();

	//input_matrix(A, 'A', fin, fout);


//	for (int i = 1; i <= 10; i++) {
		init(A, fout3, 10);

		//処理する前の行列を書き出す
		show(fout, A);

		cout << hyoka(A) << endl;

		sogyoretu(A);

		//処理が終わった後の疎行列を書き出す
		show(fout2, A);

		group_kazoeru(A);

		cout << hyoka(A) << endl;

		cout << wari << endl;
	//}

	free_matrix(A);

	return 0;
}

void show(FILE *fout, double **a)
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%.0f ", a[i][j]);
			fprintf(fout, "%.0f", a[i][j]);
		}
		printf("\n");
		fprintf(fout, "\n");
	}
	printf("\n");
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

void init(double **a, FILE *fout, int kakuritu)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < N; i++) {
		x[i] = i;
	}

	int val;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			val = rand() % 100;
			if (val >= kakuritu) {
				a[i][j] = 0;
			}
			else {
				a[i][j] = 1;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (a[i][j] != 0) {
				wari++;
			}
		}
	}

	wari /= (N * N);
	fprintf(fout, "%lf\n", wari);
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
				t = x[j];
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

	int i, j, k;
	for (i = p + 1; i < N; i++) {
		for (j = count; j < hani_end[p]; j++) {
			if (a[i][j] != 0) {
				for (k = 0; k < N; k++) {
					val = a[k][count];
					a[k][count] = a[k][j];
					a[k][j] = val;
				}
				int t = x[j];
				x[j] = x[count];
				x[count] = t;
				if (count >= hani_end[p] - 1) {
					break;
				}
				count++;
			}
		}
	}
}

//普通にアクセスした場合のアクセス回数計算
int akusesu_keisan(double **a)
{
	int val = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (a[i][j] != 0) {
				val += 3;
			}
		}
	}

	return val;
}

//普通じゃない方法アクセスした場合のアクセス回数計算
int akusesu2_keisan(double **a)
{
	int val = 0;
	int num = 0;
	bool flag = false;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (a[i][j] != 0 && a[i][j + 1] != 0) {
				val += 2;
			}
			else {
			}
		}
	}

	return val;
}

void group_kazoeru(double **a)
{
	int kazu = 0;
	int i, j, k;

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (a[i][j] != 0) {
				kazu++;
				for (k = j + 1; k < N; k++) {
					if (a[i][k] == 0) {
						break;
					}
					kazu++;
				}
				group.push_back(kazu);
				kazu = 0;
				j = k;
			}
		}
	}

	int num = group.size();

	for (int i = 0; i < num; i++) {
		cout << group[i] << " ";
	}
	cout << endl;
}