#include <stack> 
#include <iostream>

int main() {
	std::stack<int> stk;
	
	char tmp = '0';
	while (tmp != '@') {
		// Èç¹ûÊÇ·ûºÅ
		if (tmp < '0' || tmp > '9') {
			int y = stk.top(); stk.pop();
			int x = stk.top(); stk.pop();
			
			int r;
			switch (tmp) {
				case '+': r = x + y; break;
				case '-': r = x - y; break;
				case '*': r = x * y; break;
				case '/': r = x / y; break;
			}
			stk.push(r);
		} else {
			int n = tmp - '0';
			while ((tmp = getchar()) >= '0' && tmp <= '9') n = n * 10 + tmp - '0';
			stk.push(n);
		}
		
		tmp = getchar();
	}
	std::cout << stk.top();
}
