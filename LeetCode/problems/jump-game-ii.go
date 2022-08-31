package main

import (
	"fmt"
)
 
func max(a, b int) int {
	if a > b { return a }
	return b
}

func jump(nums []int) int {
	target := len(nums) - 1
	if target == 0 {
		return 0
	}

	p := 0
	j := 0
	for {
		if p + nums[p] >= target {
			j++
			break
		}

		pto := p + nums[p]
		maxto := pto
		maxi := 0
		for i := p + 1; i <= pto; i++ {
			if i + nums[i] > maxto {
				maxto = i + nums[i]
				maxi = i
			}
		}

		p = maxi
		j++
	}
	return j
}

func main() {
	fmt.Println(jump([]int{2, 3, 1, 1, 4}))
	fmt.Println(jump([]int{2, 3, 0, 1, 4}))
	fmt.Println(jump([]int{2, 3, 4, 5, 6, 1}))
	fmt.Println(jump([]int{5, 9, 3, 2, 1, 0, 2, 3, 3, 1, 0, 0}))
}
