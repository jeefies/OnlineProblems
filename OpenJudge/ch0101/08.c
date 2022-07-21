/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0101/08/
 * 		Solution URL: http://noi.openjudge.cn/ch0101/solution/35246154/
 */

#include <stdio.h>

int main() {
	char c = getchar();

	for (int i = 2; i >= 0; i--) {
		for (int j = 0; j < i; j++) {
			putchar(' ');
		}
		for (int j = 0; j < (5 - i * 2); j++) {
			putchar(c);
		}
		putchar('\n');
	}
}
