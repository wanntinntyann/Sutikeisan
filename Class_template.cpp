//y=Axの行列Aを最適化するプログラム1
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

template<class X> class Stack {
private:
	X *Box;
	int index;
	int Num;
public:
	bool push(X n);
	X pop();
	Stack(X n);
	~Stack();
};

int main()
{
	Stack<int> st(10);

	st.push(2);
	st.push(3);

	cout << st.pop() << endl;

	return 0;
}

template<class X>
Stack<X>::Stack(X n)
{
	Num = n;
	Box = new X[Num];
	index = 0;
}

template<class X>
Stack<X>::~Stack()
{
	delete[] Box;
}

template<class X>
bool Stack<X>::push(X n)
{
	if (index > Num - 1) {
		return false;
	}

	Box[index++] = n;

	return true;
}

template<class X>
X Stack<X>::pop()
{
	if (index <= 0) {
		return NULL;
	}

	return Box[--index];
}
