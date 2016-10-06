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
template<class X> 
class MAT_VEC {
protected:
	X **mat;
	int *vec;
	int Row;
	int Col;
public:
	MAT_VEC(const int r, const int c, bool, int prob);
	~MAT_VEC();
	X **Get_mat();
	int *Get_vec();
	int Get();
	void show();
};

class FILE_MAIN{
protected:
	fstream fin;
	fstream fout;
	fstream fout2;
	fstream fout3;
public:
	void Open_file(string str);
	~FILE_MAIN();
};

template<class X>
class FILE_Sub : public FILE_MAIN {
public:
	void input_matrix(X **mat, int r, int c);
	void output_matrix(X **mat, int *vec, int r, int c);
};


//行列操作クラス
template<class X> class MATRIX : public MAT_VEC<X>{
public:
	MATRIX(int r, int c, bool f, int p) : MAT_VEC(r, c, f, p) {};
	void sogyoretu();
	void retu();;
	int renketu(int x);
};

//メモリアクセス回数の計算クラス
template<class X> class KEISAN : public MAT_VEC<X>{
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
	int r = 800;
	int c = 800;

	MATRIX<double> matrix(r, c, false, 20);

	FILE_Sub<double> file_sub;

	file_sub.Open_file("mat800x800.txt");

	file_sub.input_matrix(matrix.Get_mat(), r, c);

	matrix.sogyoretu();

	file_sub.output_matrix(matrix.Get_mat(), matrix.Get_vec(), r, c);

	return 0;
}

template<class X>
MAT_VEC<X>::MAT_VEC(const int r, const int c, bool flag, int prob)
{
	Row = r;
	Col = c;

	vec = new int[Row];

	mat = new double*[Col];

	for (int i = 0; i < r; i++) {
		mat[i] = new double[c];
	}

	for (int i = 0; i < Col; i++) {
		vec[i] = i;
	}

	srand((unsigned int)time(NULL));

	if (flag == true) {
		int i, j;
		for (i = 0; i < Row; i++) {
			for (j = 0; j < Col; j++) {
				int val = rand() % 100;
				if (val < prob) {
					mat[i][j] = 1;
				}
				else {
					mat[i][j] = 0;
				}
			}
		}
	}
}

template<class X>
MAT_VEC<X>::~MAT_VEC()
{
	for (int i = 0; i < Row; i++) {
		delete mat[i];
	}

	delete[] mat;
	delete[] vec;
}

template<class X>
int MAT_VEC<X>::Get()
{
	return Num;
}

template<class X>
X **MAT_VEC<X>::Get_mat()
{
	return mat;
}

template<class X>
int *MAT_VEC<X>::Get_vec()
{
	return vec;
}

template<class X>
void MAT_VEC<X>::show()
{
	for (int i = 0; i < Row; i++) {
		for (int j = 0; j < Col; j++) {
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void FILE_MAIN::Open_file(string str)
{
	fin.open(str, ios::in);
	if (!fin.is_open()) {
		exit(1);
	}

	fout.open("output.txt", ios::out);
	if (!fout.is_open()) {
		exit(1);
	}

	fout2.open("output2.txt", ios::out);
	if (!fout2.is_open()) {
		exit(1);
	}

	fout3.open("output3.csv", ios::out);
	if (!fout3.is_open()) {
		exit(1);
	}
}

FILE_MAIN::~FILE_MAIN()
{
	fin.close();
	fout.close();
	fout2.close();
	fout3.close();
}

template<class X>
void FILE_Sub<X>::input_matrix(X **mat, int r, int c)
{
	int i, j;
	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			fin >> mat[i][j];
		}
	}
}

template<class X>
void FILE_Sub<X>::output_matrix(X **mat, int *vec, int r, int c)
{
	int i, j;

	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			fout << mat[i][j] << " ";
		}
		fout << endl;
	}
	fout << endl;

	for (int i = 0; i < c; i++) {
		fout << vec[i] << " ";
	}
}

template<class X>
void MATRIX<X>::sogyoretu()
{
	retu();
}

template<class X>
void MATRIX<X>::retu()
{
	//交換の前と後の列の比較に使う変数
	int before, after;

	double val; //列の要素を交換するときに使う
	int t = 0;  //交換した列を記憶する

	int i = 0, j = 0, k = 0;
	for (i = 0; i < Row; i++) {
		for (j = i; j < Col; j++) {
			if (i != j) {

				before = renketu(j) + renketu(i);

				//列を交換
				for (k = 0; k < Row; k++) {
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
					for (k = 0; k < Row; k++) {
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

template<class X>
int MATRIX<X>::renketu(int x)
{
	int val = 0;
	int k;
	for (k = 0; k < Row; k++) {
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

template<class X>
void KEISAN<X>::group_kazoeru()
{
	int kazu = 0;
	int i, j, k;

	for (i = 0; i < Row; i++) {
		for (j = 0; j < Col; j++) {
			if (mat[i][j] != 0) {
				kazu++;
				for (k = j + 1; k < Col; k++) {
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

template<class X>
int KEISAN<X>::akusesu_keisan()
{
	int val = 0;
	for (int i = 0; i < Row; i++) {
		for (int j = 0; j < Col; j++) {
			if (mat[i][j] != 0) {
				val += 3;
			}
		}
	}

	return val;
}

template<class X>
int KEISAN<X>::akusesu2_keisan()
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