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

const int N = 4;

int x[N];  //������������L��

//�t�@�C������ǂݍ���
void input_matrix(double **a, char c, FILE *fin, FILE *fout);

//���������
void free_matrix(double **a);

//�s��A�x�N�g���̃������擾
double **make_matrix();

void init();
void show(FILE *fout, double **a);

void sogyoretu(double **a);    //�a�s��S�̂̏���
void retu(double **a);         //�����

//�]���֐�
int hyoka(double **a);

int main()
{
	FILE *fin, *fout;

	if (fopen_s(&fin, "input.txt", "r") != 0) {
		cout << "�ǂݍ��߂܂���B" << endl;
		exit(1);
	}

	if (fopen_s(&fout, "output.txt", "w") != 0) {
		cout << "�쐬�ł��܂���B" << endl;
		exit(1);
	}

	double **A = make_matrix();

	input_matrix(A, 'A', fin, fout);

	init();

	int before = hyoka(A);

	cout << before << endl;

	sogyoretu(A);

	int after = hyoka(A);

	cout << after << endl;

	show(fout, A);

	free_matrix(A);

	return 0;
}

void sogyoretu(double **a)
{
	retu(a);
}

void retu(double **a)
{
	int max = -10;
	int count = 0;

	int pt;
	int i, j, k;
	for (i = 0; i < N - 1; i++) {
		for (j = i; j < N; j++) {
			for (k = 0; k < N; k++) {
				if (a[k][j] != 0) {
					count++;
				}
			}

			if (max < count) {
				max = count;
				pt = j;
			}
			count = 0;
		}
		if (i != pt) {
			int t;
			double temp;
			for (int l = 0; l < N; l++) {
				temp = a[l][i];
				a[l][i] = a[l][pt];
				a[l][pt] = temp;
			}
			t = x[i];
			x[i] = x[pt];
			x[pt] = t;
		}
		max = -10;
	}
}

void show(FILE *fout, double **a)
{
	fprintf(fout, "�ό`��̍s��A\n");

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fprintf(fout, "%5.2f", a[i][j]);
		}
		fprintf(fout, "\n");
	}

	fprintf(fout, "\n\n");


	fprintf(fout, "�ό`��̕ό`�O�̗�̈ʒu\n");
	for (int i = 0; i < N; i++) {
		fprintf(fout, "%d ", x[i]);
	}
}

void input_matrix(double **a, char c, FILE *fin, FILE *fout)
{
	fprintf(fout, "�s��%c�͎��ł��B\n", c);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fscanf_s(fin, "%lf", &a[i][j]);
			fprintf(fout, "%5.2f", a[i][j]);
		}
		fprintf(fout, "\n");
	}
	fprintf(fout, "\n");
}

void input_vector(double *a, char c, FILE *fin, FILE *fout)
{
	fprintf(fout, "�x�N�g��%c�͎��ł��B\n", c);

	for (int i = 0; i < N; i++) {
		fscanf_s(fin, "%lf", &a[i]);
		fprintf(fout, "%5.2f\n", a[i]);
	}
	fprintf(fout, "\n");
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

/*�s�̏I��肩��ŏ��܂ł�0���A���ő����������������
���ꂾ��0�łȂ��l���E�ɂ���Ă�ƍl������B���ׂĂ̍s�̍��v�𑫂��ă��^�[������*/
int hyoka(double **a)
{
	int count = 0;
	for (int i = 0; i < N; i++) {
		for (int j = N - 1; j >= 0; j--){
			if (a[i][j] == 0) {
				count++;
			} else{
				break;
			}
		}
	}

	return count;
}