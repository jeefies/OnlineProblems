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

using namespace std;

int main() {
	// cout << "Begin:";
	int n, m;
	scanf("%d%d", &n, &m);

	int pi = 0;
	vector<int> people(n);
	vector<int> out(m);

	for (int &i : people) {
		cin >> i;
	}

	int loopTime = 0;
	int Ocnt = 0;
	while (Ocnt != m) {
		Ocnt = 0;
		for (int &i : out) {
			if (i > 0)
				i--;
			
			if (i == 0)
				if (pi < people.size())
					i = people[pi++];
				else
					Ocnt++;
		}
		loopTime++;
	}
	cout << loopTime - 1 << endl;
}
