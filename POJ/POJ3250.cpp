#include <stack>
#include <iostream>

using namespace std;

const int MAXN = 80002;
const int MAXH = 1e9 + 2;

stack<int> stk;
int h[MAXN];

int main() {
	int n;
	scanf("%d", &n); 
	
	for (int i = 0; i < n; i++) scanf("%d", h + i);
	h[n] = MAXH;
	
	long long r = 0;
	for (int i = 0; i <= n; i++) {
		while (!stk.empty() && h[stk.top()] <= h[i]) {
			r += i - stk.top() - 1;
			stk.pop();
		}
		stk.push(i); 
	}
	
	// cout << r;
	printf("%I64d", r);
	return 0;
	
}
