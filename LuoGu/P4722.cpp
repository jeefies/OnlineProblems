#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <stack>
#include <deque>

template<typename T>
inline void read(T &x) {
	char c, f = 0; x = 0;
	do if ((c = getchar()) == '-') f = true; while (isspace(c));
	do x = (x<<3) + (x<<1) + (c ^ 48), c = getchar(); while (isdigit(c));
	if (f) x = -x;
}
template <typename T, typename ...Args> inline void read(T &t, Args&... args) { read(t), read(args...); }

using namespace std;

const int N = 1200 + 7, M = 120000 + 7;

template <class T = int>
class HLPP {
public:
	const T INF = numeric_limits<T>::max();
	struct Edge {
		int to, rev; // target, reverse edge
		T flow;
	};
	
	int maxn, s, t;
};

int main()
	int n, m, s, t;
	read(n, m, s, t);
	--s, --t; // make node start from 0
	
	vector<array<int, 3>> v(m); // vertex
	vector<int> degs(n); // in and out times
	for (auto &e : v) {
		read(e[0], e[1], e[2]);
		// --e[0], --e[1]; !from 0
		++degs[--e[0]], ++degs[--e[1]];
	}
	
	HLPP hlpp(degs, s, t);
	for (auto &e : v) {
		hlpp.add(e[0], e[1], e[2]);
	}

