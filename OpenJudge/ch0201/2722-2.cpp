/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0201/2722/
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
	int N[100];
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> N[i];
	}

	int total = 0;
	for (int c = 0; c < n; c++) {
		bool done = false;
		for (int a = 0; a < n && !done; a++) {
			for (int b = a; b < n && !done; b++) {
				if (a != b && a != c && b != c && N[c] == N[a] + N[b]) {
					total++;
					done = true;
				}
			}
		}
	}

	cout << total << endl;
	return 0;
}
