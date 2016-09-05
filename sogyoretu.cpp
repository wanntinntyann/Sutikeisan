#include <iostream>
#include <cmath>
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

/*valは価を、yは行番号を格納、xは列番号を格納する。
bは Ax=y のxベクトル*/
vector<double> val;
vector<int> x, y;

void input_matrix(int n, FILE *fin, FILE *fout);  //入力用
void input_vector(int n, FILE *fin, FILE *fout);  //出力用

int main()
{
	FILE *fin, *fout;

	if (fopen_s(&fin, "input.txt", "r") != 0) {
		cout << "読み込み失敗" << endl;
		exit(1);
	}

	if (fopen_s(&fout, "output.txt", "w") != 0) {
		cout << "作成失敗" << endl;
		exit(1);
	}

	input_matrix(N, fin, fout);
//	input_vector(N, fin, fout);

	fclose(fin);
	fclose(fout);

	return 0;
}

void input_matrix(int n, FILE *fin, FILE *fout)
{
	double temp;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fscanf_s(fin, "%lf", &temp);
			if (temp != 0) {
				val.push_back(temp);
				y.push_back(i);
				x.push_back(j);
				fprintf(fout, "%lf %d %d \n", temp, i, j);
				
			}
		}
	}
	fprintf(fout, "\n");
}

void input_vector(int n, FILE *fin, FILE *fout)
{
	double temp;

	int count = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fscanf_s(fin, "%lf", &temp);
		}
	}

	fprintf(fout, "\n");
}