#include <iostream>
#include <algorithm> 
#include <cstring>

using namespace std;
const int MOD = 1e8, N = 5000 + 2;

int f[2][N], p[2][N];
char A[N], B[N];

int main() {
	cin.tie(0)->sync_with_stdio(false);
	
	cin >> (A + 1) >> (B + 1);
	int la = strlen(A + 1) - 1, lb = strlen(B + 1) - 1;
	
	for (int i = 0; i <= lb; ++i) 
		p[0][i] = 1;
	p[1][0] = 1;
	
	int cur, prv;
	for (int i = 1; i <= la; ++i) {
		cur = i % 2, prv = cur ^ 1;
		for (int j = 1; j <= lb; ++j) {
			p[cur][j] = f[cur][j] = 0;
			f[cur][j] = max(f[cur][j - 1], f[prv][j]);
			if (A[i] == B[j])
				f[cur][j] = max(f[cur][j], f[prv][j - 1] + 1);
			
			// 计算方案数
			if (A[i] == B[j] && f[cur][j] == f[prv][j - 1] + 1)
				p[cur][j] += p[prv][j - 1];
			if (f[cur][j] == f[prv][j])
				p[cur][j] += p[prv][j]; 
			if (f[cur][j] == f[cur][j - 1])
				p[cur][j] += p[cur][j - 1];
			if (f[cur][j] == f[prv][j - 1]) p[cur][j] -= p[prv][j - 1];
			p[cur][j] %= MOD;
		}
	}
	
	cout << f[cur][lb] << '\n' << p[cur][lb] << '\n';
	return 0; 
}