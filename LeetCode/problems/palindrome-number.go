/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: leetcode.cn/problems/palindrome-number
 */
package main

import (
	"fmt"
)

func isPalindrome(x int) bool {
	if x < 0 {
		return false
	}
	bs := make([]byte, 0, 5)
	for x > 0 {
		bs = append(bs, byte(x % 10))
		x /= 10
	}
	l := 0
	r := len(bs) - 1
	for l < r {
		if bs[l] != bs[r] {
			return false
		}
		l++
		r--
	}
	return true
}

func main() {
	fmt.Println(isPalindrome(-121))
	fmt.Println(isPalindrome(1221))
	fmt.Println(isPalindrome(10))
}
