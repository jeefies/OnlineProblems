/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://leetcode.cn/problems/partition-labels/
 */
package main

import (
	"fmt"
)

func partitionLabels(s string) []int {
	cmap := make(map[byte][]int, 26)
	for i := range s {
		if sli, ok := cmap[s[i]]; ok {
			sli[1] = i
		} else {
			cmap[s[i]] = []int{i, i}
		}
	}

	result := []int{}

	left := 0
	for left < len(s) {
		right := cmap[s[left]][1]
		for i := left; i < right; i++ {
			if cmap[s[i]][1] > right {
				right = cmap[s[i]][1]
			}
		}
		result = append(result, right - left + 1)
		left = right + 1
	}
	return result
}

func main() {
	fmt.Println(partitionLabels("ababcbacadefegdehijhklij"))
}
