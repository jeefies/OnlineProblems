/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: leetcode.cn/problems/palindrome-number/
 */
package main

import (
	"fmt"
)

const MAXN int = 1 << 31 - 1

func myAtoi(s string) int {
	// Avoid if s is ""
	if len(s) == 0 {
		return 0
	}

	isNeg := false
	x, i := 0, 0
	
	// Ignore all space (as s.lstrip in python)
	for i = range s {
		if s[i] == ' ' {
			continue
		}
		break
	}
	
	switch s[i] {
	case '-':
		isNeg = true
		fallthrough
	case '+':
		i++
	}

	for ;i < len(s);i++ {
		if '0' <= s[i] && s[i] <= '9' {
			x = x * 10 + int(s[i] - '0')
		} else {
			break
		}

		if x > MAXN {
			if isNeg {
				// use ^MAXN instead of -MAXN - 1 can save a tiny time
				return ^MAXN
			} else {
				return MAXN
			}
		}
	}
	if isNeg {
		x = -x
	}
	return x
}

func main() {
	fmt.Println(myAtoi("   -42")) // -42
	fmt.Println(myAtoi("423 with words")) // 423
	fmt.Println(myAtoi("12.24132")) // 12
	fmt.Println(myAtoi("-91283472332")) // -2147483648
	fmt.Println(myAtoi("+-12")) // 0
	fmt.Println(myAtoi("00000-42a1234")) // 0
	fmt.Println(myAtoi("9223372036854775808")) // 2147483648
	fmt.Println(myAtoi("123-")) // 123
	fmt.Println(myAtoi("18446744073709551617")) // 2147483648
}
