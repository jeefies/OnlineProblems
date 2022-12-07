#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <fstream>
#include <iostream>

/*
This file is for data structures' templates
*/

// N is the scale of the data, M may for graph
const int N = 1e2, M = 1e5;

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
    void setOp(OP_FUNC fk) {
        op = fk;
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