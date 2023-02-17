#include <iostream>
#include <cmath>

#define int long long

int exgcd(int a, int b, int *s, int *t) {
    if (b == 0) {
        *s = 1, *t = 0;
        return a;
    }

    int ot, r = exgcd(b, a % b, s, t);
    ot = *t, *t = *s - (a / b) * *t, *s = ot;
    return r;
}

signed main() {
    int x, y, m, n, l;
    scanf("%lld%lld%lld%lld%lld", &x, &y, &m, &n, &l);
    int a = x - y, b = n - m;
    if (b < 0) a = -a, b = -b; // avoid b negetive.
    
    int s, t;
    int g = exgcd(b, l, &s, &t);
    s *= a / g, t *= a / g;
    // printf("Origin solution s, t = %lld, %lld\n", s, t);
    if (a % g != 0) {
        // invalid answer
        printf("Impossible\n");
    } else {
        // 需要求最小的大于0的s
        int mod = l / g;
        printf("%lld\n", ((s % mod) + mod) % mod);
    }
}