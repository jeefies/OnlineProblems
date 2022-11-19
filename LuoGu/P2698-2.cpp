#include <iostream>
#include <deque>
#include <algorithm>

struct XY {
	int x, y;
	
	bool operator < (const XY &xy) const {
		return x < xy.x;
	}
};

const int N = 1e5 + 2;

XY xy[N];
int n, d;

bool valid(int k) {
	std::deque<int> big, small;
	for (int i = 0; i < n; i++) {
		while (big.size() && xy[big.front()].x < xy[i].x - k) big.pop_front();
		while (big.size() && xy[big.back()].y <= xy[i].y) big.pop_back(); big.push_back(i);

		while (small.size() && xy[small.front()].x < xy[i].x - k) small.pop_front();
		while (small.size() && xy[small.back()].y >= xy[i].y) small.pop_back(); small.push_back(i); 
		
		// prt(big); prt(small); putchar('\n');
		
		if (xy[big.front()].y - xy[small.front()].y >= d) return true;
	}
	return false;
}

int main() {
	scanf("%d %d", &n, &d);
	for (int i = 0; i < n; i++)
		scanf("%d %d", &xy[i].x, &xy[i].y);
	
	std::sort(xy, xy + n);
	for (int i = 0; i < n; i++) {
		// printf("(%d, %d)\n", xy[i].x, xy[i].y);
	}
	
	if (!valid(xy[n - 1].x)) {
		std::cout << -1;
		return 0;
	}
	
	int smallW = 1e9;
	std::deque<int> big, small;
	int r = 0;
	// 枚举左端点，更新右端点 
	for (int i = 0; i < n; i++) {
		while (big.size() && big.front() < i) big.pop_front();
		while (small.size() && small.front() < i) small.pop_front();
		if (r < i || big.empty() || small.empty()) {
			r = i;
			big.clear(); small.clear();
			big.push_back(i), small.push_back(i);
		}
		
		while (r < n && xy[big.front()].y - xy[small.front()].y < d) {
			++r;
			while (big.size() && xy[big.back()].y <= xy[r].y) big.pop_back(); big.push_back(r);
			while (small.size() && xy[small.back()].y >= xy[r].y) small.pop_back(); small.push_back(r);
		}
		if (xy[big.front()].y - xy[small.front()].y >= d)
			smallW = std::min(smallW, abs(xy[big.front()].x - xy[small.front()].x)); 
	}
	std::cout << (smallW >= 1e9 ? -1 : smallW);
	return 0;
}
