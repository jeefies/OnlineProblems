#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;
typedef long long lint;

template<int N = 250000 + 2>
class BSTree {
private:
	lint val[N << 1];
	int siz[N << 1];
	int lc[N << 1], rc[N << 1];
	string name[N << 1];
} bst;

map<string, int> scoreMap;
int main() {
	cin.tie(0)->sync_with_stdio(false);
	
	int n; cin >> n;
	char op;
	string name;
	lint score;
	
	vector<string> names;
	for (int i = 0; i ^ n; ++i) {
		cin >> op >> name;
		
		if (op == '+') {
			cin >> score;
			
			// remake score
			score = score * 250000 - i;
			
			auto it = scoreMap.find(name);
			if (it != scoreMap.end())
				bst.remove(it->second);
				
			scoreMap.insert(it, {name, score});
			bst.insert(score, name);
		} else if (op == '?' && !isdigit(name[0])) {
			cout << bst.rank(scoreMap[name]) << '\n';
		} else {
			int idx = std::stoi(name);
			bst.query(idx, names);
			for (auto name : names) {
				cout << name << ' ';
			} cout << '\n';
		}
	}
	return 0;
}
