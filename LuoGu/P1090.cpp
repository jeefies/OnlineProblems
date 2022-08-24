#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int heaps[10002] = {0};

int main() {	
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> heaps[i];
	
	if (n == 1) {
		cout << heaps[0] << endl;
		return 0;
	}

	sort(heaps, heaps + n);

	queue<int> adder;
	long int result = 0;
	int tmp;
	int hi = 0;
	for (int i = 1; i < n; i++) {
		if (hi >= n) {
			tmp = adder.front(); adder.pop();
		} else if (!adder.empty() && adder.front() < heaps[hi]) {
			tmp = adder.front(); adder.pop();
		} else {
			tmp = heaps[hi++];
		}

		if (hi >= n) {
			tmp += adder.front(); adder.pop();
		} else if (!adder.empty() && (adder.front() < heaps[hi])) {
			tmp += adder.front(); adder.pop();
		} else {
			tmp += heaps[hi++];
		}
// 		如果两个最小的都在队列里面，则会出现问题 
//		if (hi == n) {
//			printf("a = %d ", adder.front());
//			tmp = adder.front(); adder.pop();
//			tmp += adder.front(); adder.pop();
//			adder.push(tmp);
//		} else if (!adder.empty() && (hi == n - 1 || adder.front() <= heaps[hi + 1])) {
//			printf("a = %d ", heaps[hi], adder.front());
//			adder.push((tmp = heaps[hi++] + adder.front()));
//			adder.pop();
//		} else {
//			printf("a = %d ", heaps[hi], heaps[hi+1]);
//			adder.push((tmp = heaps[hi++] + heaps[hi++]));
//		}
		adder.push(tmp);
		result += tmp;
	}
	
	cout << result << endl;
	return 0;
}
