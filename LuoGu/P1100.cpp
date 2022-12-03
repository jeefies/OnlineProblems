#include <cstdio>

#define LMASK 0xFFFF0000
#define RMASK 0x0000FFFF

int main() {
	unsigned int x;
	scanf("%u", &x);
	x = ((x & LMASK)>>16) | ((x & RMASK)<<16);
	printf("%u", x); 
} 
