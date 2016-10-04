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

class FILE_MAIN {
protected:
	FILE* fin;
	FILE* fout;
	FILE* fout2;
	FILE* fout3;
public:
	FILE_MAIN();
	~FILE_MAIN();
};


class FILE_Sub : public FILE_MAIN {
public:
	void input_matrix(double **a, int n);
	void output_matrix(double **a, int n);
};


//行列操作クラス
class MATRIX {
private:
	double **mat;
	int *vec;
	int Num;
public:
	MATRIX(int n);
	~MATRIX();
	void sogyoretu(double **a);
	void retu(double**a);
	int renketu(double **a, int x);
};

//メモリアクセス回数の計算クラス
class KEISAN {
private:
	double wari;
	vector<int> group;
public:
	int akusesu_keisan(double **a);         //普通のアクセスの回数計算
	int akusesu2_keisan(double **a);        //普通じゃない方のアクセスの回数計算
	void group_kazoeru(double **a);         //連続で続いてる数を数える
};

int main()
{
	return 0;
}

FILE_MAIN::FILE_MAIN()
{
	if(fopen_s(&fin, "mat800x800.txt", "r") != 0) {
		exit(1);
	}

	if (fopen_s(&fout, "output.txt", "w") != 0) {
		exit(1);
	}

	if (fopen_s(&fout2, "output2.txt", "w") != 0) {
		exit(1);
	}

	if (fopen_s(&fout3, "output3.csv", "w") != 0) {
		exit(1);
	}
}

FILE_MAIN::~FILE_MAIN()
{
	fclose(fin);
	fclose(fout);
	fclose(fout2);
	fclose(fout3);
}

void FILE_Sub::input_matrix(double **a, int n)
{
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fscanf_s(fin, "%lf", a[i][j]);
		}
	}
}

void FILE_Sub::output_matrix(double **a, int n)
{
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fprintf(fout, "%lf", a[i][j]);
		}
		fprintf(fout, "\n");
	}
	fprintf(fout, "\n");
}

void MATRIX::sogyoretu(double **a)
{
	retu(a);
}

void MATRIX::retu(double **a)
{
	//交換の前と後の列の比較に使う変数
	int before, after;

	double val; //列の要素を交換するときに使う
	int t = 0;  //交換した列を記憶する

	int i = 0, j = 0, k = 0;
	for (i = 0; i < Num; i++) {
		for (j = i; j < Num; j++) {
			if (i != j) {

				before = renketu(a, j) + renketu(a, i);

				//列を交換
				for (k = 0; k < Num; k++) {
					val = a[k][i];
					a[k][i] = a[k][j];
					a[k][j] = val;
				}

				after = renketu(a, j) + renketu(a, i);
				t = vec[i];
				vec[i] = vec[j];
				vec[j] = t;
				//もし列を交換した後、逆に値が小さくなってたら元に戻す
				if (after < before) {
					for (k = 0; k < Num; k++) {
						val = a[k][i];
						a[k][i] = a[k][j];
						a[k][j] = val;
					}
					t = vec[i];
					vec[i] = vec[j];
					vec[j] = t;
				}
			}
		}
	}
}

int MATRIX::renketu(double **a, int x)
{
	int val = 0;
	int k;
	for (k = 0; k < Num; k++) {
		if (a[k][x] != 0) {
			if (a[k][x + 1] != 0) {
				val++;
			}
			if (x - 1 >= 0) {
				if (a[k][x - 1] != 0) {
					val++;
				}
			}
		}
	}

	return val;
}

MATRIX::MATRIX(int n)
{
	Num = n;

	vec = new int[n];

	mat = new double*[n];

	for (int i = 0; i < n; i++) {
		mat[i] = new double[n];
	}
}

MATRIX::~MATRIX()
{
	for (int i = 0; i < Num; i++) {
		delete mat[i];
	}

	delete[] mat;
	delete[] vec;
}