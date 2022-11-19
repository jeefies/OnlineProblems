#include <iostream>
#include <unordered_map>

using namespace std;

// N is prime !
const int N = 5e4 + 21, SMOD = 137; 

unordered_map<string, int> ht;
bool iht[N + 1];
int strHash(string str) {
	if (auto search = ht.find(str); search != ht.end())
		return search->second;
	unsigned int ha = 0;
	for (int i = 0; i < 6; i++) ha = ((ha << 5) + str[i]) % N;
	while (iht[ha]) ha = (ha + SMOD) % N;
	
	return ht[str] = ha;
}
