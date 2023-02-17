#include <assert.h>
#include <math.h>

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
This file is for data structures' templates
*/

// N is the scale of the data, M may for graph
const int N = 1e2, M = 1e5;

// Fast read Integer
template<typename T>
inline void read(T &x) {
	char c, f(0); x = 0;
	do if ((c = getchar()) == '-') f = true; while (isspace(c));
	do x = (x<<3) + (x<<1) + (c ^ 48), c = getchar(); while (isdigit(c));
	if (f) x = -x;
}
template <typename T, typename ...Args> inline void read(T &t, Args&... args) { read(t), read(args...); }


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

// a*b % p, magical O(1)
int quickMul1(int a, int b, int p) {
    return ((unsigned long long)a * b - (unsigned long long)((long double)a / p * b) * p + p) % p;
}

// a*b % p, scientifically O(1)
int quickMul2(int a, int b, int p) {
    const static int n = 15, MASKR = (1<<n)-1, OFFSETN = 1<<n;
    // 15 may ok under int, 27 may better under long long
    return ((a>>n) % p * OFFSETN % p * b + (a & MASKR) % p * b) % p;
}

// (a**x) % p
template <typename T>
T quickPow(T a, T x, const int p) {
    T r = 1;
    while (x) {
        // no need to use quickMul when p*p can be smaller than int64.max !!!
        if (x & 1) r = (r * a) % p;
        a = (a * a) % p, x >>= 1;
    }
    return r;
}

template<typename data>
data BSGS(data a, data b, data p) {
	b %= p;
	static std::map<data, data> hash; hash.clear();
	// t ceil
	data t = std::ceil(std::sqrt(p)), v(1), j(0);
	
	for (; j < t; ++j) {
		hash[v * b % p] = j;
		v = v * a % p;
	}
	
	a = qpow(a, t, p), v = 1;
	/* 
	if a^t \equiv 0 mod p
	means a | p
	means \forall k a^k \equiv 0 mod p
	so it can work out a^l \equiv b mod p only if b == 0, or there's no solution
	*/
	if (a == 0) return b == 0 ? 1 : -1;
	
	// here a we already make it to a^t, so we only need ^s and find it.
	for (data s(0); s <= t; ++s) {
		j = hash.find(v) == hash.end() ? -1 : hash[v];
		if (~j && s * t >= j) return s * t - j;
		v = v * a % p;
	}
	return -1;
}

template<typename data>
data exBSGS(data a, data b, data p) {
	a %= p, b %= p;
	// a^0 = 1, a^k = 0 mod p
	if (b == 1 || p == 1) return 0;
	// d for gcd, ak for a^k / D
	data d, ak(1), k(0);
	while ((d = gcd(a, p)) != 1) {
		if (b % d) return -1;
		++k, p /= d, b /= d;
		ak = a / d * ak % p;
		if (ak == b) return k;
	}
	
	// a^k/D * a^res \equiv b / D mod p / D
	// a^res \equiv b / D * inv(a^k/D) mod p/D
	// if gcd(a, p) == 1, b = b * inv(1 / 1) % p = b % p;
	// means it's normal BSGS algorithm
	b = b * inv(ak, p) % p;
	
	data res = BSGS(a, b, p);
	if (~res) return res + k;
	return -1;
}

// in euler theory. get \varphi(x) 
int getphi(int x) {
	int phi = x;
	for (int i = 2; i * i <= x; ++i) {
		if (x % i) continue;
		phi = phi / i * (i - 1);
		do x /= i; while (x % i == 0);
	}
	if (x > 1) phi = phi / x * (x - 1);
	return phi;
}

// O(logn), get greatest common division
// gcd(x, y) = gcd(y, x % y);
template<typename T>
T gcd(T x, T y) {
    T t;
	while (y) {
        t = x % y, x = y, y = t;
    }
	return x;
}

template<typename T>
T exgcd(T a, T b, T *s, T *t) {
    if (b == 0) {
        *s = 1, *t = 0;
        return a;
    }
    T r = exgcd(b, a % b, t, s);
    *t -= (a / b) * *s;
    return r;
}

// O(n), get all prime smaller than n, or can make up to N
int getPrime(int n, int * prm) {
    int plen = 0;
    static int notp[N]; // memset(notp, 0, sizeof(notp));

    for (int i = 2; i <= n; ++i) {
        if (!notp[i]) prm[plen++] = i;

        int k;
        for (int j = 0; j < plen && (k = prm[j] * i) <= n; ++j) {
            notp[k] = true;
            if (i % k == 0) break; // make sure i is the smallest prime factor of the number
        }
    }
    return plen;
}

class MergeFindSet {
private:
    int grp[N];
public:
    void init(int n) {
        for (int i = 1; i <= n; ++i) grp[i] = i;
    }

