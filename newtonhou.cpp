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
#include <ctime>
#include <fstream>
using namespace std;

const int N = 10; //�ő唽����
const double eps = pow(10.0, -8.0);

double f(double x);
double df(double x);
double newton(double x);

int main()
{
	double x;

	cin >> x;

	double ans = newton(x);

	printf("������ x=%lf\n", ans);

	return 0;
}

double newton(double x)
{
	int n = 0;
	double d;

	do {
		d = -f(x) / df(x);
		x = x + d;
	} while (d > eps && n > N);

	if (n == N) {
		cout << "�����͌�����܂���ł����B" << endl;
	}

	return x;
}

//�֐��̒�`
double f(double x)
{
	return (x - cos(x));
}

double df(double x)
{
	return (1 + sin(x));
}