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

const int N = 300;
int x[N];   //交換した列を記憶

//2度目の列移動の範囲
int hani_start[N];
int hani_end[N];

double wari; //0でない数の割合
vector<int> group;  //連続で続いている0でない数字が何個連続しているかを記憶する

//ファイルから読み込む
void input_matrix(double **a, char c, FILE *fin, FILE *fout);

//メモリ解放
void free_matrix(double **a);

//行列、ベクトルのメモリ取得
double **make_matrix();

void init(double **a, FILE *fout, int kakuritu);
void show(FILE *fout, double **a);           //見る
void sogyoretu(double **a);                  //疎行列全体の処理
void retu(double **a, int hasi, int hasi2, int seigen, int l);  //列交換
double hyoka(double **a);		             //評価関数

int akusesu_keisan(double **a);        //普通のアクセスの回数計算
int akusesu2_keisan(double **a);       //普通じゃない方のアクセスの回数計算
void group_kazoeru(double **a);        //連続で続いてる数を数える

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
	
	if (fopen_s(&fout3, "output3.csv", "w") != 0) {
		cout << "作成できません。" << endl;
		exit(1);
	}

	double **A = make_matrix();

	//input_matrix(A, 'A', fin, fout);
	fprintf(fout3, "x,y1,y2\n");
	for (int i = 1; i <= 100; i++) {
		int akusesu;
		init(A, fout3, i);

		fprintf(fout3, "%lf,", wari);
		printf("%lf,", wari);

		akusesu = akusesu_keisan(A);
		fprintf(fout3, "%d,", akusesu);
		printf("%d,", akusesu);

		//処理する前の行列を書き出す
		//show(fout, A);

		sogyoretu(A);
		akusesu = akusesu2_keisan(A);
		fprintf(fout3, "%d\n", akusesu);
		printf("%d\n", akusesu);

		//処理が終わった後の疎行列を書き出す
		//show(fout2, A);
	}

	free_matrix(A);
	fclose(fout);
	fclose(fout2);
	fclose(fout3);

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

	fprintf(fout, "\n");

	for (int i = 0; i < N; i++) {
		fprintf(fout, "%d ", x[i]);
	}
	fprintf(fout, "\n");
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

	//動的配列を空にする
	group.clear();

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
	retu(a, 0, N, 10, 0);
}

void retu(double **a, int hasi, int hasi2, int seigen, int l)
{
	int *temp = new int[N];
	int count = hasi;
	double val;
	int t = 0;
	int i = 0, j = 0, k = 0;

	int next = 0;
	if (abs(hasi - hasi2) >= seigen && l < N) {
		for (i = l; i < N; i++) {
			next = count;
			for (j = count; j < hasi2; j++) {
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
			retu(a, next, count, seigen, l + 1);
		}
	}
	else {
		return;
	}

	delete[] temp;
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
	group_kazoeru(a);

	int val = 0;
	int val2 = 0;
	
	int size = group.size();

	val = size * 2;

	for (int i = 0; i < size; i++) {
		val2 += group[i];
	}

	val2 = val2 * 2 + val;

	return val2;
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
}
