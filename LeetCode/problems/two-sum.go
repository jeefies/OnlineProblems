/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://leetcode.cn/problems/two-sum
 */
package main

import (
	"fmt"
)

func twoSum(nums []int, target int) []int {
	nmap := make(map[int]int)
	for i := range nums {
		if val, ok := nmap[target - nums[i]]; ok {
			return []int{i, val}
		}
		nmap[nums[i]] = i
	}
	return nil
}

func main() {
	arr := twoSum([]int{-2, -3, -1}, -5);
	fmt.Println(arr)
}
