#include <iostream>

int N;
double D, GD, C;
double distance[8] = {0.0};
double cost[8] = {0.0}; 

double search() {
	double maxR = C * GD;
	int cs = 0; // current step
	double cd = 0.0; // current distance
	double cg = 0.0; // current gas count
	double money = 0.0; // need money
	while (cd != D) {
		double canReach = cd + maxR;
		int dsti = -1;
		int i;
		for (i = cs + 1; i <= N && distance[i] <= canReach; i++) {
			if (cost[i] <= cost[cs]) {
				dsti = i;
				break;
			}
		}
		
		if (distance[cs + 1] > canReach) {
			return -1;
		}
		
		if (dsti == -1) {
			// no cheaper stations after
			if (cd + maxR >= D) {
				// can reach to destination directly
				money += ((D - cd) / GD - cg) * cost[cs];
				break;
			}
			// can not reach to end
			dsti = i - 1;
			// so fill box
			money += cost[cs] * (C - cg);
			cg = C - (distance[dsti] - cd) / GD;
		} else {
			// use all gas to to station
			money += cost[cs] * ((distance[dsti] - cd) / GD - cg);
			cg = 0;
		}
		cd = distance[dsti];
	}
	return money;
}

int main() {
	scanf("%lf%lf%lf%lf%d", &D, &C, &GD, cost, &N);
	
	for (int i = 1; i < N; i++) {
		scanf("%lf%lf", distance + 1, cost + 1);
	}
	distance[N + 1] = D;
	
	double money = search();
	
	if (money == -1) std::cout << "No Solution";
	else printf("%.2lf", money);
	return 0;
}
