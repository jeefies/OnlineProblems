extern "C" {
	#include <cstdio>
	#include <cstring>
	#include <cstdlib>
	#include <climits>
	#include <cstdint>
}

#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

typedef int64_t i64;

i64 maxl = 0, scheme = 0, n;
int costs[5000];
i64 length[5000];
i64 schemes[5000];

int main(int argc, char * argv[]) {
	cin >> n;
	for (int i = 0; i < n; i++) {
		scanf("%d", costs + i);
	}

	for (int i = 0; i < n; i++) {
		length[i] = 1, schemes[i] = 1;
		
		for (int j = 0; j < i; j++) {
			if (costs[j] > costs[i]) {
				if (length[j] + 1 > length[i]) {
					length[i] = length[j] + 1;
					schemes[i] = schemes[j];
				} else if (length[j] + 1 == length[i]) {
					schemes[i] += schemes[j];
				}
			} else if (costs[j] == costs[i] && length[j] == length[i]) {
				schemes[j] = 0;
			}
		}
		
		maxl = max(maxl, length[i]);
	}
	
	for (int i = 0; i < n; i++)
		if (length[i] == maxl) scheme += schemes[i];
		
	printf("%ld %ld\n", maxl, scheme);

	return 0;
}
