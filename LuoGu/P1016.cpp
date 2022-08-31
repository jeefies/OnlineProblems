#include <stdio.h>

int N;
double D, oilD, maxOil;
double distance[8] = {0.0};
double cost[8] = {0.0}; 

double search() {
	double maxR = maxOil * oilD;

	int cs = 0; // current step
	double cd = 0.0; // current distance
	double co = 0.0; // current oil count
	double money = 0.0; // need money

	while (cd != D) {
		// judge can reach to next or not
		if (cd + maxR < distance[cs + 1]) {
			return -1;
		}

		// dst step
		int s;
		for (s = cs + 1; s <= N + 1; s++) {
			// cost[N + 1] must be 0
			if (cost[s] <= cost[cs]) {
				break;
			}

			if (cd + maxR < distance[s + 1]) {
				break;
			}
		}

		// need reach to s
		cd = distance[s];
		// no need to be full
		if (cost[s] <= cost[cs]) {
			double needOil = (distance[s] - distance[cs]) / oilD - co;
			money += needOil * cost[cs];
			co = 0;
		} else {
			// need to fill to full
			money += (maxOil - co) * cost[cs];
			double needOil = (distance[s] - distance[cs]) / oilD;
			co = maxOil - needOil;
		}
		cs = s;
		cd = distance[s];
	}
	return money;
}

int main() {
	scanf("%lf%lf%lf%lf%d", &D, &maxOil, &oilD, &cost[0], &N);
	
	for (int i = 1; i <= N; i++) {
		scanf("%lf%lf", distance + i, cost + i);
	}
	distance[N + 1] = D;
	
	double money = search();
	
	if (money == -1) printf("No Solution");
	else printf("%.2lf", money);
	return 0;
}
