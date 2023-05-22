#include <iostream>
#include <stack>

using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(false);
	int n;
	stack<int> w, m;
	cin >> n;

	for (int op, i = 0; i < n; ++i) {
		cin >> op;
		if (op == 0) {
			int x; cin >> x;
			w.push(x);
			if (m.empty()) m.push(x);
			else m.push(max(m.top(), x));
		} else if (op == 1) {
			if (!w.empty()) w.pop(), m.pop();
		} else {
			cout << (w.empty() ? 0 : m.top()) << '\n';
		}
	}
	return 0;
}