    void merge(int x, int y) {
        grp[find(x)] = find(y);
    }

    int find(int x) {
        static int o; o = x;
        while (grp[x] != x) x = grp[x];
        return grp[o] = x;
        /* find can also write as: (but notice that the space of stack!!!)
        if (grp[x] != x) return grp[x] = find(grp[x]);
        else return x;
        */
    }
};

template<typename T>
class MergeFindSetMap {
private:
    std::map<T, T> grp;
public:
    void init(const T &key) {
        grp[key] = key;
    }

    void merge(const T &a, const T &b) {
        grp[find(a)] = find(b);
    }

    const T& find(const T &x) {
        T k = x; // use k to avoid change the value of x
        while (grp[k] != k) k = grp[k];
        return grp[x] = k;
    }
};

class Log2Factory {
private:
    int lg2[N];
public:
    void init(int n) {
        for (int i = 2; i <= n; ++i) lg2[i] = lg2[i >> 1] + 1;
    }

    int operator() (const int &i) {
        return lg2[i];
    }
};

template<typename T>
class STable {
private:

    typedef T(*OP_FUNC)(T, T);
    Log2Factory Log2;
    T f[N][17]; // maybe most of the times k=17 is ok, make sure 2^k greater than N;
    OP_FUNC op;
public:
    void setOp(OP_FUNC fc) {
        op = fc;
    }

    void init(T *a, int n) {
        for (int i = 1; i <= n; ++i)
            f[i][0] = *(++a);

        int t = Log2(n);
        // f[i][k] is the area of [i, i + 2^k - 1]
        // so f[i][k] can equal to the op sum of [i, i^k - 1]
        // let r = i^k - 1
        // => f[r - (1^k) + 1][k] can equal to the op sum of [i][k]
        for (int k = 1; k <= t; ++k) {
            for (int i = 1; i + (1<<k) - 1 <= n; ++i)
                f[i][k] = op(f[i][k-1], f[i + (1<<(k-1))][k-1]);
        }
    }

    const T query(int l, int r) {
        int k = Log2(r - l + 1);
        return op(f[l][k], f[r - (1<<k) + 1][k]);
    }
};

#define lowbit(i) (i & -i)
class BIT {
private:
    int b[N];
public:
    void update(int i, int d) {
        while (i < N)
            b[i] += d, i += lowbit(i);
    }

    int query(int i) {
        int r = 0;
        while (i)
            r += b[i], i -= lowbit(i);
        return r;
    }
};

// Not a simple Queue, but a ring
template<typename T>
class Queue {
private:
    int head, tail, len, cap;
    T q[N];
public:
    Queue() : head(0), tail(0), len(0), cap(N) {}

    // return false if cannot push  anymore
    bool push(T v) {
        if (++len > N) return false;
        q[tail++ % N] = v;
        return true;
    }

    bool empty() {
        return head == tail;
    }

    int size() {
        return len;
    }

    T pop() {
        --len;
        return q[head++ % N];
    }
};

struct Edge {
    int next, to, w;
};


int vis[N];
class Graph {
private:
    int head[N], tot;
    Edge edge[M];
public:
    int n;

    void add(int u, int v) {
        add(u, v, 0);
    }

    void add(int u, int v, int w) {
        edge[++tot] = {head[u], v, w}, head[u] = tot;
    }

    void clear() {
        tot = n = 0;
        memset(head, 0, sizeof(head));
    }

    void djk(int s, int * dis) {
        memset(vis, 0, sizeof(vis));
        typedef std::pair<int, int> pii;
        // I would like to explain a bit about why I use priority_queue
        // 1. build a heap by my self is complicated, although it's faster without `-O2`
        // 2. However, std::priority_queue is much more flexible and space reduced.
        // 3. NOIP use `-O2` which makes priority_queue faster than self-build heap.
        std::priority_queue<pii, std::vector<pii>, std::greater<pii> > que;

        dis[s] = 0;
        que.push(std::make_pair(0, s));

        while (que.size()) {
            int x = que.top().second; que.pop();
            if (vis[x]) continue;
            vis[x] = true;

            for (int i = head[x]; i; i = edge[i].next) {
                int y = edge[i].to, w = edge[i].w;
                if (!vis[y] && dis[y] > dis[x] + w) {
                    dis[y] = dis[x] + w;
                    que.push(std::make_pair(dis[y], y));
                }
            }
        }
        // DJK finish
    }

    // if false return, means negetive ring exists
    bool spfa(int s, int * dis) {
        static int it[N]; memset(it, 0, sizeof(it));
        static int iq[N]; memset(iq, 0, sizeof(iq));

        Queue<int> q; q.push(s);
        dis[s] = 0, iq[s] = true;

        while (q.size()) {
            int x = q.pop();
            iq[x] = false;

            for (int i = head[x]; i; i = edge[i].next) {
                int y = edge[i].to, w = edge[i].w;
                if (dis[y] > dis[x] + w) {
                    dis[y] = dis[x] + w;
                    if (!iq[y]) {
                        iq[y] = true, q.push(y);
                        if (++it[y] > n) return false;
                    }
                }
            }
        }
        return true;
    }

