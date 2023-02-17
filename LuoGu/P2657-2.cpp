#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 12;
// dp[i][j] �ڵ�iλ������j�ж�������� λ�������� 
// ��֤ i-1 λ�������� 
int dp[N][N];
// dp[i][j] = dp[i - 1][k] (abs(j - k) >= 2)

void init() {
	for (int j(0); j < 10; ++j)
		dp[0][j] =  1;
		
	for (int i(1); i < N; ++i) {
		for (int j(0); j < 10; ++j) {
			for (int k(0); k < 10; ++k) if (abs(j - k) >= 2)
				dp[i][j] += dp[i - 1][k];
		}
	}
}

int solve(int x) {
	if (!x) return 0;
	
	static int n[N];
	int len(0), ans(0);
	while (x) {
		n[len++] = x % 10, x /= 10;
	} --len;
	
	// �������λΪ0�����
	// Ҳ����˵�󳤶�С�� len ����� 
	for (int i(0); i < len; ++i) {
		for (int j(0); j < 10; ++j)
			ans += dp[i][j];
	}
	
	// �������λû�дﵽ�Ͻ� 
	for (int j(1); j < n[len]; ++j) {
		ans += dp[len][j];
	}
	
	// ���λ�ﵽ����
	for (int i = len - 1; i >= 0; --i) {
		// ���� i λû�дﵽ����
		for (int j(0); j < n[i]; ++j) {
			//  ����� i + 1 λ�������Ҫ��ż� 
			if (abs(j - n[i + 1]) >= 2) ans += dp[i][j]; 
		}
		if (abs(n[i] - n[i + 1]) < 2) break; // ת�Ʋ������ˣ��������� 
	} 
}

int main() {
	int l, r;
	scanf("%d %d", &l, &r);
	printf("%d\n", solve(r) - solve(l - 1));
	return 0;
}
