#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
//	freopen("in.txt", "r", stdin);
	
	int s = 0;
	long long sum = 0;
	int tmp;
	while (cin >> tmp) sum += tmp, s++;
	
	cout << sum * (1 << (s - 1)) << endl;
}
