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

const int N = 11;
int x[N];        //������������L��
int x2[N];       //��������̏o�͗p
int g_kazu;      //�O���[�v�̌�
bool flag;
bool Visit[N];

double wari; //0�łȂ����̊���
vector<int> group;  //�A���ő����Ă���0�łȂ����������A�����Ă��邩���L������

					//�t�@�C������ǂݍ���
void input_matrix(double **a, char c, FILE *fin, FILE *fout);

//���������
void free_matrix(double **a);

//�s��A�x�N�g���̃������擾
double **make_matrix();

void init(double **a, FILE *fout, int kakuritu);
void show(FILE *fout, double **a);        //����
void sogyoretu(double **a);               //�a�s��S�̂̏���
void retu(double **a, double **temp, double**temp2, int y);   //�����
void arr_copy(double **a, double** temp, int *t); //�z��R�s�[
int  renketu_kazu(double **a, int x);     //�A�����Ă���𐔂���
double hyoka(double **a);		          //�]���֐�

int akusesu_keisan(double **a);           //���ʂ̃A�N�Z�X�̉񐔌v�Z
int akusesu2_keisan(double **a);          //���ʂ���Ȃ����̃A�N�Z�X�̉񐔌v�Z
int group_kazoeru(double **a);            //�O���[�v�̌��𐔂���
void group_kosu_kazoeru(double **a);      //�O���[�v�Ԃ̘A�����Ă鐔�𐔂���

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
	//for (int i = 10; i <= 100; i++) {
		init(A, fout3, 30);

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
		int val = group_kazoeru(A);
		printf("%d\n", akusesu);

		//�������I�������̑a�s��������o��
		show(fout2, A);
		flag = false;
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
			fprintf(fout, "%.0f", a[i][j]);
		}
		fprintf(fout, "\n");
	}

	fprintf(fout, "\n");

	for (int i = 0; i < N; i++) {
		fprintf(fout, "%d ", x2[i]);
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
	double **temp = make_matrix();
	double **temp2 = make_matrix();
	retu(a, temp, temp2, 0);
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			a[i][j] = temp2[i][j];
		}
	}

	free_matrix(temp);
	free_matrix(temp2);
}

void retu(double **a, double **temp, double **temp2, int y)
{
	int i, j;
	if (y < N) {
		for (i = 0; i < N; i++) {
			if (!Visit[i]) {
				x[y] = i;
				Visit[i] = true;
				retu(a, temp, temp2, y + 1);
				Visit[i] = false;
			}
		}
	}
	else {
		arr_copy(a, temp, x);
		int val2 = group_kazoeru(temp);
		if (flag == false) {
			g_kazu = val2;
			flag = true;
			for (int i = 0; i < N; i++) {
				x2[i] = x[i];
			}
		}
		else {
			if (g_kazu > val2) {
				g_kazu = val2;
				for (int i = 0; i < N; i++) {
					x2[i] = x[i];
				}			
				for (int i = 0; i < N; i++) {
					for (int j = 0; j < N; j++) {
						temp2[i][j] = temp[i][j];
					}
				}
			}
		}
	}
}

void arr_copy(double **a, double **temp, int *t)
{
	int i, j, k;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			temp[j][i] = a[j][t[i]];
		}
	}
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
	group.clear();
	group_kosu_kazoeru(a);

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

//�O���[�v�̒��̐����v�Z
void group_kosu_kazoeru(double **a)
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

//�O���[�v�̌����v�Z
int group_kazoeru(double **a)
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
				}
				j = k - 1;
			}
		}
	}

	return kazu;
}