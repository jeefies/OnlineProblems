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

int c = 0, n;
int costs[5000];

int seqn = 0;
int seqs[5000]= {0};

#warning "Fucking number of schemes"

int main(int argc, char * argv[]) {
	cin >> n;
	for (int i = 0; i < n; i++)
		scanf("%d", costs + i);
		
	int replaceTime = 0, last;
	for (int i = 0; i < n; i++) {
		bool newItem = true;
		for (int k = 0; k < seqn; k++) {
			if (seqs[k] <= costs[i]) {
				printf("Replace (%d time) index %d: %d to %d\n", ++replaceTime, k, seqs[k], costs[i]);
				
				seqs[k] = costs[i], newItem = false;
				break;
			}
		}
		if (newItem) {
			seqs[seqn++] = costs[i];
			printf("New Item with length %d\n", seqn);
		}
	}
	
	cout << seqn << endl;
	return 0;
}