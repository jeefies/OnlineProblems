/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		https://www.luogu.com.cn/problem/P1026
 */

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;

// #warning 这不是一个正确的解法，思路从一开始就是错误的

class wordspan {
	public:
		int s, e;

		wordspan(int s, int e) {
			this->s = s, this-> e = e;
		}

		bool operator== (const wordspan & ws) {
			return s == ws.s && e == ws.e;
		}
};

class list {
	public:
		wordspan* ws[6];

		list() {
			memset(ws, 0, sizeof(ws));
		}

		~list() {
			for (int i = 0; i < 6; i++)
				if (ws[i]) delete ws[i];
		}

		void append(int s, int e) {
			for (int i = 0; i < 6; i++) {
				if (ws[i] == NULL) {
					ws[i] = new wordspan(s, e);
					break;
				}
			}
		}

		void del(wordspan & w) {
			for (int i = 0; i < 6; i++) {
				if (ws[i] != NULL && *ws[i] == w) {
					delete ws[i];
					ws[i] = NULL;
				}
			}
		}

		wordspan pop() {
			wordspan r = {-1, -1};
			for (int i = 5; i >= 0; i--) {
				if (ws[i] != NULL) {
					r.e = ws[i]->e, r.s = ws[i]->s;
					delete ws[i];
					ws[i] = NULL;
					return r;
				}
			}
			return r;
		}

		int length() {
			int c = 0;
			for (int i = 0; i < 6; i++)
				if (ws[i] != NULL) c++;
			return c;
		}
};

bool equal(string & s, string & w, int os) {
	if (os + w.size() > s.size()) return false;
	for (int i = w.size() - 1; i >= 0; i--) {
		if (w[i] != s[os + i]) return false;
	}
	return true;
}

int wordCount(string & str, string * words, int s, int k) {
	list * sep = new list[str.length()];
	bool * takeup = new bool[str.length()];

	int tot = 0;
	for (int i = 0; i < str.length(); i++) {
		for (int j = 0; j < s; j++) {
			if (!takeup[i] && equal(str, words[j], i)) {
				for (int dx = 0; dx < words[j].size() - 1; dx++) {
					sep[i + dx].append(i, i + words[j].size());
				}
				tot++;
				// printf("At %d insert word %s\n", i, words[j].c_str());
				takeup[i] = true;
			}
		}
	}

	// printf("Total %d\n", tot);
	for (int i = 0; i < str.length() - 1; i++) {
		// printf("At sep %d has length %d\n", i, sep[i].length());
	}

	bool * remove = new bool[str.length()];

	for (int i = 1; i < k; i++) {
		int minl = INT_MAX;
		int mini;

		for (int j = 0; j < str.length() - 1; j++) {
			if (!remove[j] && sep[j].length() < minl) {
				mini = j;
				minl = sep[j].length();
			}
		}
			
		remove[mini] = true;

		list & li = sep[mini];
		if (li.length() == 0) continue;

		// printf("Mini At %d, delete %d\n", mini, li.length());
		tot -= li.length();
		for (int j = li.length(); j > 0; j--) {
			wordspan ws = li.pop();
			for (int d = ws.s; d < ws.e; d++) {
				sep[d].del(ws);
			}
		}
	}

	delete []sep;
	delete []takeup;
	delete []remove;

	return tot;
}

int main() {
	int p, k;
	cin >> p >> k;

	string str = "";
	for (int i = 0; i < p; i++) {
		string tmp;
		cin >> tmp;
		str += tmp;
	}

	int s;
	cin >> s;
	string * words = new string[s];
	for (int i = 0; i < s; i++) {
		cin >> words[i];
	}

	sort(words, words + s, [](string & a, string & b) { return a.length() < b.length(); });

	int r = 0;
	cout << wordCount(str, words, s, k) << endl;

	// delete []lines;
}
