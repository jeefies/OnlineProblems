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

class item {
public:
	int cost, value;
	item(int c, int v) {
		this->cost = c;
		this->value = v;
	}
};
typedef vector<item *> group;

int m, n;
vector<group *> grps;
int igrp[60];

int main(int argc, char * argv[]) {
	cin >> m >> n; m /= 10;
	int tmpA, tmpB, tmpC;
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &tmpA, &tmpB, &tmpC);
		tmpA /= 10;
		
		if (tmpC == 0) {
			// is main item
			igrp[i] = grps.size();
			grps.push_back(new group(1, new item(tmpA, tmpA * tmpB)));
		} else {
			// is not main item
			// list and append
			for (int x = grps[igrp[tmpC - 1]]->size() - 1; x >= 0; x--) {
				item * prev = grps[igrp[tmpC - 1]]->at(x);
				grps[igrp[tmpC - 1]]->push_back(
					new item(tmpA + prev->cost, tmpA * tmpB + prev->value)
				);
			}
		}
	}
	
	static int dp[3201] = {0};
	for (int g = 0; g < grps.size(); g++) {
		for (int v = m; v; v--) {
			group * grp = grps[g];
			
			for (const item * i : *grp) {
				if (i->cost <= v)
					dp[v] = max(dp[v], dp[v - i->cost] + i->value);
			}
		}
	}
	
	cout << dp[m] * 10 << endl;
	return 0;
}