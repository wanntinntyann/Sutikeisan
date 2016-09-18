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

const int N = 100;
const int OYA = 2;
const int KO = 20;
int x[N];  //動かした列を記憶

struct CHILD {
	int val;      //評価値
	int iden[N];  //遺伝子
};

vector<CHILD> parent(OYA);   //親
vector<CHILD> child(KO);     //子孫。列番号を遺伝子とする
vector<int> group;      //1が連続で続いてるグループについて
double wari;            //1の割合
bool Visit[N];

//ファイルから読み込む
void input_matrix(double **a, FILE *fin, FILE *fout);

//行列のメモリ解放
void free_matrix(double **a);

//行列のメモリ確保
double **make_matrix();

void show(FILE *fout, double **a);    //見る
void sogyoretu(double **a);           //疎行列の処理

void init(double **a, int kakuritu);  //初期化
void sentaku(double **a);             //選択
void kousa();                         //交叉
void heni();                          //突然変異
void idensi(int *a);                  //列を遺伝子の形にする
int idensi2(int *a, int pt);          //遺伝子を列の形にする
int hyoka(double **a);             //評価関数
bool hikaku(const CHILD &a, const CHILD &b);  //sort関数で使う比較関数

int akusesu_keisan(double **a);         //普通のアクセスの回数計算
int akusesu2_keisan(double **a);        //普通じゃない方のアクセスの回数計算
void group_kazoeru(double **a);         //連続で続いてる数を数える


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

	//input_matrix(A, fin, fout);

	for (int i = 1; i <= 100; i++) {
		init(A, i);
		//show(fout, A);

		printf("%lf,", wari);
		printf("%d,", akusesu_keisan(A));

		int count = 0;
		while (count <= 40) {
			sentaku(A);
			kousa();
			heni();
			count++;
		}
		sogyoretu(A);

		for (int i = 0; i < N; i++) {
			Visit[i] = false;
		}

		printf("%d\n", akusesu2_keisan(A));
	}

	free_matrix(A);
	fclose(fout);
	fclose(fout2);
	fclose(fout3);

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
		x[i] = pt2;
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
			printf("%.0f", a[i][j]);
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

void init(double **a, int kakuritu)
{
	srand((unsigned int)time(NULL));

	//動的配列を空にする
	group.clear();

	for (int i = 0; i < N; i++) {
		x[i] = i;
	}

	int index;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			index = rand() % 100;
			if (index >= kakuritu) {
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
	int *temp = new int[N];
	int i, j, k;
	int count = 0;
	double val;

	for (int i = 0; i < N; i++) {
		x[i] = i;
		temp[i] = i;
	}

	int pt;
	count = 0;

	//先に決めた子以外はランダムに決める。
	for (i = 0; i < KO; i++) {
		for (j = 0; j < N; j++) {
			do {
				pt = rand() % N;
			} while (Visit[pt]);
			Visit[pt] = true;
			child[i].iden[j] = temp[pt];
			idensi(temp);
		}
		for (k = 0; k < N; k++) {
			Visit[k] = false;
			temp[k] = k;
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

	//各遺伝子の評価値を計算
	int pt, pt2;
	for (int i = 0; i < KO; i++) {
		for (int j = 0; j < N; j++) {
			//遺伝子からもとの列の形に戻す
			pt = child[i].iden[j];
			pt2 = idensi2(temp2, pt);
			for (int k = 0; k < N; k++) {
				temp[k][j] = a[k][pt2];
			}
		}
		child[i].val = hyoka(temp);
		group.clear();
		for (int i = 0; i < N; i++) {
			Visit[i] = false;
			temp2[i] = i;
		}
	}

	sort(child.begin(), child.end(), hikaku);


	parent[0] = child[0];

	//int choose = rand() % (KO - 13);
	parent[1] = child[1];

	delete[] temp2;
	free_matrix(temp);
}

//親から子を作る
void kousa()
{
	int *a = new int[N];

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

/*連続ならそれだけ詰まってるので連続してたら
係数を大きくしいき評価値が大きくなるようにする*/
int hyoka(double **a)
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

	return group.size();
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

	return 0;
}

void heni()
{
	//ランダムで子を選んだ遺伝子を変化させる
	int kakuritu, choose;

	kakuritu = rand() % 100;

	if (kakuritu >= 5) {
		choose = rand() % KO;
		child[choose].iden[2] = 1;
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