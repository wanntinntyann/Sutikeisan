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

const int N = 10; //最大反復回数
const double eps = pow(10.0, -8.0);

double f(double x);
double df(double x);
void newton(double x);

int main()
{
	double x;

	cin >> x;

	newton(x);

	return 0;
}

void newton(double x)
{
	int n = 0;
	double d;

	do {
		d = -f(x) / df(x);
		x = x + d;
	} while (abs(d) > eps && n > N);

	if (n == N) {
		cout << "答えは見つかりませんでした。" << endl;
	} else{
	    printf("答えはx=%lf\n", x);
	}
}

//関数の定義
double f(double x)
{
	return (x - cos(x));
}

//導関数
double df(double x)
{
	return (1.0 + sin(x));
}
