//y=Ax�̍s��A���œK������v���O����1
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


//�s�񑀍�N���X
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

//�������A�N�Z�X�񐔂̌v�Z�N���X
class KEISAN {
private:
	double wari;
	vector<int> group;
public:
	int akusesu_keisan(double **a);         //���ʂ̃A�N�Z�X�̉񐔌v�Z
	int akusesu2_keisan(double **a);        //���ʂ���Ȃ����̃A�N�Z�X�̉񐔌v�Z
	void group_kazoeru(double **a);         //�A���ő����Ă鐔�𐔂���
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
	//�����̑O�ƌ�̗�̔�r�Ɏg���ϐ�
	int before, after;

	double val; //��̗v�f����������Ƃ��Ɏg��
	int t = 0;  //������������L������

	int i = 0, j = 0, k = 0;
	for (i = 0; i < Num; i++) {
		for (j = i; j < Num; j++) {
			if (i != j) {

				before = renketu(a, j) + renketu(a, i);

				//�������
				for (k = 0; k < Num; k++) {
					val = a[k][i];
					a[k][i] = a[k][j];
					a[k][j] = val;
				}

				after = renketu(a, j) + renketu(a, i);
				t = vec[i];
				vec[i] = vec[j];
				vec[j] = t;
				//�����������������A�t�ɒl���������Ȃ��Ă��猳�ɖ߂�
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