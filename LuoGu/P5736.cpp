#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

// 						0		1		2	3		4
bool notPrime[100005] = {true, true, false, false, true};
int primes[10005] = {2, 3};
int nums[101];


int main() {
	int n;
	scanf("%d", &n);
	
	int maxn = 0, tmp;
	for (int i = 0; i < n; i++) {
		scanf("%d", &tmp);
		nums[i] = tmp;
		if (tmp > maxn) maxn = tmp;
	}
	
	int count = 2;
	for (int i = 4; i <= maxn; i++) {
		if (!notPrime[i]) primes[count++] = i;
		for (int pi = 0; pi < count && i * primes[pi] <= maxn; pi++) {
			notPrime[i * primes[pi]] = true;
			if (i % primes[pi]) break;
		}
	}
	
	sort(nums, nums + n);
	for (int i = 0; i < n; i++) {
		if (!notPrime[nums[i]])
			cout << nums[i] << ' ';
	}
	cout << endl;
	
}
