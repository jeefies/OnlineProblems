package main

import (
	"fmt"
	"time"
)

func max(a, b int) int {
	if a > b { return a }
	return b
}

// Normal Slow Solution
/* use DP to find increasing subsequence
func increasingTriplet(nums []int) bool {
	nl := len(nums)
	dp := make([]int, nl)

	fmt.Println(nums)

	for i := 0; i < nl; i++ {
		dp[i] = 1
		for j := 0; j < i; j++ {
			if nums[j] < nums[i] {
				dp[i] = max(dp[i], dp[j] + 1)
			}
		}

		fmt.Printf("\tLoop %d end: ", i)
		fmt.Println(dp)

		if dp[i] >= 3 {
			return true
		}
	}
	return false
}
*/

const MAX_INT = 1 << 31 - 1

// I'm such a fool
/*
func increasingTriplet(nums []int) bool {
	i, j, _ := MAX_INT, MAX_INT, MAX_INT
	iq,  jq := make([]int, 0), make([]int, 0)
	ln := len(nums)

	fmt.Println(nums)

	for x := 0; x < ln; x++ {

		fmt.Printf("\tLoop %d: ", x)
		fmt.Print(iq)
		fmt.Print(" ")
		fmt.Println(jq)

		time.Sleep(time.Second / 2)

		nx := nums[x]

		if nx <= i {
			iq = append(iq, x)
			i = nx
			if len(jq) == 0 && len(iq) > 1 {
				iq = iq[1:]
				i = nums[iq[0]]
			}
			continue
		}

		if nx <= j {
			jq = append(jq, x)
			j = nx

			if len(jq) > 1 {
				jq = jq[1:]
				j = nums[jq[0]]
			}

			if len(iq) > 1 {
				iq = iq[1:]
				i = nums[iq[0]]
			}

			continue
		}

		return true;
	}

	return false;
}
*/

func increasingTriplet(nums []int) bool {
	i, j, l, na := MAX_INT, MAX_INT, len(nums), 0
	for a := 0; a < l; a++ {
		na = nums[a]
		if na <= i {
			i = na
		} else if na <= j {
			j = na
		} else {
			return true
		}
	}
	return false
}

func main() {
	time.Sleep(0)
	fmt.Println(increasingTriplet([]int{1, 2, 3, 4, 5}))
	fmt.Println(increasingTriplet([]int{2, 1, 5, 0, 4, 6}))
	fmt.Println(increasingTriplet([]int{2, 1, 5, 4, 0, 4, 6}))
	fmt.Println(increasingTriplet([]int{1, 2, 1, 3}))
	fmt.Println(increasingTriplet([]int{5, 4, 3, 2, 1}))
	fmt.Println(increasingTriplet([]int{2, 4, -2, -3}))
}
