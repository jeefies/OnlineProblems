/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: leetcode.cn/problems/longest-palindromic-substring/
 */
package main

import (
	"fmt"
)

func longestPalindrome(s string) string {
	b := []byte(s)
	maxl := 0
	index := 0
	for i := range b {
		if l := palindromeLength(b, i); l > maxl {
			index = i
			maxl = l
		}
	}
	fmt.Println(maxl, index)
	return s[index - (maxl - 1) / 2: index + maxl / 2 + 1]
}

func palindromeLength(b []byte, i int) int {
	bl := len(b)
	offset := 0
	maxl := 0

	for i + offset < bl && i - offset >= 0 && b[i - offset] == b[i + offset] {
		offset++
	}

	if offset > 1 {
		offset--
		maxl = offset * 2 + 1
	}

	offset = 0
	for i + 1 + offset < bl && i - offset >= 0 && b[i - offset] == b[i + 1 + offset] { // Even palidrome
		offset++
	}
	if offset != 0 {
		offset--
		l := offset * 2 + 2
		if l > maxl {
			maxl = l
		}
	}
	return maxl
}

func main() {
	fmt.Println(longestPalindrome("bbb"))
}
