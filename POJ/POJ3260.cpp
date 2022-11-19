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

int n, nt, t = 20000;

int john[20001] = {0}, clerk[20001] = {0};
int coins[100], nums[100];

int main(int argc, char * argv[]) {
	cin >> n >> nt;
	for (int i = 0; i < n; i++) {
		scanf("%d", coins + i);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", nums + i);
	}
	/*
	for (int i = 0; i < n; i++) {
		printf("%d: %d\n", coins[i], nums[i]);
	}
	*/	
	memset(john, 0x3F, sizeof(john));
	memset(clerk, 0x3F, sizeof(clerk));
	john[0] = clerk[0] = 0;
	
	for (int i = 0; i < n; i++) {
		for (int v = coins[i]; v <= t; v++) {
			clerk[v] = min(clerk[v], clerk[v - coins[i]] + 1);
		}
		
		for (int c = 0; nums[i] - (1 << c) >= 0; c++) {
			int k = nums[i] - (2 << c) >= 0 ? (1 << c) : (nums[i] - (1 << c) + 1);
			
			for (int v = t; v >= coins[i] * k; v--) {
				john[v] = min(john[v], john[v - coins[i] * k] + k);
			}
		}
	}
	/*
	for (int i = 0; i < 100; i++) {
		if (i % 10 == 0) putchar('\n');
		printf("%12x", john[i]);
	}
	cout << endl << endl;
	for (int i = 0; i < 100; i++) {
		if (i % 10 == 0) putchar('\n');
		printf("%12x", clerk[i]);
	}
	*/
	int minc = INT_MAX;
	for (int i = nt; i <= t; i++) {
		if (john[i] != 0x3F3F3F3F && clerk[i] != 0x3F3F3F3F) {
			minc = min(minc, john[i] + clerk[i - nt]);
			// printf("at %d %d updated to: %d\n", i, i - n, minc);
		}
	}
	
	cout << minc << endl;
	
	return 0;
}