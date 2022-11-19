#include <stdio.h>
#include <stack>
#include <string.h>

int main() {
	char s[300] = {0};
	scanf("%s", s);
	int sl = strlen(s);
	
	int lc = 0;
	for (int i = 0; i < sl; i++) {
		if (s[i] == '(') ++lc;
		if (s[i] == ')') {
			if (lc <= 0) {
				printf("NO\n");
				return 0;
			}
			--lc;
		}
	}
	printf(lc == 0 ? "YES\n" : "NO\n");
}
