/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: leetcode.cn/problems/longest-substring-without-repeating-characters/
 */
package main

import (
	"fmt"
)

func IMax(x, y int) int {
	if x > y {
		return x
	}
	return y
}

func IMin(x, y int) int {
	if x > y {
		return y
	}
	return x
}

func lengthOfLongestSubstring(s string) int {
	r := 0
	maxl := 0
	sl := len(s)
	subs := make([]byte, 128)
	bs := []byte(s)
	for i := range bs {
		if i > 0 {
			if subs[bs[i - 1]] > 0 {
				subs[bs[i - 1]]--
			}
		}
		r = IMax(i, r)
		for r < sl && subs[bs[r]] == 0 {
			subs[bs[r]]++
			r++
		}
		maxl = IMax(maxl, r - i)
	}
	return maxl
}

func main() {
	fmt.Println(lengthOfLongestSubstring("dvdf"))
}
