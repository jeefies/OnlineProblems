#include <iostream>

int base;

inline bool valid(char c) {
	return ('0' <= c && c <= '9') || ('A' <= c && c <= 'F');
}

#define toNum(c) ('0'<=(c)&&(c)<='9' ? (c) - '0' : (c) - 'A' + 10)
#define toChar(c) ((c)<10 ? c + '0' : c + 'A' - 10)

int read() {
	char tmp;
	do tmp = getchar(); while (!valid(tmp));
	int x = 0;
	do {
		x = x * base + toNum(tmp);
		tmp = getchar(); 
	} while (valid(tmp));
	return x;
}

void prt(int n) {
	if (n / base) prt(n / base);
	printf("%c", toChar(n % base));
}

int main() {
	scanf("%d", &base);
	int x = read();
	scanf("%d", &base);
	prt(x);
}
