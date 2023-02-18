#include <algorithm>
#include <iostream>

using namespace std;
const int N = 2e6, BLOCK = (1<<9);

struct Ques {
	int l, r, i;
} ques[N];

int prefix[N];
long long tot(0), res[N];
long long but[N];

int n, m, k;

void add(int x) {
	tot += but[k ^ x];
	++but[x];
}

void del(int x) {
	--but[x];
	tot -= but[k ^ x];
}

int main() {
	cin.tie(0)->sync_with_stdio(false);

	cin >> n >> m >> k;
	int x;
	for (int i(1); i <= n; ++i) {
		cin >> x;
		prefix[i] = prefix[i - 1] ^ x;
	}

	Ques * q = ques;
	for (int i(0); i ^ m; ++i, ++q) {
		cin >> q->l >> q->r;
		q->i = i;
		--q->l;
	}

	sort(ques, q, [](const Ques &x, const Ques &y) {
		if ((x.l>>9) ^ (y.l>>9)) return x.l < y.l;
		return ((x.l>>9) & 1) ? x.r > y.r : x.r < y.r;
	});

	q = ques;
	int l(1), r(0);
	for (int i(0); i ^ m; ++i, ++q) {
		while (r < q->r) add(prefix[++r]);
		while (r > q->r) del(prefix[r--]);
		while (l < q->l) del(prefix[l++]);
		while (l > q->l) add(prefix[--l]);

		res[q->i] = tot;
	}

	for (int i(0); i ^ m; ++i) {
		cout << res[i] << '\n';
	} cout << flush;
	return 0;
}
