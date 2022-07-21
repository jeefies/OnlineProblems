/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

int main() {
	int n, na, nb;
	scanf("%d%d%d", &n, &na, &nb);
	int *a = (int *)malloc(sizeof(int) * na);
	int *b = (int *)malloc(sizeof(int) * nb);
	for (int i = 0; i < na; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 0; i < nb; i++) {
		scanf("%d", &b[i]);
	}

	int wa = 0;
	for (int i = 0; i < n; i++) {
		int ca = a[i % na];
		int cb = b[i % nb];
		// printf("cwa %d ca:%d cb:%d\n", wa, ca, cb);
		if (ca == 0) { // Shitou
			if (cb == 2) { // Jiandao
				// B lose
				wa++;
			} else if (cb == 5) { // Bu
				wa--;
			}
		} else if (ca == 2) {// Jiandao
			if (cb == 0) // Shitou
				// B win
				wa--;
			else if (cb == 5)
				wa++;
		} else { // Bu
			if (cb == 0) // Shitou
				// A win
				wa++;
			else if (cb == 2)
				wa--;
		}
	}

	// printf("%d\n", wa);
	if (wa > 0)
		printf("A");
	else if (wa < 0)
		printf("B");
	else printf("draw");
}
