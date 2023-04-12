#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 3e7;

int P[N];
char s[N];

int main() {
	s[0] = '^', s[1] = '#';
	int n(2);
	char tmp;
	do tmp = getchar(); while (tmp < 'a' && 'z' < tmp); 
	do s[n++] = tmp, s[n++] = '#', tmp = getchar(); while ('a' <= tmp && tmp <= 'z');
	s[n] = '$';
	int ans(0);
	int M(0), R(0); // M ���ĵ� 
	// (i - P[i], i + P[i])
	for (int i(1); i < n; ++i) {
		int p = R > i ? min(R - i + 1, P[M * 2 - i]) : 1; 
		while (s[i + p] == s[i - p]) ++p; // ��������չ
		if (i + p - 1 > R) M = i, R = i + p - 1; // �����е� 
		if ((P[i] = p) > ans) ans = p; // ���´� 
	}
	printf("%d\n", ans - 1);
	return 0;
}
