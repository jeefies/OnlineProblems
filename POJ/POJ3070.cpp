#include <iostream>
#include <vector>
#include <cstdint>

typedef std::vector<int> vec;
typedef std::vector<vec> mat;

mat mul(const mat &a, const mat &b, int mod) {
    // a: n*m, b: m*s
    size_t n = a.size(), m = a[0].size(), s = b[0].size();

    mat ans(n, vec(s, 0));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < s; ++j)
            for (size_t k = 0; k < m; ++k) {
                ans[i][j] = (ans[i][j] + a[i][k] * b[k][j]) % mod;
            }
    }

    return ans;
}

// a ** b % p;
void quickMatPow(mat &ans, mat base, int b, int p) {
    while (b) {
        if (b & 1) ans = mul(base, ans, p);
        b >>= 1, base = mul(base, base, p);
    }
}

int main() {
    int n;
    const int MOD = 10000;

    mat base {
        {1, 1},
        {1, 0},
    };

    while (~scanf("%d", &n)) {
        mat ans = {
            {1},
            {1},
        };
        
        if (n <= 2) {
            printf("%.2f\n", n ? 1.0 : 0.0);
            continue;
        }
        quickMatPow(ans, base, n - 2, MOD);
        // printf("Ans mat:\n");
        // prtMat(ans);
        printf("%.2f\n", (float)ans[0][0]);
    }
}