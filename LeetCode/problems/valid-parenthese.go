/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://leetcode.cn/problems/valid-parentheses/
 */
package main

import (
	"fmt"
)

func isValid(s string) bool {
	stack := make([]byte, 0, len(s))

	for i := 0; i < len(s); i++ {
		switch s[i] {
		case '(':
			fallthrough
		case '[':
			fallthrough
		case '{':
			stack = append(stack, s[i])
		case ')':
			if len(stack) == 0 || stack[len(stack) - 1] != '(' {
				return false
			}
			stack = stack[:len(stack) - 1]
		case ']':
			if len(stack) == 0 || stack[len(stack) - 1] != '[' {
				return false
			}
			stack = stack[:len(stack) - 1]
		case '}':
			if len(stack) == 0 || stack[len(stack) - 1] != '{' {
				return false
			}
			stack = stack[:len(stack) - 1]
		}
	}
	if len(stack) > 0 {
		return false
	}
	return true
}

func main() {
	fmt.Println(isValid("()"))
	fmt.Println(isValid("()[]{}"))
	fmt.Println(isValid("([}]"))
	fmt.Println(isValid("([])"))
	fmt.Println(isValid("["))
	fmt.Println(isValid("]"))
}
