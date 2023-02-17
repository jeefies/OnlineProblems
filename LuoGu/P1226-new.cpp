#include <iostream>

#define int long long

// for testing template

// a*b % p O(log b)
int quickMul(int a, int b, int p) {
    if (a < b) std::swap(a, b);
    
    int r = 0;
    while (b) {
        if (b & 1) r = (r + a) % p;
        a = (a<<1) % p, b >>= 1;
    }
    return r;
}

// a*b % p, scientifically O(1)
int quickMul2(int a, int b, int p) {
    const static int n = 25, MASKR = (1<<n)-1, OFFSETN = 1<<n;
    return ((a>>n) % p * OFFSETN % p * b + (a & MASKR) % p * b) % p;
}

// (a**x) % p
int quickPow(int a, int x, int p) {
    int r = 1;
    while (x) {
        if (x & 1) r = quickMul2(a, r, p);
        a = quickMul2(a, a, p), x >>= 1;
    }
    return r;
}

signed main() {
    int a, x, m;
    std::cin >> a >> x >> m;
    std::cout << a << '^' << x << " mod " << m << '=' << quickPow(a, x, m) << std::endl;
}