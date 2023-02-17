#include <cstdio>
#include <algorithm>

typedef unsigned int uint;
namespace fastIO {
	const uint BUF_LEN = 1<<17|1;
	char buf[BUF_LEN], *ps = buf, *pe = buf;
	FILE * fp = stdin;
	
	inline void open(const char * fn) {
		fp = fopen(fn, "rb");
	}
	
	#define gc() (ps == pe && (pe = (ps = buf) + fread(buf, 1, BUF_LEN, fp), pe == ps) ? EOF : *ps++)
	template <typename T>
	inline void read(T &x) {
		register char tmp, f(0); x = 0;
		do if ((tmp = gc()) == '-') f = 1; while (tmp < '0' || '9' < tmp);
		do x = (x<<1) + (x<<3) + (tmp ^ 48), tmp = gc(); while ('0' <= tmp && tmp <= '9');
		if (f) x = -x;
	}
	template <typename T, typename ...Args>
	inline void read(T &x, Args&... args) {
		read(x), read(args...);
	}
};
using fastIO::read;

const int N = 1e6 + 7;

struct Ques {
	int l, r, i;
	
	bool operator< (const Ques &q) {
		return r < q.r;
	}
};

Ques ques[N];
int a[N], res[N], exi[N];

#define lowbit(i) (i & -i)
class BIT {
private:
	int b[N];
public:
	void update(int i, int x) {
		for (; i < N; i += lowbit(i)) b[i] += x;
	}
	
	int query(int i) {
		int r = 0;
		for (; i; i -= lowbit(i)) r += b[i];
		return r;
	}
};

int main() {
	// fastIO::open("P1972.in");
	
	int n;
	// scanf("%d", &n);
	read(n);
	
	for (int i = 1; i <= n; ++i) {
		// scanf("%d", a + i);
		read(a[i]);
	}
		
	int m;
	register Ques * qptr = ques;
	// scanf("%d", &m);
	read(m);
	for (int i = 1; i <= m; ++i, ++qptr) {
		// scanf("%d %d", &ques[i].l, &ques[i].r);
		read(qptr->l, qptr->r);
		qptr->i = i;
		// ques[i].i = i;
	}
	std::sort(ques, qptr);
	
	
	int r = 0;
	static BIT bit;
	qptr = ques;
	for (int i = 1; i <= m; ++i, ++qptr) {
		while (r < qptr->r) {
			++r;
			if (exi[a[r]]) bit.update(exi[a[r]], -1);
			bit.update(r, 1);
			exi[a[r]] = r;
		}
		res[qptr->i] = bit.query(qptr->r) - bit.query(qptr->l - 1);
	}
	
	for (int i = 1; i <= m; ++i) {
		printf("%d\n", res[i]);
	}
	
	return 0;
}