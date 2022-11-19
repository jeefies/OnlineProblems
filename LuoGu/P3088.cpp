#include <iostream>
#include <algorithm>

const int N = 50000;
struct XH {
	int x, h;
	bool operator < (const XH & r) const {
		return x < r.x; 
	}
};
int que[N], L[N], R[N], head = 0, tail = -1;
XH xh[N];

signed main() {
	int n, d;
	scanf("%d %d", &n, &d);
	XH *xhptr = xh;
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &xhptr->x, &xhptr->h), ++xhptr;
	}
	std::sort(xh, xh + n);
	
	for (int i = 0; i < n; i++) {
		while (head <= tail && xh[que[head]].x + d < xh[i].x) ++head;
		while (head <= tail && xh[que[tail]].h <= xh[i].h) --tail;
		que[++tail] = i;
		L[i] = que[head];
		
		// printf("L[%d] is %d\n", xh[i].x, xh[L[i]].x);
	}
	
	head = 0, tail = -1;
	for (int i = n - 1; i >= 0; i--) {
		while (head <= tail && xh[que[head]].x > xh[i].x + d) ++head;
		while (head <= tail && xh[que[tail]].h <= xh[i].h) --tail;
		que[++tail] = i;
		R[i] = que[head];
		
		// printf("R[%d] is %d\n", xh[i].x, xh[R[i]].x);
	}
	
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (xh[L[i]].h >= xh[i].h * 2 && xh[R[i]].h >= xh[i].h * 2) cnt += 1;
	}
	std::cout << cnt;
	return 0;
}
