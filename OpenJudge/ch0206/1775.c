#include <stdio.h>
#include <string.h>

#define max(a,b) (a>b?a:b)

int t[101], v[101];
// f[i][j] 表示在j+1时间内放i+1株植物所能获取的最大价值 
int f[101][1001] = {0};

int main() {
	int T, M;
	scanf("%d%d", &T, &M);

	for (int i = 0; i < M; i++) {
		scanf("%d%d", t + i, v + i);
	}
	
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < T; j++) {
			
		}
	}
	
	printf("%d\n", f[M - 1][T - 1]);
	return 0;
}
