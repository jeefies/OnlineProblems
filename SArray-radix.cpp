#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 4e6 + 3;

char s[N];
int sa[N], tmp[2][N];
int cnt[N]; // radix_sort的计数桶

int * getSA(int n) {
    int m = 128; // 值域
    int *x = tmp[0], *y = tmp[1];

    // 第一次排序
    for (int i = 1; i <= n; ++i)
        ++cnt[x[i] = s[i]];
    // 计数前缀和
    for (int i = 1; i <= m; ++i)
        cnt[i] += cnt[i - 1];
    for (int i = n; i; --i)
        sa[cnt[x[i]]--] = i;
    
    // 开始之后的排序，对于 (rank[x], rank[x + k]) 进行排序。
    for (int p, k = 1; k <= n; k <<= 1) {
        p = 0;
        // 由于对于 [n - k + 1, n]，其 rank[x + k] 一定为0，故会被放在最前面
        for (int i = n - k + 1; i <= n; ++i) y[++p] = i;
        // 很明显，rk已经是有序的，前k名一定是已经被放入的(rank[x+k] = 0)
        // 所以，我们只需要将后面的 n-k 个按顺序加入即可
        // （对于此次的第二关键词排序即使对上一次的第一关键词排序，已经是有序的，所以直接加进去）
        for (int i = 1; i <= n; ++i) {
            if (sa[i] > k) y[++p] = sa[i] - k;
        }

        // 现在开始对于第一关键字排序
        // 清空计数桶，实际上可能不需要？
        for (int i = 0; i <= m; ++i) cnt[i] = 0;
        // x[i] 实际上就是上一次的rank，也就是第一关键字
        // 实际上这里可以写作 ++cnt[x[y[i]]]; 效果是一样的
        for (int i = 1; i <= n; ++i) ++cnt[x[i]];
        for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        // i外套了一层y[i], 实际上就是按照第二关键词排好的顺序放回原数组中。
        for (int i = n; i; --i)
            sa[cnt[x[y[i]]]--] = y[i], y[i] = 0;
        
        // 为了避免memset，类似于滚动数组的思想
        swap(x, y);
        // 此时y也就是之前的rank，那么我们现在要取得此时的rank

        p = 0;
        for (int i = 1; i <= n; ++i) {
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? p : ++p;
        }

        if (p >= n) break; //  完成排序，每一个都不一样了。
        m = p; // 改变值域，最终为n
    }

    return x; // 最终的rank
}

int main() {
    std::cin >> (s + 1);
    int n = strlen(s + 1);
    int * rk = getSA(n);
    for (int i = 1; i <= n; ++i) {
        std::cout << sa[i] << ' ';
    } std::cout << '\n';

    for (int i = 1; i <= n; ++i) {
        std::cout << rk[i] << ' ';
    } std::cout << '\n';
    return 0;
}