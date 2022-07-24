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

#include <unistd.h>

using namespace std;

int main() {
	int i, n, k;
	double p;
	cin >> n >> k;
	p = 200;
	// for (i = 1; i < 20; i++) {
	i = 1;
	while (i < 20) {
		if (i * n >= p) {
			cout << i << endl;
			return 0;
		}
		p = p + p * k / 100.0;
		i++;
	}
	cout << "Impossible" << endl;
	return 0;
}
