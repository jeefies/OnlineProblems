/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
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

int main() {
	double top;
	cin >> top;
	getchar();

	string a, b;
	getline(cin, a);
	getline(cin, b);

	int total = a.size(), same = 0;
	for (int i = 0; i < total; i++) {
		if (a[i] == b[i]) same++;
	}

	if (double(same) / double(total) >= top) {
		cout << "yes" << endl;
	} else
		cout << "no" << endl;
}
