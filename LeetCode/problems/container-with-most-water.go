/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://leetcode.cn/problems/container-with-most-water/
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

func max(x, y int) int {
	if x < y {
		return y
	}
	return x
}

func maxArea(height []int) int {
	l, r := 0, len(height) - 1
	maxa := 0

	for l < r {
		maxa = max(maxa, (r - l) * min(height[r], height[l]))
		if height[l] <= height[r] {
			l++
		} else {
			r--
		}
	}
	return maxa
}

func main() {
	fmt.Println(maxArea([]int{1,8,6,2,5,4,8,3,7})) // 49
	fmt.Println(maxArea([]int{1,1})) // 1
}
