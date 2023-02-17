#include <cstdio>
#include <algorithm>

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
	int n;
	scanf("%d", &n);
	
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
		
	int m;
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", &ques[i].l, &ques[i].r);
		ques[i].i = i;
	}
	
	std::sort(ques + 1, ques + m + 1);
	
	int r = 0;
	register Ques * ptr = ques + 1;
	static BIT bit;
	for (int i = 1; i <= m; ++i) {
		while (r < ptr->r) {
			++r;
			if (exi[a[r]]) bit.update(exi[a[r]], -1);
			bit.update(r, 1);
			exi[a[r]] = r;
		}
		res[ptr->i] = bit.query(ptr->r) - bit.query(ptr->l - 1);
		++ptr;
	}
	
	for (int i = 1; i <= m; ++i) {
		printf("%d\n", res[i]);
	}
	
	return 0;
}