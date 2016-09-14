/*#include <iostream>
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

const int N = 12;

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
double hyoka(double **a);

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

	double before = hyoka(A);

	cout << before << endl;

	sogyoretu(A);

	double after = hyoka(A);

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
	int *temp = new int[N];
	int i, j, k;

	int count = 0;
	double val;

	for (i = 0; i < N; i++) {
		for (j = count; j < N; j++) {
			if (a[i][j] != 0) {
				for (k = 0; k < N; k++) {
					val = a[k][count];
					a[k][count] = a[k][j];
					a[k][j] = val;
				}
				int t = x[j];
				x[j] = x[count];
				x[count] = t;
				if (count >= N - 1) {
					break;
				}
				count++;
			}
		}
	}

	delete[] temp;
}

void show(FILE *fout, double **a)
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fprintf(fout, "%.0f ", a[i][j]);
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

void init()
{
	for (int i = 0; i < N; i++) {
		x[i] = i;
	}
}

/*�s�̏I��肩��ŏ��܂ł�0���A���ő����������������
���ꂾ��0�łȂ��l���E�ɂ���Ă�ƍl������B���ׂĂ̍s�̍��v�𑫂��ă��^�[������
double hyoka(double **a)
{
	double value = 1;
	double keisu = 1.0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - 1; j++) {
			if (a[i][j] != 0) {
				value += keisu * a[i][j];
				if (a[i][j + 1] != 0) {
					keisu *= 2.0;
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
*/