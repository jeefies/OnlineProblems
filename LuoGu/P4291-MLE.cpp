#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

typedef unsigned int partHashInt;
typedef unsigned long long int hashInt;
unordered_map<hashInt, string> nameMap;
unordered_map<hashInt, int> scoreMap;

// Error MLE!!
template<int N = 250000 + 2, int BS = 30>
class BSTrie {
private:
	int siz[N << 5];
	vector<hashInt> idn[N << 5];
	int ch[N << 5][2];
	int usage;
public:
	BSTrie() : usage(1) {}
	#define bit(x, i) ((x >> i) & 1)
	#define newNode() ({ \
		++usage; \
		siz[usage] = ch[usage][0] = ch[usage][1] = 0; \
		idn[usage].clear(); \
		usage; \
	})
	void insert(int v, hashInt id) {
//		cout << "In inserting:\n";
		int p = 1;
		for (int bt, i = BS; ~i; --i) {
			bt = bit(v, i);
			if (!ch[p][bt]) ch[p][bt] = newNode();
			++siz[p], p = ch[p][bt]; 
		} ++siz[p], idn[p].push_back(id);
//		cout << "Done\n";
	}
	
	void remove(int v, hashInt id) {
		int p = 1;
		for (int i = BS; ~i; --i) {
			--siz[p], p = ch[p][bit(v, i)]; 
		} --siz[p];
		auto it = find(idn[p].begin(), idn[p].end(), id);
		idn[p].erase(it);
	}
	
	int rank(int v, hashInt id) {
//		cout << "Ranking " << v << " (id: " << id << ")\n";
		int p = 1, rk = 0;
		for (int bt, i = BS; ~i; --i) {
			bt = bit(v, i);
			if (bt) rk += siz[ch[p][0]];
			p = ch[p][bt];
		}
		rk += (idn[p].end() - find(idn[p].begin(), idn[p].end(), id));
		return siz[1] - rk + 1;
	}
	
	hashInt kth(int k) {
		int p = 1;
		for (int i = BS; ~i; --i) {
			if  (k <= siz[ch[p][0]]) p = ch[p][0];
			else k -= siz[ch[p][0]], p = ch[p][1];
		}
		return idn[p][siz[p] - k];
	}
	
	void query(int k, vector<hashInt> &hashes) {
		hashes.clear();
		for (int rk = siz[1] - k + 1, rke = max(rk - 9, 1); rk >= rke; --rk)
			hashes.push_back(kth(rk));
	}
};
BSTrie<> bst;

hashInt mhash(const string &s) {
	const partHashInt BX = 97, BY = 131;
	partHashInt x = 0, y = 0;
	for (auto c : s) {
		x = x * BX + c;
		y = y * BY + c;
	}
	
	hashInt hash = ((hashInt)x << 32) | y;
	if (nameMap.find(hash) == nameMap.end())
		nameMap[hash] = s;
	return hash;
}

int main() {
	cin.tie(0)->sync_with_stdio(false);
	
	int n; cin >> n;
	char op;
	string name;
	int score;
	
	vector<hashInt> hashes;
	for (int i = 0; i ^ n; ++i) {
		cin >> op >> name;
//		cout << "Op: " << op << ", name: " << name << '\n';
		
		
		if (op == '+') {
			cin >> score;
			hashInt name_hash = mhash(name);
//			cout << "\tname hash: " << name_hash << '\n';
			
			auto it = scoreMap.find(name_hash);
			if (it != scoreMap.end())
				bst.remove(it->second, name_hash);
				
			scoreMap.insert(it, {name_hash, score});
			bst.insert(score, name_hash);
		} else if (op == '?' && !isdigit(name[0])) {
			hashInt name_hash = mhash(name);
//			cout << "\tname hash: " << name_hash << '\n';
			cout << bst.rank(scoreMap[name_hash], name_hash) << '\n';
		} else {
			score = std::stoi(name);
			bst.query(score, hashes);
			for (auto h : hashes) {
				cout << nameMap[h] << ' ';
			} cout << '\n';
		}
	}
	return 0;
}
