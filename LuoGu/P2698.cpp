#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

struct XY {
	int x, y;
	
	bool operator < (const XY &xy) const {
		return x < xy.x;
	}
};

const int N = 1e5 + 2;

XY xy[N];
int n, d;

void prt(deque<int> & dq) {
	for (int i = 0; i < dq.size(); i++) {
		printf("%d, ", dq[i]);
	}
	putchar('\n');
}

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
	// freopen("P2698_2.txt", "r", stdin);
	
	scanf("%d %d", &n, &d);
	for (int i = 0; i < n; i++)
		scanf("%d %d", &xy[i].x, &xy[i].y);
	
	std::sort(xy, xy + n);
	for (int i = 0; i < n; i++) {
		// printf("xy[%d] = {%d, %d}\n", i, xy[i].x, xy[i].y);
	}
	
	int sk = 0, bk = xy[n - 1].x;
	
	if (!valid(bk)) {
		std::cout << -1;
		return 0;
	}
	while (sk < bk) {
		// printf("Searching [%d, %d]\n", sk, bk);
		int mid = (sk + bk) / 2;
		if (valid(mid)) bk = mid;
		else {
			if (sk == mid) break;
			sk = mid;
		}
	}
	std::cout << bk;
	return 0;
}
