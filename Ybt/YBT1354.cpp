#include <stdio.h>
#include <string>
#include <stack>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool isValid(std::string s) {
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
	std::string str;
	std::cin >> str;
	
	Solution solve;
	printf(solve.isValid(str) ? "OK" : "Wrong");
	
	return 0;
}
