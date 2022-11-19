#include <stdio.h>
#include <string>
#include <stack>
#include <iostream>

class Solution {
public:
    bool isValid(std::string & s) {
        std::stack<char> stk;

        for (const char c : s) {
            if (c == '[' || c == '(' || c == '{' || c == '<') stk.push(c);
            else if (!stk.empty() && (
						(c == ')' && stk.top() == '(') || 
						(c == ']' && stk.top() == '[') || 
						(c == '}' && stk.top() == '{') ||
						(c == '>' && stk.top() == '<')
						)
					)
                stk.pop();
            else {
                return false;
            }
        }
        return stk.empty() ? true : false;
    }
};


int main() {
	int n; std::cin >> n;
	
	std::string str;
	Solution solve;
	for (int i = 0; i < n; i++) {
		std::cin >> str;
		printf(solve.isValid(str) ? "YES\n" : "NO\n");
	}
	
	return 0;
}
