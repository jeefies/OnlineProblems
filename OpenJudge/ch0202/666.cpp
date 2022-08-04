/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0202/666/
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

int plate_apples[11];

int c = 0;
int plates = 0;

// apples: the rest number
// platei: the plate index 
// prev: last put
int place(int apples, int plates) {
	if (apples == 0 || apples == 1) return c++;
	if (apples == 2) return c+=2;
	if (plates == 0) return 0;
	for (int place = apples; place > apples / 2; place--) {
		place(apples - place, plates-1);
	}
}

int main() {
	plates = 2;
	place(4, 2, 0, 1);
	cout << c << endl;
}
