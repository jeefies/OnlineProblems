/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0106/12/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int len = 1;
char num[40] = {0};
char mul[40] = {0};
char multi2[3] = {2, 0, 0};
char multi4[3] = {4, 0, 0};
char multi8[3] = {8, 0, 0}; //
char multi16[3] = {6, 1, 0}; // 2 * 4

int multiply(char * x)
{
	for (int i = 0; i < len; i++)
		for (int j = 0; j < 3; j++) {
			mul[i + j] += num[i] * x[j];
			mul[i + j + 1] += mul[i + j] / 10; 
			mul[i + j] %= 10;
			// c.w[i+j-1]+=a.w[i]*b.w[j];//此处一定要写成+=
			// c.w[i+j]+=c.w[i+j-1]/10;
			// c.w[i+j-1]%=10;
		}


	len = 39;
	while (len > 0 && mul[len] == '\0') len--;
	len++;
	memcpy(num, mul, sizeof(num));
	memset(mul, 0, sizeof(mul));

}

int main() {
	int n;
	scanf("%d", &n);

	if (n < 64) {
		printf("%llu\n", (unsigned long long)1 << n);
		return 0;
	}

	num[0] = 1;
	while (n >= 4) {
		n -= 4;
		multiply(multi16);
	}

	while (n > 0) {
		n--;
		multiply(multi2);
	}

	for (int i = len - 1; i >= 0; i--) {
		putchar(num[i] + '0');
	}
}
