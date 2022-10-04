#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdint.h"
#include "limits.h"

int fc, v;
int beauty[100][100];
int in[100][100];

int max(int a, int b) {
    return a > b ? a : b;
}

void print(int i, int k) {
    if (i > 0) {
        print(i - 1, in[i][k] - 1);
    }
    printf("%d ", in[i][k] + 1);
}

int main(int argc, char const *argv[]) {
    scanf("%d%d", &fc, &v);
    for (int i = 0; i < fc; i++) {
        for (int j = 0; j < v; j++) {
            scanf("%d", beauty[i] + j);
        }
    }

    for (int i = 0; i < fc; i++) {
        for (int j = i; j < v; j++) {
            // printf("beauty[%d][%d] origin %d ", i, j, beauty[i][j]);

            int notthis = (j > 0 ? beauty[i][j - 1] : INT_MIN);
            int choosethis = (i > 0 ? beauty[i - 1][j - 1] : 0) + beauty[i][j];
            if (notthis < choosethis) {
                in[i][j] = j;
                beauty[i][j] = choosethis;
            } else {
                in[i][j] = j > 0 ? in[i][j - 1] : -1;
                beauty[i][j] = notthis;
            }

            // printf("set to %d\n", beauty[i][j]);
        }
    }

    printf("%d\n", beauty[fc - 1][v - 1]);
    print(fc - 1, v - 1);
    return 0;
}
