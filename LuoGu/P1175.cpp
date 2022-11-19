#include <stack>
#include <vector>
#include <cstdio>
#include <deque>
#include <iostream>

using namespace std;

struct item {
	bool isOp;
	int val;
};

int level(char v) {
	switch (v) {
		case '+': return 1;
		case '-': return 1;
		case '*': return 3;
		case '/': return 3;
		case '^': return 5;
		case '(': return 0;
		case ')': return 7; 
	}
}

int smaller(item n, item o) {
	if (n.val == '^' && o.val == '^') return false;
	if (level(n.val) <= level(o.val)) return true;
	return false;
}

// useless
void prtStk(stack<item> * stk) {
	if (!stk->empty()) {
		item it = stk->top(); stk->pop();
		prtStk(stk);
		printf(it.isOp ? "%c " : "%d ", it.val);
		stk->push(it);
	}
}

void prt(const item i) {
	printf(i.isOp ? "%c " : "%d ", i.val);
}

int main() {
	stack<item> exp;
	stack<item> ops;
	
	char c;
	item it;
	while ((c = getchar()) != EOF && c != '\n') {
		if ('0' <= c && c <= '9') {
			exp.push({false, c - '0'});
		} else {
			it.isOp = true; it.val = c;
			
			// 括号特判 
			if (c != '(' && c != ')') {
				while (!ops.empty() && smaller(it, ops.top())) {
					exp.push(ops.top());
					ops.pop();
					
				}
			} else if (c == ')') { // 右括号需要一直出栈到左括号匹配 
				while (!ops.empty() && ops.top().val != '(') {
					exp.push(ops.top()); ops.pop();
					
				}
				
				ops.pop(); // pop ( up;
			}
			// 左括号直接加入 
			
			if (c != ')') ops.push(it);
		}
		/*
		printf("Parsing %c\n", c);
		printf("\texp update to: "); prtStk(exp); putchar('\n');
		printf("\tops update to: "); prtStk(ops); putchar('\n');
		*/
	}
	
	while (!ops.empty()) {
		exp.push(ops.top()); ops.pop();
	}
	
	stack<item> calc;
	while (!exp.empty()) {
		calc.push(exp.top()); exp.pop(); 
	}
	
	bool undone = true;
	while (undone) {
		undone = false;
		while (!calc.empty()) {
			exp.push(calc.top());
			prt(calc.top());
			calc.pop();
		}
		putchar('\n');
		while (!exp.empty()) {
			calc.push(exp.top()); exp.pop();
		}
		
		while (!calc.empty() && calc.top().isOp == false) {
			// printf("\tTop is not op\n");
			ops.push(calc.top()); calc.pop();
			undone = true;
		}
		
		if (!undone) break;
		
		char c = calc.top().val; calc.pop();
		int b = ops.top().val; ops.pop();
		int a = ops.top().val; ops.pop();
		
		// printf("op %c, expr %d %c %d\n", c, a, c, b);
		
		int r = 0;
		switch (c) {
			case '+': r = a + b; break;
			case '-': r = a - b; break;
			case '*': r = a * b; break;
			case '/': r = a / b; break;
			case '^': r = 1; while (b --> 0) r *= a; break;
		}
		
		it.isOp = false; it.val = r;
		if (calc.empty() && ops.empty()) {
			printf("%d\n", r);
			break;
		}
		calc.push(it);
		
		while (!ops.empty()) {
			calc.push(ops.top()); ops.pop();
		}
	}
	
	return 0;
}
