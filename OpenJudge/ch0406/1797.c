#include <stdio.h>

typedef struct type {
	int weight;
	int total;
	double single;
} type;

int tail;
type metals[102];

int main() {
	int n;
	scanf("%d", &n);

	while (n--) {
		tail = 0;

		int cantake;
		scanf("%d", &cantake);

		// get data
		int typecount;
		scanf("%d",&typecount);
		while (tail < typecount) {
			int weight, total;
			scanf("%d%d", &weight, &total);

			type cur = {weight, total, (double)total / (double)weight};

			metals[tail++] = cur;
		}

		// sort data
		type tmp;
		for (int i = 0; i < typecount - 1; i++) {
			for (int j = 0; j < typecount - 1 - i; j++) {
				if (metals[j].single < metals[j + 1].single) {
					tmp = metals[j];
					metals[j] = metals[j + 1];
					metals[j + 1] = tmp;
				}
			}
		}

		// take metal
		double value = 0;
		for (int i = 0; i < typecount; i++) {
			if (cantake >= metals[i].weight) {
				value += metals[i].total;
				cantake -= metals[i].weight;
			} else {
				value += metals[i].single * cantake;
				break;
			}
		}

		printf("%.2lf\n", value);
	}
}
