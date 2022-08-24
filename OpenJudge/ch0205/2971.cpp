#include <utility>
#include <tuple>
#include <iostream>
#include <queue>

using namespace std;

int ok = 0;
int okc = 0;

int k;

queue< pair<int, int> > q;
bool already[150000] = {false};

void push(int n, int c) {
	// cout << n << ' ' << c << endl;
	if (already[n]) return;
	q.push(make_pair(n, c));
	already[n] = true;
}

int next(int on) {
	q.push(make_pair(on, 0));

	while (!q.empty()) {
		int n, c;
		tie(n, c) = q.front();
		q.pop();

		if (n == k) {
			cout << c << endl;
			return 0;
		}

		c++;
		if (n < k) push(n + 1, c);
		if (n > 0) push(n - 1, c);
		if (n < k && n < 75000 && n > 1) push(n * 2, c);
	}
}

int main() {
	int n;
	cin >> n >> k;

	if (n >= k) {
		cout << n - k << endl;
		return 0;
	}

	next(n);
}
