#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <cstring>

const int N = 1e8 + 7;

int getPrime(int n, int * prm) {
    int plen = 0;
    static int notp[N]; // memset(notp, 0, sizeof(notp));

    for (int i = 2; i <= n; ++i) {
        if (!notp[i]) prm[plen++] = i;

        int k;
        for (int j = 0; j < plen && (k = prm[j] * i) <= n; ++j) {
            notp[k] = true;
            if (i % prm[j] == 0) break;
        }
    }
    return plen;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    static int prm[N]; // memset(prm, 0, sizeof(prm));
    getPrime(n, prm);

    int k;
    while (q--) {
        scanf("%d", &k);
        printf("%d\n", prm[k - 1]);
    }

    return 0;
}