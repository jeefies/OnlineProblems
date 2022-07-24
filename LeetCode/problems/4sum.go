/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://leetcode.cn/problems/4sum/
 */
package main

import (
	"fmt"
	"sort"
)

func fourSum(nums []int, target int) [][]int {
	ln := len(nums)
	sort.Ints(nums)

	rli := make([][]int, 0, 3)

	for a := range nums {
		// Ignore the same
		if a > 0 && nums[a] == nums[a - 1] {
			continue
		}

		b := a + 1
		for ; b < ln - 2; b++ {
			// Ignore the same
			if b > a + 1 && nums[b] == nums[b - 1] {
				continue
			}

			x := nums[a] + nums[b]
			c, d := b + 1, ln - 1
			for ; c < d; c++ {
				if c > b + 1 && nums[c] == nums[c - 1] {
					continue
				}

				cvx := nums[c] + x
				for c < d && cvx + nums[d] > target {
					d--
				}

				if c == d {
					break
				}

				if cvx + nums[d] == target {
					rli = append(rli, []int{nums[a], nums[b], nums[c], nums[d]})
				}
			}
		}
	}
	return rli
}

func main() {
	fmt.Println(fourSum([]int{1, 0, -1, 0, -2, 2}, 0))
	fmt.Println(fourSum([]int{2, 2, 2, 2, 2}, 8))
}
