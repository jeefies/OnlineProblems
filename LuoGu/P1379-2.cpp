#include <iostream>
#include <queue>

using namespace std;

typedef long long ll;

struct STAT {
	ll status, steps;
	int li;
};

ll e[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
inline ll swapNum(ll os, ll i, ll j) {
	ll tn = (os / e[i]) % 10;
	os -= e[i] * tn;
	os += e[j] * tn;
	
	return os;
}

long long bfs(ll b) {
	queue<STAT> que;
	STAT st = {b, 0, -1};
	que.push(st);
	
	register ll status, steps, li;
	while (que.size()) {
		st = que.front();
		que.pop();
		status = st.status;
		steps = st.steps;
		li = st.li;
		
		static ll target = 123804765;
		if (status == target) return steps;
		
		ll pos;
		for (pos = 0; pos <= 9; pos++) {
			if ((status / e[pos]) % 10 == 0) break;
		}
		
		ll x = pos % 3, y = pos / 3;
		static ll dx[4] = {0, 1, -1, 0};
		static ll dy[4] = {1, 0, 0, -1};
		for (int i = 0; i < 4; i++) {
			if (i == li) continue;
			
			ll cx = x + dx[i], cy = y + dy[i];
			if (cx < 0 || cx >= 3 || cy < 0 || cy >= 3) continue;
			ll next = swapNum(status, cx + cy * 3, pos);
			
			que.push({next, steps + 1, 3 - i});
		}
	}
}

signed main() {
	ll origin = 283104765;
	cin >> origin;
	cout << bfs(origin);
}
