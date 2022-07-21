/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: leetcode.cn/problems/reverse-integer
 */
package main

import (
	"fmt"
)

func reverse(x int) int {
	isNeg := false
	if x < 0 {
		isNeg = true
		x = -x
	}

	r := 0
	for x > 0 {
		r = r * 10 + x % 10
		x /= 10
	}
	if r > 1 << 31 {
		return 0
	}
	if isNeg {
		r = -r
	}
	return r
}

func main() {
	fmt.Println(reverse(120))
}
