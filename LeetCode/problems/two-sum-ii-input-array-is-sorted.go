/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/
 */
package main

import (
	"fmt"
)

func twoSum(numbers []int, target int) []int {
	l, r := 0, len(numbers) - 1
	for l < r {
		for l < r && numbers[l] + numbers[r] < target {
			l++
		}

		for l < r && numbers[l] + numbers[r] > target {
			r--
		}

		if numbers[l] + numbers[r] == target {
			break
		}
	}

	return []int{l+1, r+1}
}

func main() {
	fmt.Println(twoSum([]int{2,7,11,15}, 9))
	fmt.Println(twoSum([]int{2,3,4}, 6))
}
