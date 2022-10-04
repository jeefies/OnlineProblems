extern "C" {
	#include <cstdio>
	#include <cstring>
	#include <cstdlib>
	#include <climits>
}

#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

int n, w, g;
vector<int> groups[1001];
// f[g][v]
int f[1001] = {0};
int weight[1001], values[1001];

int main(int argc, char * argv[]) {
	cin >> w >> n;
	for (int i = 0; i < n; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		groups[c].push_back(i);
		weight[i] = a, values[i] = b;
		
		g = max(g, c);
	}
	
	// printf("Get %d groups\n", g);
	
	for (int gi = 1; gi <= g; gi++) {
		for (int wi = w; wi > 0; wi--) {
			for (int i = groups[gi].size() - 1; i >= 0; i--) {
				int k = groups[gi][i];
				// printf("Search group %d item %d, global at %d\n", gi, i, k);
				/*
				if (wi >= weight[k])
					f[gi][wi] = max(f[gi - 1][wi], 
						f[gi - 1][wi - weight[k]] + values[k]);
				else f[gi][wi] = f[gi - 1][wi];
				*/
				if (wi >= weight[k])
					f[wi] = max(f[wi], f[wi - weight[k]] + values[k]);
			}
		}
	}
	
	cout << f[w] << endl;
	return 0;
}