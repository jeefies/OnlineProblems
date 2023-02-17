#include <iostream>
#include <cstdint>
#include <cmath>

#define int long long

int gcd(int a, int b) {
    int t;
    while (b) {
        t = a % b, a = b, b = t;
    }
    return a;
}

int exgcd(int a, int b, int *s, int *t) {
    if (b == 0) {
        *s = 1, *t = 0;
        return a;
    }

    int ot, r = exgcd(b, a % b, s, t);
    ot = *t, *t = *s - (a / b) * *t, *s = ot;
    return r;
}

void proc() {
    int a, b, c;
    scanf("%lld%lld%lld", &a, &b, &c);

    int s, t, sm, tm;
    int g = exgcd(a, b, &s, &t);
    // unsolvable
    if (c % g != 0) {
        printf("-1\n");
        return;
    }
    // 利用exgcd求出来的第一组解
    s *= c/g, t *= c/g;

    // 当 s增加 r2, t 需要减少 r1
    int r1 = a / g, r2 = b / g;

    // 求最小s，最大t
    int k = ceil((1 - s) * 1.0 / r2);
    s += r2 * k, t -= r1 * k;

    // 求最大sm，最小tm
    int km = ceil((1.0 - t) / r1);
    sm = s - r2 * km, tm = t + r1 * km;

    if (t <= 0) {
        // 没有正整数解
        printf("%lld %lld\n", s, tm);
    } else {
        printf("%lld ", (sm - s) / r2 + 1); // 解的个数
        printf("%lld %lld %lld %lld\n", s, tm, sm, t);
    }

}

signed main() {
    int T;
    scanf("%lld", &T);
    while (T--) {
        proc();
    }
}