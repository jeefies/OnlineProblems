#include <bits/stdc++.h>

using namespace std;

bool trees[30002] = {false};

struct req {
	int b, e, t;
} reqs[5002];

bool cmp (req r1, req r2) {
	return r1.e < r2.e;
}

int main() {
	int n, h;
	cin >> n >> h;
	
	for (int i = 0; i < h; i++) {
		cin >> reqs[i].b >> reqs[i].e >> reqs[i].t;
	}
	
	sort(reqs, reqs + h, cmp);
	
	int c = 0, b, e, t;
	req tmp;
	for (int i = 0; i < h; i++) {
		tmp = reqs[i];
		b = tmp.b, e = tmp.e, t = tmp.t;
		for (int ix = b; ix <= e; ix++) {
			if (trees[ix]) t--;
		}
		
		for (int ix = e; ix >= b && t > 0; ix--) {
			if (!trees[ix]) --t, ++c, trees[ix] = true;
		}
	}
	
	cout << c << endl;
	return 0;
}
