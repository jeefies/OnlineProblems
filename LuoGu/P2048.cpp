#include <iostream>
#include <algorithm>
#include <cstring>

const int N = 5e5 + 7;

int n, k, L, R;
int prefix[N] = {0};

int readInt() {
	int n = 0, f = 1;
	char tmp;
	do {
		if ((tmp = getchar()) == '-') f = -1;
	} while (tmp < '0' || '9' < tmp);
	do {
		n = n * 10 + tmp - '0';
		tmp = getchar();
	} while ('0' <= tmp && tmp <= '9');
	return n * f;
}

void read() {
	scanf("%d %d %d %d", &n, &k, &L, &R);
	for (int i = 1; i <= n; ++i) {
		prefix[i] = readInt() + prefix[i - 1];
	}
}

class Heap {
private:
	int heap[N * 2];
public:
	int size;
	
	Heap() : size(0) {
		memset(heap, 0x7F, sizeof(heap));
	}
	
	void down(int p) {
		int c = p * 2;
		while (c <= size) {
			// choose smaller one, top should be least.
			if (c < size && heap[c] > heap[c + 1]) ++c;
			if (heap[p] > heap[c]) {
				std::swap(heap[p], heap[c]);
				p = c, c = p * 2;
			} else {
				break;
			}
		}
	}
	
	void up(int p) {
		int c;
		while (p > 1) {
			c = p >> 1;
			if (heap[p] < heap[c]) {
				std::swap(heap[p], heap[c]);
				p = c;
			} else break;
		}
	}
	
	void topTo(int val) {
		if (size == 0) heap[++size] = val;
		else {
			heap[1] = val;
			down(1);
		}
	}
	
	int top() {
		return heap[1];
	}
	
	void insert(int val) {
		heap[++size] = val;
		up(size);
	}
	
	long long sum() {
		long long r = 0;
		for (int i = 1; i <= size; ++i) {
			r += heap[i];
		}
		return r;
	}
};

Heap hp;
int main() {
	read();
	int sum;
	for (int len = L; len <= R; ++len) {
		// [i, i + L), sum = prefix[i + len - 1] - prefix[i - 1]
		for (int i = 1; i + len - 1 <= n; ++i) {
			sum = prefix[i + len - 1] - prefix[i - 1];
			
			if (hp.size == k) {
				if (sum > hp.top()) hp.topTo(sum);
			} else {
				hp.insert(sum);
			}
			
			if (hp.size > k) return 1;
		}
	}
	printf("%lld\n", hp.sum());
	return 0;
}