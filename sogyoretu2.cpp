//y=Ax�̑a�s��A�̍œK���̃v���O����2
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
int x[N];  //������������L��

struct CHILD {
	double val;      //�]���l
	int iden[N];  //��`�q
};

vector<CHILD> parent(OYA);   //�e
vector<CHILD> child(KO);     //�q���B��ԍ�����`�q�Ƃ���
bool Visit[N];

//�t�@�C������ǂݍ���
void input_matrix(double **a, FILE *fin, FILE *fout);

//�s��̃��������
void free_matrix(double **a);

//�s��̃������m��
double **make_matrix();

void show(FILE *fout, double **a);  //����
void sogyoretu(double **a);         //�a�s��̏���

void init(double **a);           //������
void sentaku(double **a);        //�I��
void kousa();                    //����
void heni();                     //�ˑR�ψ�
void idensi(int *a);             //�����`�q�̌`�ɂ���
int idensi2(int *a, int pt);     //��`�q���̌`�ɂ���
double hyoka(double **a);        //�]���֐�
bool hikaku(const CHILD &a, const CHILD &b);  //sort�֐��Ŏg����r�֐�

int main()
{
	FILE *fin, *fout;

	if (fopen_s(&fin, "mat800x800.txt", "r") != 0) {
		cout << "�ǂݍ��߂܂���B" << endl;
		exit(1);
	}

	if (fopen_s(&fout, "output.txt", "w") != 0) {
		cout << "�쐬�ł��܂���B" << endl;
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
			fprintf(fout, "%.0f ", a[i][j]);
		}
		fprintf(fout, "\n");
	}
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

void init(double **a)
{
	for (int i = 0; i < N; i++) {
		x[i] = i;
	}

	srand((unsigned int)time(NULL));

	int pt;
	int i, j, k;
	int max = -10;
	int count = 0;

	int *temp = new int[N];

	for (i = 0; i < N; i++) {
		temp[i] = i;
	}

	//�����_���Ɏq�����߂�B
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

	//�e��`�q�̕]���l���v�Z
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

	//�]���l�̏�8�ʂ��烉���_���ɐe��I��
	int choose, choose2;
	choose = rand() % (KO - 14) + 14;

	parent[0] = child[choose];
	//Visit[choose] = true;
	/*
	do {
		choose2 = rand() % (KO -13) + 13;
		cout << "a" << endl;
	}while(Visit[choose2]);
	*/
	parent[1] = child[choose - 1];

	cout << parent[0].val << endl;

	//Visit[choose] = false;
	delete[] temp2;
	free_matrix(temp);
}

//�e����q�����
void kousa()
{
	int *a = new int[N];

	//��l����
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

/*�A���Ȃ炻�ꂾ���l�܂��Ă�̂ŘA�����Ă���
�W����傫���������]���l���傫���Ȃ�悤�ɂ���*/
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
	//�����_���Ŏq��I�񂾈�`�q��ω�������
	int kakuritu, choose;

	kakuritu = rand() % 100;

	if (kakuritu >= 5) {
		choose = rand() % KO;
		child[choose].iden[2] = 1;
	}
}