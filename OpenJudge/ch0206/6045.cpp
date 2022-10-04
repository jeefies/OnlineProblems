#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int max(int a, int b) {
  return a > b ? a : b;
}

void proceed() {
  static int places[100], values[100];
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++) {
    scanf("%d", places + i);
  }
  for (int i = 0; i < n; i++) {
    scanf("%d", values + i);
  }

  static int dp[100];
  memset(dp, 0, sizeof(dp));

  int maxresult = 0;
  for (int p = 0; p < n; p++) {
    int maxv = 0;
    for (int i = 0; i < p; i++) {
      if (places[i] + k >= places[p]) break;
      maxv = max(maxv, dp[i]);
    }
    dp[p] = maxv + values[p];
    maxresult = max(maxresult, dp[p]);
  }

  printf("%d\n", maxresult);
}

int main(int argc, char const *argv[]) {
  int n;
  scanf("%d", &n);
  for (int data = 0; data < n; data++) {
    proceed();
  }
  return 0;
}
