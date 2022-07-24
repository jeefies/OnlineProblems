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

char preProcessChar(char x) {
	if ('A' <= x && x <= 'Z') return x - 'A' + 26;
	if ('a' <= x && x <= 'z') return x - 'a';
}

int cmpchar(char a, char b) {
}

int cmpstr(const char * a, const char * b)
