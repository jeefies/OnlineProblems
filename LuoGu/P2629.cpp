#include <iostream>
#include <deque>

const int N = 1e6;
int n;
int news[N], L[N], R[N];

int main() {
	scanf("%d", &n);
	int * ptr = news;
	for (int i = 0; i < n; i++) scanf("%d", ptr++);
	for (int i = 1; i < n; i++) news[i] += news[i - 1];
	 
	std::deque<int> dq;
	for (int i = 0; i < n; i++) {
		while (dq.size() && dq.back() >= news[i]) dq.pop_back();
		dq.push_back(news[i]);
		L[i] = dq.front();
		// printf("L[%d] = %d\n", i, L[i]);
	}
	while (dq.size()) dq.pop_back();
	for (int i = n - 1; i >= 0; i--) {
		while (dq.size() && dq.back() >= news[i]) dq.pop_back();
		dq.push_back(news[i]);
		R[i] = dq.front();
		// printf("R[%d] = %d\n", i, R[i]);
	}
	
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		int ni = i > 0 ? news[i - 1] : 0;
		if (R[i] - ni < 0) continue;
		if (news[n - 1] - ni + L[i] < 0) continue;
		++cnt;
	}
	std::cout << cnt;
	return 0;
}
