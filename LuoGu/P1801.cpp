extern "C" {
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <limits.h>
}

#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

int nums[200000];
int getp[200000];

priority_queue<int, vector<int>, greater<int> > sheap; // Ð¡¶¥
priority_queue<int> bheap; // ´ó¶¥

int main(int argc, char * argv[]) {
    int m, n;
    scanf("%d%d", &m, &n);
    for (int i = 0; i < m; i++) scanf("%d", nums + i);
    for (int i = 0; i < n; i++) scanf("%d", getp + i);

    int ri = 0, ni = 1;
    size_t kth = 0;
    sheap.push(nums[0]);

    for (ri = 0; ri < n; ri++) {
        ++kth;
        for (;ni < getp[ri]; ni++) {
            if (nums[ni] >= sheap.top()) sheap.push(nums[ni]);
            else bheap.push(nums[ni]);
        }
		
		while (bheap.size() > kth) {
			sheap.push(bheap.top()); bheap.pop();
		}
		while (bheap.size() < kth) {
			bheap.push(sheap.top()); sheap.pop();
		}

        printf("%d\n", bheap.top());

    }
    return 0;
}
