/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0109/04/
 */

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>

using namespace std;

int getPrice(int avg, int cls_grade, char isStudent, char isWestern, int articleCount) {
	int price = 0;
	if (articleCount > 0 && avg > 80) price += 8000;
	if (cls_grade > 80 && avg > 85) price += 4000;
	if (avg > 90) price += 2000;
	if (isWestern == 'Y' && avg > 85) price += 1000;
	if (isStudent == 'Y' && cls_grade > 80) price += 850;
	return price;
}

int main() {
	int maxp = 0;
	char maxp_name[22];

	int n;
	cin >> n;

	int totalPrice = 0;

	string name;
	int avg, cls_grade, articleCount;
	char isStudent, isWestern;
	for (int i = 0; i < n; i++) {
		cin >> name;
		scanf("%d %d %c %c %d", &avg, &cls_grade, &isStudent, &isWestern, &articleCount);
		int p = getPrice(avg, cls_grade, isStudent, isWestern: false, articleCount);
		totalPrice += p;
		if (p > maxp) {
			maxp = p;
			size_t len = name.copy(maxp_name, 21, 0);
			maxp_name[len] = '\0';
		}
	}

	cout << maxp_name << endl << maxp << endl << totalPrice << endl;
}
