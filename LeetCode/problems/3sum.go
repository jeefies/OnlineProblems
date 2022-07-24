/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 */
package main

import (
	"fmt"
	"sort"
)

func threeSum(nums []int) [][]int {
	ln := len(nums)
	sort.Ints(nums)
	// fmt.Println(nums)
	rli := make([][]int, 0)
	for x := range nums {
		if x > 0 && nums[x] == nums[x - 1] {
			continue
		}

		l, r := x + 1, ln - 1
		target := -nums[x]
		for l < r {
			if l > x + 1 && nums[l] == nums[l - 1] {
				l++
				continue
			}

			for l < r && nums[l] + nums[r] > target {
				r--
			}

			if l == r {
				break
			}
			
			if nums[l] + nums[r] == target {
				rli = append(rli, []int{nums[x], nums[l], nums[r]})
			}

			l++
		}
	}
	return rli
}


func main() {
	fmt.Println(threeSum([]int{-1,0,1,2,-1,-4}))
	fmt.Println(threeSum([]int{}))
	fmt.Println(threeSum([]int{0,0,0,0}))
	fmt.Println(threeSum([]int{1, 0, -1, 0}))
	fmt.Println(threeSum([]int{-2, 0, 0, 2, 2}))
}