    bool markBipartile(int x, int c, int * color) {
        vis[x] = 1;
        color[x] = c;

        for (int i = head[x]; i; i = edge[i].next) {
            int y = edge[i].to;
            if (vis[y] && color[y] + c != 3) {
                return false;
            }
            if (!vis[y])
                if (!markBipartile(y, 3 - c, color)) return false;
        }
        return true;
    }

    // 二分图
    int isBipartile() {
        static int color[N]; memset(color, 0, sizeof(color));
        memset(vis, 0, sizeof(vis));
        return markBipartile(1, 1, color);
    }
};

class TestReader {
private:
    std::ifstream reader;
public:
    TestReader() {
        reader.open("./templates-testdata.in");
    }

    int readInt() {
        static char tmp;
        
        int f = 1, x = 0;
        do {
            reader.get(tmp);
            if (tmp == '-') f = -1;
        } while (tmp < '0' || tmp > '9');
        do {
            x = x * 10 + tmp - '0';
            reader.get(tmp);
        } while ('0' <= tmp && tmp <= '9' && !reader.eof());
        return f * x;
    }
};

int main() {
    // For Test
    TestReader reader;
    int n, m, i, j, k, u, v, w;

    // Test QuickPow and QuickMul
    // I have tested in P1226, see the history of LuoGu
    printf("Test quickMul 1, 2, 3 and quickPow OK\n");

    // Test MergeFindSet
    // MergeFindSet need not to test
    printf("Test MergeFindSet OK\n");

    // Test MergeFindSetMap
    static MergeFindSetMap<int> mfsm;

    n = reader.readInt();
    while (n--) mfsm.init(reader.readInt());

    n = reader.readInt();
    while (n--) mfsm.merge(reader.readInt(), reader.readInt());

    n = reader.readInt();
    while (n--) assert(mfsm.find(reader.readInt()) == mfsm.find(reader.readInt()));
    printf("Test MergeFindSetMap OK\n");

    // Test STable
    int (*max)(int, int) = [](int a, int b) {
        return a > b ? a : b;
    };
    static STable<int> st;
    st.setOp(max);

    static int numbers[N];
    n = reader.readInt(), i = 1;
    do numbers[i++] = reader.readInt(); while (i <= n);
    st.init(numbers, n);

    n = reader.readInt();
    while (n--) {
        i = reader.readInt(), j = reader.readInt(), k = reader.readInt();
        assert(st.query(i, j) == k);
    }
    printf("Test STable OK\n");

    // Test BIT
    static BIT bit;
    n = reader.readInt();
    while (n--) {
        i = reader.readInt(), j = reader.readInt();
        bit.update(i, j);
    }
    
    n = reader.readInt();
    while (n--) {
        i = reader.readInt(), j = reader.readInt();
        assert(bit.query(i) == j);
    }
    printf("Test BIT OK\n");

    // Test Graph
    printf("Test Graph:\n");
    // Test djk
    static Graph g;
    g.n = reader.readInt();
    m = reader.readInt();
    int s = reader.readInt();
    while (m--) {
        u = reader.readInt(), v = reader.readInt(), w = reader.readInt();
        g.add(u, v, w);
    }

    // numbers for ans
    i = 0;
    do numbers[++i] = reader.readInt(); while (i < g.n);

    static int dis[N];
    memset(dis, 0x3F, sizeof(dis));
    g.djk(1, dis);
    for (int i = 1; i <= 4; ++i) {
        // assert(dis[i] == numbers[i]);
        printf("%d ", numbers[i]);
    } putchar('\n');
    printf("\tTest Graph DJK ok\n");

    memset(dis, 0x3F, sizeof(dis));
    g.spfa(1, dis);
    for (int i = 1; i <= 4; ++i) {
        assert(dis[i] == numbers[i]);
        printf("%d ", dis[i]);
    } putchar('\n');

    printf("\tTest Graph SPFA ok\n");

    i = 2;
    while (i--) {
        g.clear();
        g.n = reader.readInt();
        m = reader.readInt();
        while (m--) {
            u = reader.readInt(), v = reader.readInt();
            g.add(u, v);
            g.add(v, u);
        }

        bool isTrue = (bool)reader.readInt();
        std::cout << "Want " << isTrue << std::endl;
        assert(g.isBipartile() == isTrue);
        printf("\t\tTest isBipartile group %d ok\n", 2 - i);
    }
    printf("\tTest isBipartile OK\n");

    return 0;
}
