#include <iostream>

using namespace std;

struct game {
	int et, fine;
};

game gs[502];
bool planned[502] = {false};

int main() {
	int m;
	cin >> m;
	int n;
	cin >> n;
	
	for (int i = 0; i < n; i++)
		cin >> gs[i].et;
	for (int i = 0; i < n; i++)
		cin >> gs[i].fine;
		
	for (int i = 0; i < n; i++)
		for (int j = 1; j < n - i; j++)
			if (gs[j - 1].fine < gs[j].fine) swap(gs[j - 1], gs[j]);
			
	int fine = 0;
	for (int i = 0; i < n; i++) {
		int j;
		for (j = gs[i].et - 1; j >= 0; j--) {
			if (!planned[j]) {
				planned[j] = true;
				break;
			}
		}
		if (j == -1) fine += gs[i].fine;
	}
	
	cout << m - fine << endl;
}
