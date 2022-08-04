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

void move(int num, char src, char dst, char help) {
	if (num == 1) {
		cout << src << "->1->" << dst << endl;
		return;
	}
	move(num - 1, src, help, dst);
	printf("%c->%d->%c\n", src, num, dst);
	move(num - 1, help, dst, src);
}
 
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int n;
    char src, dst, help;
    cin >> n >> src >> dst >> help;
	move(n, src, dst, help);
    return 0;
}
