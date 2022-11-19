#include <iostream>
#include <cstring> 
using namespace std;

int n, m;

int main() {
	int O = 0x7FFFFFFF; // all 1
	int Z = 0x00000000; // all 0
	cin >> n >> m;
	char op[5]; int x;
	for (int i = 0; i < n; i++) {
		op[2] = op[3] = '\0';
		scanf("%s %d", op, &x);
		if (strcmp(op, "AND") == 0) O &= x, Z &= x;
		else if (strcmp(op, "OR") == 0) O |= x, Z |= x;
		else O ^= x, Z ^= x;
	}
	
	
	int org = 0, val = 0;
	int wi = 1 << 30, r0, r1;
	for (int i = 29; i >= 0; i--) {
		wi >>= 1, r0 = Z & (1 << i), r1 = O & (1 << i);
		if (org + wi <= m && (r1 > r0)) {
			org += wi, val += r1;
		} else val += r0;
	}
	
	cout << val << endl;
	return 0;
}
