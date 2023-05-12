#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <ctime> 
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

template<int MAX_LEVEL, typename KT = int>
struct Node {
	KT key;
	int count, level; // exists time
	Node * nxt[MAX_LEVEL + 1];
	int len[MAX_LEVEL + 1]; 
	Node(KT key = KT()) : key(key), count(1), level(MAX_LEVEL) {
		fill(nxt, nxt + 1 + MAX_LEVEL, nullptr);
		fill(len, len + 1 + MAX_LEVEL, 0);
	}
	
	string toString() {
		stringstream ss;
		ss << "key: " << key << ", appear " << count << " times ";
		return ss.str();
	}
};

template<int MAX_LEVEL = 16>
class SkipList {
private:
	using LNode = Node<MAX_LEVEL>;
	
	// random generator
	mt19937 _gen;
	uniform_int_distribution<> _distri;
	
	// SkipList information
	int curlevel;
	LNode * head;
public:
	SkipList() : _gen(time(NULL)), _distri(0, 2), curlevel(1) {
		// head = new LNode(-0x7FFFFFFF);
		head = new LNode(0);
	}
	
	LNode * find(int key) {
		int tmp;
		return find(key, tmp);
	}
	
	LNode * find(int key, int &rank) {
		rank = 0;
		LNode * cur = head;
		for (int i = curlevel; i; --i) {
			while (cur->nxt[i] != nullptr && cur->nxt[i]->key < key)
				rank += cur->len[i], cur = cur->nxt[i];
		}
		
		if (cur->nxt[1] != nullptr && cur->nxt[1]->key == key)
			return ++rank, cur->nxt[1];
		return nullptr;
	}
	
	void insert(int key) {
		static LNode* updates[MAX_LEVEL + 1];
		static int len[MAX_LEVEL + 2] = {0, 0};
		
		int level = randLevel();
		if (level > curlevel) curlevel = level;
		
		LNode * cur = head;
		for (int i = curlevel; i; --i) {
			len[i + 1] = 0;
			while (cur->nxt[i] != nullptr && cur->nxt[i]->key < key)
				len[i + 1] += cur->len[i], cur = cur->nxt[i];
			updates[i] = cur;
		}
		
		if (cur->nxt[1] != nullptr && cur->nxt[1]->key == key) {
			++cur->nxt[1]->count;
			for (int i = curlevel; i; --i) ++(updates[i]->len[i]);
			return;
		}
		
		LNode * add = new LNode(key);
		add->level = level;
		for (int i = level; i; --i) {
			add->nxt[i] = updates[i]->nxt[i];
			add->len[i] = updates[i]->len[i] ? updates[i]->len[i] - len[i] : 0;
			updates[i]->nxt[i] = add;
			updates[i]->len[i] = len[i] + 1;
		}
	}
	
	inline int randLevel() {
		int level = 1;
		while (level < MAX_LEVEL && _distri(_gen) == 0) ++level;
		return level;
	}
	
	void debug() {
		cout << "In debug:\n";
		LNode * cur = head;
		while (cur != 0) {
			cout << cur->count << '\t';
			for (int i = 1; i <= cur->level; ++i) {
				cout << setw(4) << cur->key << ' ';
			} cout << '\n';
			cout << "LEN:\t";
			for (int i = 1; i <= cur->level; ++i) {
				cout << setw(4) << cur->len[i] << ' ';
			}
			cout << "\n\n";
			cur = cur->nxt[1];
		}
		cout << "DONE\n";
	}
};

int main() {
	SkipList<> sl;
	for (int i = 1; i <= 10; ++i)
		sl.insert(i), sl.debug();
	sl.insert(3); sl.debug();
	
	cout << "Insert done" << endl;
	
	int rank;
	cout << (sl.find(10, rank)->toString()) << '\n';
	cout << "Rank " << rank << ' '; 
	
} 
