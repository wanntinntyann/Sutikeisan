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

const int N = 10;
int x[N];   //������������L��
bool Visit[N];
int vec[N];
int vec_ans[N];
int vec_rand[N];

double wari; //0�łȂ����̊���
vector<int> group;  //�A���ő����Ă���0�łȂ����������A�����Ă��邩���L������

struct RETU {
	int index;
	int kazu; 
};

//�t�@�C������ǂݍ���
void input_matrix(double **a, char c, FILE *fin, FILE *fout);

//���������
void free_matrix(double **a);

//�s��A�x�N�g���̃������擾
double **make_matrix();

void init(double **a, FILE *fout, int kakuritu);
void show(FILE *fout, double **a);   //����
void sogyoretu(double **a);          //�a�s��S�̂̏���
void retu(double **a, int n);               //������̑S�̂̊֐�
void retu_kae(double **a, int count, int zyogen, int &score); //�����ւ��̎�Ȋ֐�
int hyoka(double **a, int *t, int n);            //�O���[�v�̌��𐔂���
int retuyouso(double **a, int x);
int akusesu_keisan(double **a);      //���ʂ̃A�N�Z�X�̉񐔌v�Z
int akusesu2_keisan(double **a);     //���ʂ���Ȃ����̃A�N�Z�X�̉񐔌v�Z
void group_kazoeru(double **a);      //�A���ő����Ă鐔�𐔂���
bool hikaku(const RETU& a, const RETU& b);

int main()
{
	FILE *fin, *fout, *fout2, *fout3;

	if (fopen_s(&fin, "mat800x800.txt", "r") != 0) {
		cout << "�ǂݍ��߂܂���B" << endl;
		exit(1);
	}
	
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
	//for (int i = 1; i <= 100; i++) {
		init(A, fout3, 20);

		fprintf(fout3, "%lf,", wari);
		printf("%lf,", wari);

		akusesu = akusesu2_keisan(A);
		fprintf(fout3, "%d,", akusesu);
		printf("%d,", akusesu);

		//��������O�̍s��������o��
		show(fout, A);
		sogyoretu(A);
		akusesu = akusesu2_keisan(A);

		fprintf(fout3, "%d\n", akusesu);
		printf("%d\n", akusesu);

		//�������I�������̑a�s��������o��
		show(fout2, A);
	//}

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
			fprintf(fout, "%.0f ", a[i][j]);
			//printf("%.0f ", a[i][j]);
		}
		fprintf(fout, "\n");
		//printf("\n");
	}
	//printf("\n");

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

void sogyoretu(double **a)
{
	int count = 0;
	double **arr = make_matrix();
	vector<RETU> temp(N);
	int i = 0, j = 0, k = 0;

	for (i = 0; i < N; i++) {
		temp[i].kazu = retuyouso(a, i);
		temp[i].index = i;
	}

	sort(temp.begin(), temp.end(), hikaku);

	for (int i = 0; i < N; i++) {
		x[i] = temp[i].index;
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			arr[j][i] = a[j][temp[i].index];
		}
	}

	free_matrix(arr);

	retu(a, 5);
}

void retu(double **a, int n)
{
	double **arr = make_matrix();

	for (int i = 0; i < N; i++) {
		vec[i] = x[i];
		vec_ans[i] = x[i];
	}

	int score = 1000000;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < n; j++) {

			int kazu;
			do {
				kazu = rand() % N;
			} while (Visit[kazu]);
			vec_rand[j] = kazu;
		}

		for (int j = 0; j < N; j++) {
			Visit[j] = false;
		}

		retu_kae(a, 0, n, score);

		for (int j = 0; j < N; j++) {
			x[vec_rand[j]] = vec_ans[j];
		}
	
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				arr[k][j] = a[k][vec_ans[j]];
			}
		}
		score = 1000000;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			a[i][j] = arr[i][j];
		}
	}

	free_matrix(arr);
}

void retu_kae(double **a, int count, int zyogen, int& score)
{
	int val = 0;
	if (count >= zyogen) {
		val = hyoka(a, vec, zyogen);
		if (val < score) {
			score = val;
			for (int k = 0; k < zyogen; k++) {
				vec_ans[k] = vec[k];
			}
		}
	}
	else {
		for (int i = 0; i < zyogen; i++) {
			if (!Visit[x[vec_rand[i]]]) {
				vec[vec_rand[i]] = x[vec_rand[i]];
				Visit[x[vec_rand[i]]] = true;
				retu_kae(a, count + 1, zyogen, score);
				Visit[x[vec_rand[i]]] = false;
			}
		}
	}
}


int hyoka(double** a, int *t, int n)
{
	int val = 0;
	int i, j, k;
	double **arr = make_matrix();

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			arr[i][j] = a[i][j];
		}
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < N; j++) {
			arr[j][vec_rand[i]] = arr[j][t[i]];
		}
	}


	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (a[i][j] != 0) {
				val++;
				for (k = j + 1; k < n; k++) {
					if (arr[i][j] == 0) {
						break;
					}
				}
				j = k - 1;
			}
		}
	}

	return val;
}

int retuyouso(double **a, int x)
{
	int val = 0;
	int k;
	for (k = 0; k < N; k++) {
		if (a[k][x] != 0) {
			val++;
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
	group.clear();
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
				j = k - 1;
			}
		}
	}
}

bool hikaku(const RETU &a, const RETU &b)
{
	if (a.kazu - b.kazu > 0) {
		return true;
	}

	return false;
}