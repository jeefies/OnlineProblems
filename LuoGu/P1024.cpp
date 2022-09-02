/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://www.luogu.com.cn/problem/P1024
 */

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;
	
double a, b, c, d;

double f(double x) {
	return a * x * x * x + b * x * x + c * x + d;
}

void search(double l, double r) {
	if (r - l < 1e-4) {
		printf("%.2lf ", l);
		return;
	}

	double fl = f(l), fr = f(r);

	if (fl == 0) {
		printf("%.2lf ", l);
		return;
	}

	if (fl * fr >= 0) return;

	double mid = (l + r) / 2;
	double fm = f(mid);

	if (fm * fl < 0) search(l, mid);
	else search(mid, r);
}

int main() {
	cin >> a >> b >> c >> d;
	for (int i = -100; i < 100; i++) {
		search(i, i + 1);
	}
}
