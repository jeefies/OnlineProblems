#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

struct XY {
	int x, y;
};

const int N = 150 + 2;
const double INF = 1e20;
int n;
double mp[151][151];
XY xy[N];

double dis(XY & a, XY & b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); 
}

static int field[N] = {0};
void mark_field(int i, int id) {
	field[i] = id;
	for (int j = 0; j < n; j++) {
		if (!field[j] && mp[i][j] < INF) mark_field(j, id);
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d %d", &xy[i].x, &xy[i].y);
	char tmp;
	// get every distance
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cin >> tmp;
			if (tmp == '1' || i == j) mp[i][j] = dis(xy[i], xy[j]);
			else mp[i][j] = INF;
		}
	}
	
	// marking the same field
	static int id = 0;
	for (int i = 0; i < n; i++) if (!field[i])
		mark_field(i, ++id); 
	
	// for (int i = 0; i < n; i++) printf("%d ", field[i]); putchar('\n');
	
	// floyd
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				mp[i][j] = min(mp[i][j], mp[i][k] + mp[k][j]);
			}
	}
	
	/*
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			printf("%10.5lf ", mp[i][j]);
		putchar('\n');
	}
	*/
	
	// get max d
	double maxPD[N], maxD[N] = {0.0};
	for (int i = 0; i < n; i++) {
		maxPD[i] = 0;
		for (int j = 0; j < n; j++) {
			if (mp[i][j] != INF)
				maxPD[i] = max(maxPD[i], mp[i][j]);
		}
		// printf("%lf ", maxPD[i]);
		// get field's max D
		maxD[field[i]] = max(maxD[field[i]], maxPD[i]);
	} // putchar('\n');
	
	// for (int i = 1; i <= id; i++) printf("%g ", maxD[i]); putchar('\n');
	
	double min_d = INF, max_d;
	for (int i = 0; i < n; i++) {
		// avoid repeated searching
		for (int j = i + 1; j < n; j++) {
			if (field[i] != field[j]) {
				max_d = max(maxD[field[i]], maxD[field[j]]);
				max_d = max(max_d, maxPD[i] + maxPD[j] + dis(xy[i], xy[j]));
				// printf("mD choose in (%lf, %lf, %lf) to %lf\n", maxD[field[i]], maxD[field[j]], maxPD[i] + maxPD[j] + dis(xy[i], xy[j]), mD);
				min_d = min(min_d, max_d);
			}
		}
	}
	
	printf("%.6lf", min_d);
	return 0;
}
