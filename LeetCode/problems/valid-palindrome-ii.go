/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		origin url : https://leetcode.cn/problems/valid-palindrome-ii/
 */
package main

import (
	"fmt"
)

// It's slow......
func validPalindromeDfs(s string, l, r int, modified bool) bool {
	if l >= r {
		return true
	}

	if s[l] == s[r] {
		return validPalindromeDfs(s, l+1, r-1, modified)
	}

	if modified {
		return false
	}

	return validPalindromeDfs(s, l+1, r, true) || validPalindromeDfs(s, l, r-1, true)
}

func validPalindrome(s string) bool {
	l, r := 0, len(s) - 1
	return validPalindromeDfs(s, l, r, false)

}

func main() {
	fmt.Println(validPalindrome("aba"))
	fmt.Println(validPalindrome("a"))
	fmt.Println(validPalindrome("bb"))
	fmt.Println(validPalindrome("abcdba"))
	fmt.Println(validPalindrome("abcdedccba"))
	fmt.Println(validPalindrome("abca"))
	fmt.Println(validPalindrome("lcupuufxoohdfpgjdmysgvhmvffcnqxjjxqncffvmhvgsymdjgpfdhooxfuupucul"))
	fmt.Println(validPalindrome("bcapcb"))
	fmt.Println(validPalindrome("abc"))
	fmt.Println(validPalindrome("abbbccba"))
	fmt.Println(validPalindrome("eeccccbebaeeabebccceea"))
}
