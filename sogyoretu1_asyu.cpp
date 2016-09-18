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
int x[N];   //������������L��

double wari; //0�łȂ����̊���
vector<int> group;  //�A���ő����Ă���0�łȂ����������A�����Ă��邩���L������

//�t�@�C������ǂݍ���
void input_matrix(double **a, char c, FILE *fin, FILE *fout);

//���������
void free_matrix(double **a);

//�s��A�x�N�g���̃������擾
double **make_matrix();

void init(double **a, FILE *fout, int kakuritu);
void show(FILE *fout, double **a);      //����
void sogyoretu(double **a);             //�a�s��S�̂̏���
void retu(double **a);                  //�����
int  renketu_kazu(double **a, int x);   //�A�����Ă���𐔂���
double hyoka(double **a);		        //�]���֐�

int akusesu_keisan(double **a);         //���ʂ̃A�N�Z�X�̉񐔌v�Z
int akusesu2_keisan(double **a);        //���ʂ���Ȃ����̃A�N�Z�X�̉񐔌v�Z
void group_kazoeru(double **a);         //�A���ő����Ă鐔�𐔂���

int main()
{
	FILE *fin, *fout, *fout2, *fout3;
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

	if (fopen_s(&fout3, "output3.csv", "w") != 0) {
		cout << "�쐬�ł��܂���B" << endl;
		exit(1);
	}

	double **A = make_matrix();

	//input_matrix(A, 'A', fin, fout);

	int akusesu;
	fprintf(fout3, "x, �����@, �����A\n");
	for (int i = 1; i <= 100; i++) {
		init(A, fout3, i);

		fprintf(fout3, "%lf,", wari);
		printf("%lf,", wari);

		akusesu = akusesu_keisan(A);
		fprintf(fout3, "%d,", akusesu);
		printf("%d,", akusesu);

		//��������O�̍s��������o��
		//show(fout, A);

		sogyoretu(A);
		akusesu = akusesu2_keisan(A);

		fprintf(fout3, "%d\n", akusesu);
		printf("%d\n", akusesu);

		//�������I�������̑a�s��������o��
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
			fprintf(fout, "%.0f", a[i][j]);
		}
		fprintf(fout, "\n");
	}

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

	//���I�z�����ɂ���
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
}

void retu(double **a)
{
	int *temp = new int[N];

	�����̑O�ƌ�̗�̔�r�Ɏg���ϐ�
	int before, after;

	double val; //��̗v�f����������Ƃ��Ɏg��
	int t = 0;  //������������L������

	int i = 0, j = 0, k = 0;
	for (i = 0; i < N; i++) {
		for (j = i; j < N; j++) {
			if (i != j) {

				before = renketu_kazu(a, j) + renketu_kazu(a, i);

				//�������
				for (k = 0; k < N; k++) {
					val = a[k][i];
					a[k][i] = a[k][j];
					a[k][j] = val;
				}

				after = renketu_kazu(a, j) + renketu_kazu(a, i);

				//�����������������A�t�ɒl���������Ȃ��Ă��猳�ɖ߂�
				if (after < before) {
					for (k = 0; k < N; k++) {
						val = a[k][i];
						a[k][i] = a[k][j];
						a[k][j] = val;
					}
				}

				//������������L��
				t = x[i];
				x[i] = x[j];
				x[j] = t;
			}
		}
	}

	delete[] temp;
}

int renketu_kazu(double **a, int x)
{
	int val = 0;
	int k;
	for (k = 0; k < N; k++) {
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

//���ʂɃA�N�Z�X�����ꍇ�̃A�N�Z�X�񐔌v�Z
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

//���ʂ���Ȃ����@�A�N�Z�X�����ꍇ�̃A�N�Z�X�񐔌v�Z
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