#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

// with one RE!??
class RadixHeap {
private:
	size_t hsize, B, nC; 
	typedef map<int, vector<int>> Bucket;
	vector<Bucket> buckets;
	vector<int> bucketMin, bucketMax;
public:
	RadixHeap(int nC) : hsize(0), B(0), nC(nC) {
		for (long long w = 1; w <= nC; w <<= 1, ++B) {
			bucketMax.push_back((int)(w - 1));
			bucketMin.push_back((int)(w >> 1));
			buckets.emplace_back(Bucket());
		}
	}
	void push(int v, int x) {
		++hsize;
		int i = 0;
		while (v < bucketMin[i] || v > bucketMax[i]) ++i; // until v >= bucketMin[i];
		buckets[i][v].push_back(x);
	}
	
	pair<int, int> pop() {
		tryPull();
		--hsize;
		auto it = buckets[0].begin();
		pair<int, int> p = make_pair(it->first, it->second.back());
		if (it->second.size() > 1) {
			return it->second.pop_back(), p;
		}
		
		// only one element, clear then
		buckets[0].clear();
		return p;
	}
	
	void tryPull() {
		if (buckets[0].size()) return;
		
		size_t i = 1;
		while (i < B && buckets[i].size() == 0) ++i;
		if (i == B) return; // no elements!
		
		Bucket &bk = buckets[i];
		auto it = bk.begin();
		buckets[0][it->first] = it->second;
		int D = bucketMin[i], U = bucketMax[i];
		bucketMin[0] = bucketMax[0] = D;
		for (int k = 1, w = 1; (size_t)k < i; ++k, w <<= 1) {
			bucketMin[k] = D + w, bucketMax[k] = min(U, D + (w << 1) - 1);
		}
		
		bucketMin[i] = nC;
		
		i = 1;
		if (it != bk.end()) for (++it; it != bk.end(); ++it) {
			while (it->first > bucketMax[i]) ++i;
			buckets[i][it->first] = it->second;
		} bk.clear();
	}
	
	size_t size() {
		return hsize;
	}
}; 

const int N = 1e5 + 3;
class Graph {
private:
	int n;
	struct Edge {
		int to, w;
	};
	vector<Edge> G[N];
public:
	inline void read(int n, int m) {
		this->n = n;
		for (int u, v, w, i = 0; i < m; ++i) {
			cin >> u >> v >> w;
			G[u].push_back({v, w});
		}
	}
	
	void djk(int s, vector<int> &dis) {
		RadixHeap rh(1e9);
		vector<bool> vis(n + 1);
		
		dis[s] = 0;
		rh.push(dis[s], s);
		while (rh.size()) {
			pair<int, int> p = rh.pop();
			int x = p.second;
			if (vis[x]) continue;
			vis[x] = true;
			for (auto e : G[x]) {
				if (dis[e.to] > dis[x] + e.w) {
					dis[e.to] = dis[x] + e.w;
					rh.push(dis[e.to], e.to);
				}
			}
		}
	}
} g;

int main() {
	cin.tie(0)->sync_with_stdio(false);
	
	int n, m, s;
	cin >> n >> m >> s;
	
	g.read(n, m);
	vector<int> dis(n + 1, 0x7FFFFFFF);
	g.djk(s, dis);
	for (int i = 1; i <= n; ++i) {
		cout << dis[i] << ' ';
	}
}
