package main

import (
	"fmt"
    "time"
)
 
func max(a, b int) int {
	if a > b { return a }
	return b
}

func canJump(nums []int) bool {
	target := len(nums) - 1

	if target == 0 {
		return true
	}

	p := 0
	for {
		if p + nums[p] >= target {
			break
		}

		pto := p + nums[p]
		maxto := pto
		maxi := p
		for i := p + 1; i <= pto; i++ {
			if i + nums[i] > maxto {
				maxto = i + nums[i]
				maxi = i
			}
		}

		if maxto < target && pto == maxto && nums[maxto] == 0 {
			return false
		}
		p = maxi
	}
	return true
}

func main() {
	fmt.Println(canJump([]int{2, 3, 1, 1, 4}))
	fmt.Println(canJump([]int{2, 3, 0, 1, 4}))
	fmt.Println(canJump([]int{2, 3, 4, 5, 6, 1}))
	fmt.Println(canJump([]int{5, 9, 3, 2, 1, 0, 2, 3, 3, 1, 0, 0}))
	fmt.Println(canJump([]int{3, 2, 1, 0, 4}))
	fmt.Println(canJump([]int{3, 2, 1, 3, 2, 1, 0, 4}))
}
