#include <assert.h>

#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <fstream>
#include <iostream>

/*
This file is for data structures' templates temporarily test, would be merge to templates.cpp
*/

// N is the scale of the data, M may for graph
const int N = 1e2, M = 1e5;


typedef int64_t i64;
// High precision Int
class HPInt {
private:
    // to reduce for loop times, use uint64 (base 1e9) instead of char (base 10)
    // int32 is also ok with base 1e4
    // space would not be saved !!
    int len; // if len < 0, means the number is negetive.
    i64 v[N];

    const static int MOD = 1e9;
public:
    HPInt(int x = 0) {
        this->init((i64)x);
    }

    HPInt(i64 x) {
        this->init(x);
    }

    HPInt(const HPInt &hp) {
        this->init(hp);
    }

    void init(i64 x) {
        memset(v, 0, sizeof(v));
        v[0] = x % MOD, v[1] = x / MOD;
        len = (v[1] ? 2 : (v[0] ? 1 : 0));
    }

    void init(const HPInt &hp) {
        this->init(0);
        len = hp.len;
        for (int i = 0; i < len; ++i) v[i] = hp.v[i];
    }

    HPInt operator+ (const HPInt &b) {
        HPInt r(*this);
        return (r += b);
    }

    HPInt & operator+= (const HPInt &b) {
        int ws = std::max(len, b.len);
        int i;
        for (i = 0; i <= ws; ++i) {
            v[i] += b.v[i];
            v[i + 1] += v[i] / MOD;
            v[i] %= MOD;
        }
        while (!v[i]) i--;
        len = i + 1;
        return *this;
    }

    HPInt operator- (const HPInt &b) {
        HPInt r(*this);
        return (r -= b);
    }

    HPInt & operator-= (const HPInt &b) {
        int ws = std::max(len, b.len);
        int i;
        for (i = 0; i <= ws; ++i) {
            v[i] -= b.v[i];
            if (v[i] < 0) {
                v[i] += MOD;
                v[i + 1] -= 1;
            }
        }
        while (!v[i]) i--;
        len = i + 1;
        return *this;
    }

    HPInt operator*(const HPInt &b) {
        HPInt r(*this);

        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < b.len; ++j) {
                r.v[i + j] = v[i] * b.v[j];
                r.v[i + j + 1] += r.v[i + j] / MOD;
                r.v[i + j] %= MOD;
            }
        }

        r.len = len + b.len + 1;
        while (r.v[r.len]) --r.len;
        ++r.len;

        return r;
    }

    HPInt & operator*= (const HPInt &b) {
        this->init(*this * b);
        return *this;
    }

    void print(bool newline = true) {
        int i = len;
        while (i && !v[i]) i--;
        printf("%lld", v[i--]);
        while (i >= 0) printf("%09lld", v[i--]);
        if (newline) putchar('\n');
    }

    bool operator==(const HPInt &b) {
        if (len != b.len) return false;
        for (int i = 0; i < len; ++i) 
            if (v[i] != b.v[i]) return false;
        return true;
    }

    bool operator!=(const HPInt &b) {
        return !(*this == b);
    }

    bool operator< (const HPInt &b) {
        if (len < b.len) return true;
        if (len > b.len) return false;

        for (int i = len - 1; i >= 0; --i) {
            if (v[i] < b.v[i]) return true;
            if (v[i] > b.v[i]) return false;
        }
        return false; // equal
    }

    bool operator> (const HPInt &b) {
        if (len < b.len) return false;
        if (len > b.len) return true;

        for (int i = len - 1; i >= 0; --i) {
            if (v[i] < b.v[i]) return false;
            if (v[i] > b.v[i]) return true;
        }
        return false; // equal
    }
};

int main() {
    i64 x, y;
    scanf("%lld%lld", &x, &y);

    if (x < y) std::swap(x, y);

    HPInt a, b;
    bool neg = false;
    if (x < 0) {
        // both smaller than 0
        a.init(-x), b.init(-y);
        putchar('-');
        (a + b).print();
        return 0;
    }

    if (y < 0) {
        // just y smaller than 0
        y = -y;

        if (x < y) std::swap(x, y), neg = true;

        if (neg) putchar('-');
        a.init(x), b.init(y);
        (a - b).print();
        return 0;
    }

    // all positive
    a.init(x), b.init(y);
    (a + b).print();

    return 0;
}