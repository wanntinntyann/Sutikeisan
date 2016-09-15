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

const int N = 800;
int x[N];  //������������L��

//2�x�ڂ̗�ړ��͈̔�
int hani_start[N];
int hani_end[N];

//0�łȂ����̊���
double wari = 0;

//�t�@�C������ǂݍ���
void input_matrix(double **a, char c, FILE *fin, FILE *fout);

//���������
void free_matrix(double **a);

//�s��A�x�N�g���̃������擾
double **make_matrix();

void init(double **a);
void show(FILE *fout, double **a);  //����
void sogyoretu(double **a);         //�a�s��S�̂̏���
void retu(double **a);              //�����
void retu_sita(double **a, int x);  //2�x�ڂ̗����
									
//�]���֐�
double hyoka(double **a);

int main()
{
	FILE *fin, *fout, *fout2;
	/*
	if (fopen_s(&fin, "mat800x800.txt", "r") != 0) {
		cout << "�ǂݍ��߂܂���B" << endl;
		exit(1);
	}
	*/
	if (fopen_s(&fout, "output.txt", "w") != 0) {
		cout << "�쐬�ł��܂���B" << endl;
		exit(1);
	}

	if (fopen_s(&fout2, "output2.txt", "w") != 0) {
		cout << "�쐬�ł��܂���B" << endl;
		exit(1);
	}

	double **A = make_matrix();

	//input_matrix(A, 'A', fin, fout);

	init(A);

	//��������O�̍s��������o��
	show(fout, A);

	cout << hyoka(A) << endl;

	sogyoretu(A);

	cout << hyoka(A) << endl;

	//�������I�������̑a�s��������o��
	show(fout2, A);

	cout << wari << endl;

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

void init(double **a)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < N; i++) {
		x[i] = i;
	}

	int val;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			val = rand() % 100;
			if (val >= 15) {
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
/*�s�̏I��肩��ŏ��܂ł�0���A���ő����������������
���ꂾ��0�łȂ��l���E�ɂ���Ă�ƍl������B���ׂĂ̍s�̍��v�𑫂��ă��^�[������*/
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
				//�����r����0�ɂȂ�����W����1.0�ɖ߂��B
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