/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://leetcode.cn/problems/longest-common-prefix/
 */
package main

import (
	"fmt"
)

func min(x, y int) int {
	if x < y {
		return x
	}
	return y
}

func longestCommonPrefix(strs []string) string {
	minl := 200
	cp := strs[0]
	sls := len(strs)
	for i := 0; i < sls; i++ {
		sl := len(strs[i])
		minl = min(sl, minl)

		if sl == 0 {
			return ""
		}

		if cp[0] != strs[i][0] {
			return ""
		}
	}

	for i := 1; i < minl; i++ {
		for j := 1; j < sls; j++ {
			if cp[i] != strs[j][i] {
				return cp[:i]
			}
		}
	}
	// Then, there's only one element in strs, or other elements only have one char
	return cp[:minl]
}

func main() {
	fmt.Println(longestCommonPrefix([]string{"flower","flow","flight"}))
	fmt.Println(longestCommonPrefix([]string{"dog","racecar","car"}))
	fmt.Println(longestCommonPrefix([]string{"ab", "a"}))
}
