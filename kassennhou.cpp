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

const double eps = pow(10, -8);
const int N = 20;  //最大反復回数

void secant(double x0, double x1);  //割線法
double f(double x); //f(x)の計算

int main()
{
	int x0, x1;

	cin >> x0 >> x1;

	secant(x0, x1);

	return 0;
}

void secant(double x0, double x1)
{
	double y0, y1, d;
	int n = 0;

	d = x1 - x0;
	y0 = f(x0);

	do {
		y1 = f(x1);
		d = -y1 * d / (y1 - y0);
		x1 = x1 + d;
		y0 = y1;
		n++;
	} while (abs(d) >= eps && n < N);

	if (n == N) {
		cout << "答えが見つかりません。" << endl;
	}
	else {
		printf("答えは x=%lf\n", x1);
	}
}

double f(double x)
{
	return (x - tan(x));
}