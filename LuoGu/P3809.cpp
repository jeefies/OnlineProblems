#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

const int N = 1e6 + 7;

char s[N];
int n;
int SA[N << 1], temp[2][N << 1];

int main() {
	scanf("%s", s);
	n = strlen(s); 

	for (int i(0); i < n; ++i) SA[i] = i, temp[0][i] = s[i];
	
	for (int w(1), k(0); w < n; w <<= 1, k ^= 1) {
		int *rank = temp[k], *backup = temp[k ^ 1];
		
		for (int i(0); i < n; ++i) {
			printf("(%d, %d) ", rank[i], rank[i + w]);
		} printf("\n");
		
		std::sort(SA, SA + n, [&w, rank](const int &x, const int &y) {
			return rank[x] ^ rank[y] ? rank[x] < rank[y] : rank[x + w] < rank[y + w];
		});
		
		for (int p(1), i(0); i < n; ++i) {
			if (rank[SA[i]] == rank[SA[i + 1]] && rank[SA[i] + w] == rank[SA[i + 1] + w])
				backup[SA[i]] = p;
			else backup[SA[i]] = p++;
		}
		
		for (int i(0); i < n; ++i) {
			printf("%d ", backup[i]);
		} printf("\n");
	}
	
	for (int i(0); i < n; ++i) printf("%d ", SA[i] + 1);
	return 0;
}
