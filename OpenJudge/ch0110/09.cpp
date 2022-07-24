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

using namespace std;

bool bitmap[1001] = {false};

int main() {
	int c;
	cin >> c;
	
	int id;
	for (int i = 0; i < c; i++) {
		cin >> id;
		bitmap[id] = true;
	}

	int n = 0;
	stringstream ss;
	for (int i = 0; i < 1001; i++) {
		if (bitmap[i]) {
			n++;
			ss << i << ' ';
		}
	}
	cout << n << endl << ss.str() << endl;
}
