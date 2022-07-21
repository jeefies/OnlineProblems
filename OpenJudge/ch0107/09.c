/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include <iostream>
#include <string>

int main() {
	std::string s;
	getline(std::cin, s);
	for (const char &tmp : s) {
		if ('a' <= tmp && tmp <= 'z') {
			printf("%c", 'a' + (tmp - 'a' + 1) % 26);
		} else if ('A' <= tmp && tmp <= 'Z') {
			putchar('A' + (tmp - 'A' + 1) % 26);
		} else
			putchar(tmp);
	}
}
