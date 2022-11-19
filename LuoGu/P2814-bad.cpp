#include <iostream>
#include <unordered_map>

using namespace std;

/*
 * 这是一个很无脑的算法，结合的hash和并查集，占用的空间太多
 * 而且，有一个点不知道为什么过不了？
 */

// N is prime !
const int N = 5e4 + 21, SMOD = 137; 

unordered_map<string, int> ht;
string has[N + 1];
bool iht[N + 1];
int strHash(string str) {
	if (auto search = ht.find(str); search != ht.end())
		return search->second;
	int ha = 0;
	for (int i = 0; i < 6; i++) ha = ((ha << 4) + str[i]) % N;
	while (iht[ha]) ha = (ha + SMOD) % N;
	
	has[ha] = str;
	return ht[str] = ha;
}

class MergeFindSet {
	private:
		int grp[N];
	public:
		void init(int n) {
			for (int i = 0; i < n; i++) {
				grp[i] = i;
			}
		}

		int find(int ox) {
			static int x; x = ox;
			while (grp[x] != x) x = grp[x];
			return grp[ox] = x;
		}

		void merge(int fa, int ch) {
			grp[find(ch)] = find(fa);
		}
};

inline char getToken() {
	char tmp;
	while ((tmp = getchar()) != '#' && tmp != '+' && tmp != '?' && tmp != '$');
	return tmp;
}

static MergeFindSet mfs;
int main(int argc, char *argv[]) {
	char s[8] = {'0'}, p[8] = {0};
	mfs.init(N);

	char opt;
	string parent, name;
	int paha, naha;
	while ((opt = getToken()) != '$') {
		if (opt == '#') {
			cin >> parent; paha = strHash(parent);
			// printf("Get parent hash %d\n", paha);
		} else if (opt == '+') {
			cin >> name; naha = strHash(name);
			// printf("Get child hash %d\n", naha);

			mfs.merge(paha, naha);
		} else {
			// find parent
			cin >> name; naha = strHash(name);
			// printf("Wanted hash %d, named %s\n", naha, name.c_str());
			int pa = mfs.find(naha);
			cout << name << ' ' << has[pa] << endl;
		}
	}

	return 0;
}
