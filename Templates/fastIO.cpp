#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>

typedef unsigned int uint;

namespace normalIO {
	template<typename T>
	inline void read(T &x) {
		register char tmp, f(0); x = 0;
		do if ((tmp = getchar()) == '-') f = 1; while (tmp < '0' || '9' < tmp);
		do x = (x<<1) + (x<<3) + (tmp ^ 48), tmp = getchar(); while ('0' <= tmp && tmp <= '9');
		if (f) x = -x;
	}
	template <typename T, typename ...Args>
	inline void read(T &x, Args&... args) {
		read(x), read(args...);
	}
}

namespace fastIO {
	const uint BUF_LEN = 1<<17|1;
	char buf[BUF_LEN], *ps = buf, *pe = buf;
	FILE * fp = stdin;
	
	inline void open(const char * fn) {
		fp = fopen(fn, "rb");
	}
	
	#define gc() (ps == pe && (pe = (ps = buf) + fread(buf, 1, BUF_LEN, fp), pe == ps) ? EOF : *ps++)
	template <typename T>
	inline void read(T &x) {
		register char tmp, f(0); x = 0;
		do if ((tmp = gc()) == '-') f = 1; while (tmp < '0' || '9' < tmp);
		do x = (x<<1) + (x<<3) + (tmp ^ 48), tmp = gc(); while ('0' <= tmp && tmp <= '9');
		if (f) x = -x;
	}
	template <typename T, typename ...Args>
	inline void read(T &x, Args&... args) {
		read(x), read(args...);
	}
};
using fastIO::read;

int main() {
	fastIO::open("templates-testdata.in");
	
	int n;
	read(n);
	
	printf("%d\n", n);
	return 0;
}