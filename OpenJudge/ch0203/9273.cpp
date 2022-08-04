/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0203/9273/
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

typedef struct {
	char w[267];
} hp;

hp jia(hp a,hp b) {
	hp c;
	
	if (a.w[0]>b.w[0]) c.w[0]=a.w[0]+1;
	else c.w[0]=b.w[0]+1;
	
	for (int i=1;i<=c.w[0];i++) c.w[i]=0;

	for (int i=1;i<=c.w[0]-1;i++) {
		c.w[i]+=a.w[i]+b.w[i];
		c.w[i+1]+=c.w[i]/10;
		c.w[i]%=10;
	}
	
	while (c.w[0]>1&&c.w[c.w[0]]==0) c.w[0]--;
	
	return c;
}

int number(int n) {
	hp a = {1, 1};
	hp b = {1, 3};
	if (n == 0) return printf("1\n");
	if (n == 1) return printf("1\n");
	if (n == 2) return printf("3\n");

	while (n-- - 2 > 0) {
		hp c = jia(jia(a, a), b);
		a = b;
		b = c;
	}

	for (int i = b.w[0]; i > 0; i--) {
		printf("%d", b.w[i]);
	}
	return printf("\n");
}

int main() {
	int n;
	while (cin >> n)
		number(n);
}
