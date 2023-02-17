#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>

int n, l, s;

typedef unsigned long long hashInt;
const unsigned int N = 30003, L = 203, BASE = 137, BASE2 = 97;

hashInt off2[N] = {1};

class String {
private:
	char str[L];
	hashInt f, b;
public:
	String * read() {
		scanf("%s", str + 1);
		return this;
	}
	
	void prepare() {
		for (int i = 1; i <= l; ++i) {
			fHash[i] = fHash[i - 1] * BASE + str[i] - 37;
			bHash[l + 1 - i] = bHash[l + 2 - i] * BASE2 + str[l + 1 - i] - 37;
		}
	}
	
	hashInt fhash(int i) { return fHash[i]; }
	hashInt bhash(int i) { return bHash[i]; }
	hashInt hash() { return fHash[l]; }
};
static String strs[N];

int main() {
	scanf("%d %d %d", &n, &l, &s);
	
	for (int i(0); i < n; ++i) {
		strs[i].read()->prepare();
	}
	
	// 保证了没有相同的名字
	static std::pair<hashInt, hashInt> hashes[N]; 
	int ans(0);
	for (int bp = 1; bp <= l; ++bp) { // 枚举断点
		for (int i(0); i < n; ++i) {
			hashes[i] = {strs[i].fhash(bp - 1), strs[i].bhash(bp + 1)};
		}
		sort(hashes, hashes + n);
		int same(1);
		for (int i(1); i < n; ++i) {
			if (hashes[i] == hashes[i - 1]) ans += same++;
			else same = 1;
		}
	}
	
	printf("%d\n", ans);
	return 0;
}
