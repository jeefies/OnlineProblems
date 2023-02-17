#include <iostream>
#include <algorithm>
#include <cstring>
#include <array>

using std::array;
using std::pair;

#define N 500007
#define K 5
#define KS 3

typedef unsigned char uint8;
typedef int data;

#define Array(type) array<type, K + 1>

struct Node {
	/*----------flag----------*/
	uint8 leaf, n;
	/*----keys and indexes----*/
	// Each node at most has K vals and K kids
	Array(data) vals;
	Array(Node*) kids;
	/*----------leaf----------*/
	Node *prev, *next;
	/* if root, parent == nullptr*/
	Node *parent;
	
	inline void insert(int val, Node *kid = nullptr) {
		vals[n] = val, kids[n] = kid;
		for (int i(n++); i; --i)
			if (vals[i] < vals[i - 1]) {
				std::swap(vals[i], vals[i - 1]);
				std::swap(kids[i], kids[i - 1]);
			}
			else break;
	}
	
	// no key return -1!
	inline data key() {
		return n ? kids[n - 1] : -1;
	}
	
	inline int findKey(data key) {
		for (int i = 0; i < n; ++i) {
			if (key <= vals[i]) return i;
		}
		return n - 1;
	}
};

class BPTree {
private:
	Node _nodes[N];
	Node *root, *usage;
public:
	BPTree() : usage(_nodes), root(_nodes) {
		root->leaf = true; // empty tree!
	};
	
	void insert(int val, Node * cur) {
		// insert the val, and maintain it later!
		if (cur->leaf) {
			cur->insert(val);
			return;
		}
		
		/* Find the leaf we should insert val in! */
		int pos(0);
		array<data, K + 1> &keys = cur->vals;
		for (; pos < cur->n; ++pos) {
			if (val < keys[pos]) break;
		}
		if (pos == cur->n) --pos;
		Node * insertNode = cur->kids[pos];
		insert(val, insertNode);
		
		/* now we need to maintain the child node! */
		if (insertNode->n > K) {
			// need to split it!
			Node * splitNode = ++usage;
			for (int i(0); i < KS; ++i) {
				splitNode->vals[i] = insertNode->vals[i + KS];
				splitNode->kids[i] = insertNode->kids[i + KS];
			}
			splitNode->n = insertNode->n = KS;
			if ((splitNode->next = insertNode->next)) splitNode->next->prev = splitNode;
			insertNode->next = splitNode, splitNode->prev = insertNode;
		}
	}
};