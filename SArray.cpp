#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>

using namespace std;
const int N = 1e6 + 7;

char s[N];
// SA 保存排序后的下标，rk 保存原串中从 i 位置处开始的串是第几小的串
int SA[N << 1], rk[N << 1], tmp[N << 1];

void getSA(char * s, int n) {
	if (n == 1) return (void)(rk[1] = SA[1] = 1);
	
	for (int i = 1; i <= n; ++i) SA[i] = i, rk[i] = s[i];
	
	for (int w = 1; w <= n; w <<= 1) {
		auto rp = [&](int x) { return std::make_pair(rk[x], rk[x + w]); };
		std::sort(SA + 1, SA + 1 + n, [&](int x, int y) { return rp(x) < rp(y); });
		for (int p = 0, i = 1; i <= n; ++i)
			tmp[SA[i]] = rp(SA[i]) == rp(SA[i - 1]) ? p : ++p;
		std::copy_n(tmp + 1, n, rk + 1);
	}
}

// ht[i] 表示排序后的第i小串与第i-1小的最长前缀
// 字符串本质不同的子串数量为 n(n-1)/2 - \sum ht[i]
int ht[N];
void getHt(int n) {
    for (int k(0), i = 1; i <= n; ++i) {
        if (k > 0) --k;
        while (s[i + k] == s[SA[rk[i] - 1] + k]) ++k;
        ht[rk[i]] = k;
   }
}

int main() {
    std::cin >> (s + 1);
	int n = strlen(s + 1);
    getSA(s, n);
    for (int i = 1; i <= n; ++i)
        std::cout << SA[i] << ' ';
    std::cout << '\n';
    for (int i = 1; i <= n; ++i)
        std::cout << rk[i] << ' ';
    std::cout << '\n';
    getHt(n);
    for (int i = 1; i <= n; ++i)
        std::cout << ht[i] << ' ';
    std::cout << '\n';
    return 0;
}