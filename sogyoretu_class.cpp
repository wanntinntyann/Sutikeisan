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

//ベクトルと行列のクラス
class MAT_VEC {
protected:
	double **mat;
	int *vec;
	int Num;
public:
	MAT_VEC(const int n = 0);
	~MAT_VEC();
	double **Get_mat();
	int *Get_vec();
	int Get();
	void show();
};

class FILE_MAIN{
protected:
	FILE* fin;
	FILE* fout;
	FILE* fout2;
	FILE* fout3;
public:
	void Open_file();
	~FILE_MAIN();
};


class FILE_Sub : public FILE_MAIN {
public:
	void input_matrix(double **mat, int n);
	void output_matrix(double **mat, int n);
};


//行列操作クラス
class MATRIX : public MAT_VEC{
public:
	MATRIX(int n) : MAT_VEC(n) {};
	void sogyoretu();
	void retu();;
	int renketu(int x);
};

//メモリアクセス回数の計算クラス
class KEISAN : public MAT_VEC{
private:
	double wari;
	vector<int> group;
public:
	int akusesu_keisan();         //普通のアクセスの回数計算
	int akusesu2_keisan();        //普通じゃない方のアクセスの回数計算
	void group_kazoeru();         //連続で続いてる数を数える
};

int main()
{
	MATRIX matrix(800);
	FILE_Sub file_sub;

	file_sub.input_matrix(matrix.Get_mat(), 800);

	matrix.sogyoretu();

	matrix.show();

	return 0;
}

MAT_VEC::MAT_VEC(const int n)
{
	Num = n;

	vec = new int[n];

	mat = new double*[n];

	for (int i = 0; i < n; i++) {
		mat[i] = new double[n];
	}
}

MAT_VEC::~MAT_VEC()
{
	for (int i = 0; i < Num; i++) {
		delete mat[i];
	}

	delete[] mat;
	delete[] vec;
}

int MAT_VEC::Get()
{
	return Num;
}

double **MAT_VEC::Get_mat()
{
	return mat;
}

int *MAT_VEC::Get_vec()
{
	return vec;
}

void MAT_VEC::show()
{
	for (int i = 0; i < Num; i++) {
		for (int j = 0; j < Num; j++) {
			printf("%.0f ", mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void FILE_MAIN::Open_file()
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

void FILE_Sub::input_matrix(double **mat, int n)
{
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fscanf_s(fin, "%lf", &mat[i][j]);
		}
	}
}

void FILE_Sub::output_matrix(double **mat, int n)
{
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fprintf(fout, "%lf", mat[i][j]);
		}
		fprintf(fout, "\n");
	}
	fprintf(fout, "\n");
}

void MATRIX::sogyoretu()
{
	retu();
}

void MATRIX::retu()
{
	//交換の前と後の列の比較に使う変数
	int before, after;

	double val; //列の要素を交換するときに使う
	int t = 0;  //交換した列を記憶する

	int i = 0, j = 0, k = 0;
	for (i = 0; i < Num; i++) {
		for (j = i; j < Num; j++) {
			if (i != j) {

				before = renketu(j) + renketu(i);

				//列を交換
				for (k = 0; k < Num; k++) {
					val = mat[k][i];
					mat[k][i] = mat[k][j];
					mat[k][j] = val;
				}

				after = renketu(j) + renketu(i);
				t = vec[i];
				vec[i] = vec[j];
				vec[j] = t;
				//もし列を交換した後、逆に値が小さくなってたら元に戻す
				if (after < before) {
					for (k = 0; k < Num; k++) {
						val = mat[k][i];
						mat[k][i] = mat[k][j];
						mat[k][j] = val;
					}
					t = vec[i];
					vec[i] = vec[j];
					vec[j] = t;
				}
			}
		}
	}
}

int MATRIX::renketu(int x)
{
	int val = 0;
	int k;
	for (k = 0; k < Num; k++) {
		if (mat[k][x] != 0) {
			if (mat[k][x + 1] != 0) {
				val++;
			}
			if (x - 1 >= 0) {
				if (mat[k][x - 1] != 0) {
					val++;
				}
			}
		}
	}

	return val;
}

void KEISAN::group_kazoeru()
{
	int kazu = 0;
	int i, j, k;

	for (i = 0; i < Num; i++) {
		for (j = 0; j < Num; j++) {
			if (mat[i][j] != 0) {
				kazu++;
				for (k = j + 1; k < Num; k++) {
					if (mat[i][k] == 0) {
						break;
					}
					kazu++;
				}
				group.push_back(kazu);
				kazu = 0;
				j = k - 1;
			}
		}
	}
}

int KEISAN::akusesu_keisan()
{
	int val = 0;
	for (int i = 0; i < Num; i++) {
		for (int j = 0; j < Num; j++) {
			if (mat[i][j] != 0) {
				val += 3;
			}
		}
	}

	return val;
}

int KEISAN::akusesu2_keisan()
{
	group.clear();
	group_kazoeru();

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