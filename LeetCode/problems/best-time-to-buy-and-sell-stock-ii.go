/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/
 */
package main

import (
	"fmt"
)

func maxProfit(prices []int) int {
	own := false
	cp := 0
	profit := 0
	for i := 0; i < len(prices); i++ {
		if !own {
			if i + 1 < len(prices) && prices[i] < prices[i + 1] {
				own = true
				cp = prices[i]
			}
		} else {
			if i + 1 < len(prices) && prices[i] > prices[i + 1] || i + 1 == len(prices) {
				own = false
				profit += prices[i] - cp
			}
		}
	}

	return profit
}

func main() {
	fmt.Println(maxProfit([]int{7,1,5,3,6,4})) // 7
	fmt.Println(maxProfit([]int{1,2,3,4,5})) // 4
	fmt.Println(maxProfit([]int{7,6,4,3,1})) // 0
}
