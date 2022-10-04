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

int h, n;

typedef struct {
	int time, life, height, restReach;
} waste;

typedef struct {
	int height, life;
} timepoint;

waste * wastes[100];

void prt(int depth) {
	while (depth--) putchar('\t');
}

int maxlife = 10;
bool survived = false;
int minsurvive = INT_MAX;

void search(int time, int life, int height, int wi, int depth) {
	// prt(depth); printf("search %d, %d, %d, %d\n", time, life, height, wi);
	
	// survived
	if (height >= h) {
		minsurvive = min(minsurvive, wastes[wi - 1]->time);
		survived = true;
		return;
	}

	// can reach to next
	if (wi < n) life -= (wastes[wi]->time - time), time = wastes[wi]->time;;
	if (life < 0 || wi == n) {
		maxlife = max(maxlife, time + life);
		return;
	}
	
	// can reach to top, NOT eat all things to live
	if (wastes[wi]->restReach + height >= h) {	
		// do fill
		search(time, life, height + wastes[wi]->height, wi + 1, depth + 1);
	}
	
	// do eat
	search(time, life + wastes[wi]->life, height, wi + 1, depth + 1);
		
	
}

int main(int argc, char * argv[]) {
	cin >> h >> n;
	for (int i = 0; i < n; i++) {
		wastes[i] = new waste;
		cin >> wastes[i]->time >> wastes[i]->life >> wastes[i]->height;
		wastes[i]->restReach = wastes[i]->height;
	}
	
	for (int i = n - 2; i >= 0; i--) {
		wastes[i]->restReach += wastes[i + 1]->restReach;
	}
	
	sort(wastes, wastes + n, [](waste * a, waste * b) {
		return a->time < b->time;
	});
	
	search(0, 10, 0, 0, 0);
	
	if (survived) cout << minsurvive << endl;
	else cout << maxlife << endl;
	return 0;
}