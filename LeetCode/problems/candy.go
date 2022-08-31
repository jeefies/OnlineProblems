package main

import (
	"fmt"
)

func max(a, b int) int {
	if a > b { return a }
	return b
}

func candy(ratings []int) int {
	n := len(ratings)
	candies := make([]int, n)

	candies[0] = 1
	for i := 1; i < n; i++ {
		candies[i] = 1
		if ratings[i] > ratings[i - 1] {
			candies[i] = candies[i - 1] + 1
		}
		// fmt.Println("one", candies)
	}

	r := 0
	for i := n - 1; i > 0; i-- {
		if ratings[i] < ratings[i - 1] {
			candies[i - 1] = max(candies[i - 1], candies[i] + 1)
		}
		r += candies[i]
	}
	r += candies[0]

	// fmt.Println(candies)
	return r
}

func main() {
	fmt.Println(candy([]int{1, 0, 2}))
	fmt.Println(candy([]int{1, 2, 2}))
	fmt.Println(candy([]int{1, 3, 4, 5, 2}))
}
