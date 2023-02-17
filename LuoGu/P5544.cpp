#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <ctime>

template<typename T>
inline void read(T &x) {
	register char tmp, f(x = 0);
	do if ((tmp = getchar()) == '-') f = 1; while (tmp < '0' || '9' < tmp);
	do x = x * 10 + (tmp ^ 48), tmp = getchar(); while ('0' <= tmp && tmp <= '9');
	if (f) x = -x;
}
template<typename T, typename ...Args>
inline void read(T &x, Args&...args) {
	read(x), read(args...);
}

struct P {
	int x, y, r;
	bool operator < (const P & p) {
		return x < p.x;
	}
} build[13], enemy[2003];
int N, M, _R;
double R;

inline double pow2(double x) { return x * x; }
inline double distance(double x, double y, double a, double b) {
	return sqrt(pow2(x - a) + pow2(y - b));
}

inline int calc(int x, int y) {
	int cnt(0);
	double d = R;
	P * ptr = build;
	// find valid d
	for (int i(0); i < N; ++i, ++ptr) {
		double dis = distance(x, y, ptr->x, ptr->y) - ptr->r;
		if (dis < 0) return 0;
		if (dis < d) d = dis;
	}
	ptr = enemy;
	for (int i(0); i < M; ++ptr, ++i) {
		if (distance(x, y, ptr->x, ptr->y) <= d) ++cnt;
	}
	return cnt;
}

int res(0);
inline void SA(double sx, double sy, double * ex, double * ey) {
	// srand(time(NULL));
	double x = sx, y = sy;
	double temp = 3007;
	constexpr double delta = 0.999, esp = 1e-10;
	while (temp > esp) {
		temp *= delta;
		sx = x + ((rand() << 1) - RAND_MAX) * temp;
		sy = y + ((rand() << 1) - RAND_MAX) * temp;
		int cur = calc(sx, sy), d = res - cur;
		// printf("Cur = %d\n", cur);
		if (d < 0) { // better
			x = sx, y = sy, res = cur;
		} else if (exp(-d / temp) * RAND_MAX < rand()) {
			*ex = sx, *ey = sy;
		}
	}
	// printf("SA end: get res = %d\n", res);
	*ex = x, *ey = y;
}

double sx(0.0), sy(0.0);
void solve() {
	int time = 8;
	while (time--) SA(sx, sy, &sx, &sy);
	// time_t start = clock();
	// time_t useT = (clock() - start);
	// while (clock() + useT <= CLOCKS_PER_SEC * 2.95) SA(sx, sy, &sx, &sy);
}

int main() {
	srand(20070727);
	
	read(N, M, _R);
	R = _R;
	
	P * ptr = build;
	for (int i = 0; i < N; ++i, ++ptr) {
		read(ptr->x, ptr->y, ptr->r);
	}
	
	ptr = enemy;
	for (int i = 0; i < M; ++i, ++ptr) {
		read(ptr->x, ptr->y);
	}
	ptr = enemy;
	for (int i = 0, t; i < M; ++i, ++ptr) {
		t = calc(ptr->x, ptr->y);
		if (t > res) res = t, sx = ptr->x, sy = ptr->y;
	}
	
	solve();

	printf("%d\n", res);	
	return 0;
}