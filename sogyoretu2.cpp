//y=Axの疎行列Aの最適化のプログラム2
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
const int OYA = 2;
const int KO = 20;

struct CHILD {
	int val;      //評価値
	int iden[N];  //遺伝子
};

vector<CHILD> parent(OYA);   //親
vector<CHILD> child(KO);     //子孫。列番号を遺伝子とする
bool Visit[N];

//ファイルから読み込む
void input_matrix(double **a, FILE *fin, FILE *fout);

//行列のメモリ解放
void free_matrix(double **a);

//行列のメモリ確保
double **make_matrix();

void show(FILE *fout, double **a);  //見る
void sogyoretu(double **a);         //疎行列の処理

void init(double **a);           //初期化
void sentaku(double **a);        //選択
void kousa();                    //交叉
void heni();                     //突然変異
void idensi(int *a);             //列を遺伝子の形にする
int idensi2(int *a, int pt);     //遺伝子を列の形にする
int hyoka(double **a);           //評価関数
bool hikaku(const CHILD &a, const CHILD &b);  //sort関数で使う比較関数

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

	input_matrix(A, fin, fout);

	cout << hyoka(A) << endl;

	init(A);

	int count = 0;
	while (count <= 100) {
		sentaku(A);
		kousa();
		heni();
		count++;
	}

	sogyoretu(A);

	cout << hyoka(A) << endl;

	show(fout, A);

	free_matrix(A);

	return 0;
}

void sogyoretu(double **a)
{
	int *temp = new int[N];
	double **temp2 = make_matrix();

	for (int i = 0; i < N; i++) {
		temp[i] = i;
	}

	int i, j, pt, pt2;
	for (i = 0; i < N; i++) {
		pt = parent[0].iden[i];
		pt2 = idensi2(temp, pt);
		for (j = 0; j < N; j++) {
			temp2[j][i] = a[j][pt2];
		}
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			a[i][j] = temp2[i][j];
		}
	}

	delete[] temp;
	free_matrix(temp2);
}

void show(FILE *fout, double **a)
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fprintf(fout, "%lf", a[i][j]);
		}
		fprintf(fout, "\n");
	}
	fprintf(fout, "\n");
}

void input_matrix(double **a, FILE *fin, FILE *fout)
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

void init(double **a)
{
	srand((unsigned int)time(NULL));

	int pt, pt2;
	int i, j, k;
	int max = -10;
	int count = 0;

	int *temp = new int[N];


	//最初の親はプログラム1のやり方の様にすれば大きい値から始められる。
	for (i = 0; i < N; i++) {
		temp[i] = i;
	}

	/*列の0でない要素が多い順に左に寄せる。その子の遺伝子を一つだけ作る。
	そしてそれ以外はランダムに作る。*/
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (!Visit[j]) {
				for (k = 0; k < N; k++) {
					if (a[k][j] != 0) {
						count++;
					}
				}

				if (max <= count) {
					max = count;
					pt = j;
				}
				count = 0;
			}
		}
		child[KO - 1].iden[i] = temp[pt];
		Visit[pt] = true;
		idensi(temp);
		max = -10;
	}

	for (int i = 0; i < N; i++) {
		Visit[i] = false;
	}

	for (i = 0; i < N; i++) {
		temp[i] = i;
	}


	//ランダムに子を決める。
	for (i = 0; i < KO - 1; i++) {
		for (j = 0; j < N; j++) {
			do {
				pt = rand() % N;
			} while (Visit[pt]);
			Visit[pt] = true;
			child[i].iden[j] = temp[pt];
			idensi(temp);
		}
		for (int i = 0; i < N; i++) {
			Visit[i] = false;
			temp[i] = i;
		}
	}

	delete[] temp;
}

void sentaku(double **a)
{
	double **temp = make_matrix();
	int *temp2 = new int[N];

	for (int i = 0; i < N; i++) {
		temp2[i] = i;
	}

	//各遺伝子を評価値を計算
	int pt, pt2;
	for (int i = 0; i < KO; i++) {
		for (int j = 0; j < N; j++) {
			pt = child[i].iden[j];
			pt2 = idensi2(temp2, pt);
			for (int k = 0; k < N; k++) {
				temp[k][j] = a[k][pt2];
			}
		}

		child[i].val = hyoka(temp);
		for (int i = 0; i < N; i++) {
			Visit[i] = false;
			temp2[i] = i;
		}
	}

	sort(child.begin(), child.end(), hikaku);

	//評価値の上位2位を親に選択
	parent[0] = child[KO - 1];
	parent[1] = child[KO - 2];
	cout << parent[0].val << endl;
	
	delete[] temp2;
	free_matrix(temp);
}

//親から子を作る
void kousa()
{
	int *a = new int[N];
	double temp;

	//一様交叉
	for (int i = 0; i < KO - 3; i++) {
		for (int j = 0; j < N; j++) {
			a[j] = rand() % 2;
		}
		
		for (int j = 0; j < N; j++) {
			child[i].iden[j] = parent[0].iden[j];
			child[i + 1].iden[j] = parent[1].iden[j];
		}
		
		for (int j = 0; j < N; j++) {
			if (a[j] == 1) {
				child[i].iden[j] = parent[1].iden[j];
				child[i + 1].iden[j] = parent[0].iden[j];
			}
		}
	}
	
	delete[] a;
}

/*行の終わりから最初まで0が連続で続いた個数が多ければ
それだけ0でない値が右によってるから優れてると考える。すべての行の合計を足してリターンする*/
int hyoka(double **a)
{
	int count = 0;
	for (int i = 0; i < N; i++) {
		for (int j = N - 1; j >= 0; j--) {
			if (a[i][j] == 0) {
				count++;
			}
			else {
				break;
			}
		}
	}

	return count;
}

bool hikaku(const CHILD &a, const CHILD &b)
{
	if (a.val - b.val < 0) {
		return true;
	}
	
	return false;
}

void idensi(int *a)
{
	int k = 0;
	for (int i = 0; i < N; i++) {
		if (!Visit[i]) {
			a[i] = k;
			k++;
		}
	}
}

int idensi2(int *a, int pt) 
{
	int k = 0;
	for (int i = 0; i < N; i++) {
		if (!Visit[i]) {
			a[i] = k;
			k++;
		}
	}

	for (int i = 0; i < N; i++) {
		if (a[i] == pt && !Visit[i]) {
			Visit[i] = true;
			return i;
		}
	}
}

void heni()
{
}