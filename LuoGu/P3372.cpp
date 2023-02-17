#include <iostream>
#include <deque>

const int N = 4e5 + 2;

struct Node {
	int l, r; // [l, r]
	int lazy, sum, val;
	Node *lt, *rt;
};

class NodeFactory {
private:
	Node * nodes;
	int used;
public:
	NodeFactory() : used(0) {
		nodes = (Node *)malloc(N * sizeof(Node));
	}

	Node * newNode() {
		return nodes[used++];
	}
}

// lazy create nodes
class SegTree {
private:
	Node * root;
	NodeFactory nf;
public:
	SegTree(int l, int r) {
		root = nf.newNode();
		root->l = l, root->r = r;
	}

	// A node is available just when lt and rt are not nullptr.
	// node: [l, r];
	// 	lt: [l, (l + r) / 2];
	// 	rt: [(l + r) / 2 + 1, r];
	int query(int l, int r) {
		return query(root, l, r);
	}

	int query(Node * root, int l, int r) {
		if (l <= root->l && root->r <= r) {
			return root->val;
		}
		int mid = (root->l + root->r) >> 1;
		int ans = 0;
		
		if (r > mid) {
			ans += query(root->rt, l, r);
		}
		
		if (l <= mid) {
			ans += query(root->lt, l, r);
		}

		return ans;
	}
}
