#include <iostream>
#include <string>

using namespace std;

const int N = 1e3 + 7;

bool match(string &a, string &b, int k) {
	// printf("Matching at %d\n", k);
	int as = a.size() / 2;
	size_t bm = 1;
	for (int i = k + 1; i < k + as; ++i) {
		if (a[i] == b[bm]) {
			if (++bm == b.size()) return true;
		}
	}
	
	return false;
}

bool proc() {
	string a, b;
	cin >> a >> b;
	int as = a.size(), bs = b.size();
	a = a + a;
	
	if (bs > as) {
		return false;
	}
	
	// printf("Proc!\n");
	for (int k = 0; k < as; ++k) {
		if (a[k] == b[0]) {
			if (match(a, b, k)) return true;
		}
	}
	return false;
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		if (proc()) printf("Y\n");
		else printf("N\n");
	}
	return 0;
}